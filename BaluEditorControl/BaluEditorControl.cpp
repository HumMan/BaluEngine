#include "BaluEditorControl.h"

#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Source/PropertiesRegistry/propertiesRegistry.h"

using namespace EngineInterface;

#include "../Example/DemoWorld.h"

class TCallbackManagedBridge
{
	gcroot<Editor::BaluEditorControl^> managed_object;
public:
	TCallbackManagedBridge(Editor::BaluEditorControl^ use_obj){ managed_object = use_obj; }
	static void OnSelectionChanged(void* calle, IBaluWorldObject* old_selection, IBaluWorldObject* new_selection)
	{
		((TCallbackManagedBridge*)calle)->managed_object->OnSelectionChangedByEditor(old_selection, new_selection);
	}
	static void OnPropertiesChanged(void* calle, IBaluWorldObject* changed_obj)
	{
		((TCallbackManagedBridge*)calle)->managed_object->OnPropertiesChangedByEditor(changed_obj);
	}
	static void OnObjectCreated(void* calle, IBaluWorldObject* new_object)
	{
		((TCallbackManagedBridge*)calle)->managed_object->OnObjectCreatedByEditor(new_object);
	}
};

template<class T>
std::string GetNewDefaultName()
{
	int static id = 0;
	id++;
	char buf[100];
	sprintf_s(buf, "%s%i",T::GetDefaultName().c_str(), id);
	return std::string(buf);
}

class TMyEditorSelectionChangedListener : public IEditorSelectionChangedListener
{
public:
	BaluEditorControlPrivate* p;
	void SelectionChanged(IProperties* old_selection, IProperties* new_selection)
	{

	}
};

class BaluEditorControlPrivate
{
public:
	IDirector* director;
	IBaluWorld* world;
	IBaluWorldInstance* world_instance;
	std::string base_path;
	IBaluSceneInstance* scene_instance;
	TScreen* screen;
	IViewport* main_viewport;
	TView main_viewport_view;
	IAbstractEditor* active_editor;
	std::unique_ptr<TCallbackManagedBridge> callbackbridge;

	IBaluWorldObject* active_edited_object;

	std::vector<IBaluWorldObject*> active_selection_list;

	TDrawingHelperContext drawing_context;

	TMyEditorSelectionChangedListener selection_change_listener;

	bool viewport_drag_active;
	TVec2 viewport_drag_last_pos;
	TVec2i viewport_drag_last_mouse_pos;

	BaluEditorControlPrivate()
	{
		selection_change_listener.p = this;
		director = nullptr;
		world = nullptr;
		world_instance = nullptr;
		scene_instance = nullptr;
		screen = nullptr;
		main_viewport = nullptr;
		active_editor = nullptr;
		active_edited_object = nullptr;
	}
};



namespace Editor
{
	ref class TUtils
	{
	public:
		static void CreateEditorToolsToolBar(ToolStrip^ tool_strip, const std::vector<TToolWithDescription>& tools, IAbstractEditor* active_editor, BaluEditorControl^ editor_control);
		static void CreateEditorToolStateToolBar(ToolStrip^ tool_state_strip, IEditorTool* tool);
	};

	ref class TEditorToolEvent
	{
		IEditorTool* tool;
		IAbstractEditor* editor;
		BaluEditorControl^ editor_control;
	public:
		TEditorToolEvent(IEditorTool* tool, IAbstractEditor* editor, BaluEditorControl^ editor_control)
		{
			this->tool = tool;
			this->editor = editor;
			this->editor_control = editor_control;
		}

		void OnClick(Object ^ sender, EventArgs ^ e)
		{
			editor->SetActiveTool(tool);
			editor_control->ToolStateToolsBar->Items->Clear();
			TUtils::CreateEditorToolStateToolBar(editor_control->ToolStateToolsBar, tool);

			auto obj_sel = tool->NeedObjectSelect();
			if (obj_sel != TWorldObjectType::None)
			{
				editor_control->ToolObjectSelect->Enabled = true;
				editor_control->ToolObjectSelect->Items->Clear();
				std::vector<IBaluWorldObject*> selection_list;
				editor_control->ToolNeedObjectSelect(selection_list);
				for (auto v : selection_list)
					editor_control->ToolObjectSelect->Items->Add(gcnew String(v->GetName().c_str()));
			}
			else
			{
				editor_control->ToolObjectSelect->Enabled = false;
				editor_control->ToolObjectSelect->Items->Clear();
			}

			
		}
	};

	ref class TEditorToolStateEvent
	{
		IEditorTool* tool;
		String^ state;
	public:
		TEditorToolStateEvent(IEditorTool* tool, String^ state)
		{
			this->tool = tool;
			this->state = state;
		}

		void OnClick(Object ^ sender, EventArgs ^ e)
		{
			auto t = msclr::interop::marshal_as<std::string>(state->ToString());
			tool->SetActiveState(t);
		}
	};

	void TUtils::CreateEditorToolsToolBar(ToolStrip^ tool_strip, const std::vector<TToolWithDescription>& tools, IAbstractEditor* active_editor, BaluEditorControl^ editor_control)
		{
			tool_strip->Items->Clear();
			for (const TToolWithDescription& tool : tools)
			{
				auto handler = gcnew TEditorToolEvent(tool.tool.get(), active_editor, editor_control);
				ToolStripItem^ i = gcnew ToolStripButton(gcnew String(tool.name.c_str()));
				i->Click += gcnew EventHandler(handler, &TEditorToolEvent::OnClick);
				tool_strip->Items->Add(i);
			}
		}
	void TUtils::CreateEditorToolStateToolBar(ToolStrip^ tool_state_strip, IEditorTool* tool)
		{
			tool_state_strip->Items->Clear();
			for (auto& v : tool->GetAvailableStates())
			{
				auto handler = gcnew TEditorToolStateEvent(tool, msclr::interop::marshal_as<String^>(v));
				ToolStripItem^ i = gcnew ToolStripButton(gcnew String(v.c_str()));
				i->Click += gcnew EventHandler(handler, &TEditorToolStateEvent::OnClick);
				tool_state_strip->Items->Add(i);
			}
		}

	IAbstractEditor* BaluEditorControl::CreateEditorOfWorldObject(IBaluWorldObject* obj)
	{
		//if ((dynamic_cast<IBaluMaterial*>(obj)) != nullptr)
		//	return new TMaterialEditor();

		//if ((dynamic_cast<TBaluSpritePolygonDef*>(obj)) != nullptr)
		//	return new TSpritePolygonEditor();

		p->active_edited_object = obj;

		if ((dynamic_cast<IBaluSprite*>(obj)) != nullptr)
			return CreateSpriteEditor(p->drawing_context, p->world, dynamic_cast<IBaluSprite*>(obj), p->scene_instance);

		//if ((dynamic_cast<IBaluClass*>(obj)) != nullptr)
		//	return new TClassEditor();

		if ((dynamic_cast<IBaluScene*>(obj)) != nullptr)
			return CreateSceneEditor(p->drawing_context, p->world, dynamic_cast<IBaluScene*>(obj), p->scene_instance);

		return nullptr;
	}

	void BaluEditorControl::DestroyEditorOfWorldObject(IBaluWorldObject* obj)
	{
		//if ((dynamic_cast<IBaluMaterial*>(obj)) != nullptr)
		//	return new TMaterialEditor();

		//if ((dynamic_cast<TBaluSpritePolygonDef*>(obj)) != nullptr)
		//	return new TSpritePolygonEditor();

		p->active_edited_object = nullptr;

		if ((dynamic_cast<IBaluSprite*>(obj)) != nullptr)
			return DestroySpriteEditor(p->active_editor);

		//if ((dynamic_cast<IBaluClass*>(obj)) != nullptr)
		//	return new TClassEditor();

		if ((dynamic_cast<IBaluScene*>(obj)) != nullptr)
			DestroySceneEditor(p->active_editor);
	}

	bool BaluEditorControl::ToolNeedObjectSelect(std::vector<IBaluWorldObject*>& selection_list)
	{
		selection_list.clear();
		assert(p->active_editor != nullptr);
		if (p->active_editor != nullptr)
		{
			auto need_obj = p->active_editor->GetActiveTool()->NeedObjectSelect();
			switch (need_obj)
			{
			case TWorldObjectType::Material:
				for (const auto& v : p->world->GetMaterials())
					selection_list.push_back(dynamic_cast<IBaluWorldObject*>(v.second));
				break;
			case TWorldObjectType::Sprite:
				for (const auto& v : p->world->GetSprites())
					selection_list.push_back(dynamic_cast<IBaluWorldObject*>(v.second));
				break;
			case TWorldObjectType::Class:
				for (const auto& v : p->world->GetClasses())
					selection_list.push_back(dynamic_cast<IBaluWorldObject*>(v.second));
				break;
			default:
				assert(false);
				return false;
				break;
			}
			p->active_selection_list = selection_list;
			return true;
		}
		p->active_selection_list.clear();
		return false;
	}

	void BaluEditorControl::OnSelectionChangedByEditor(IBaluWorldObject* old_selection, IBaluWorldObject* new_selection)
	{
		TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(p->world, new_selection);
		SelectedObjectProperty->SelectedObject = obj;
	}
	
	void BaluEditorControl::OnPropertiesChangedByEditor(IBaluWorldObject* changed_obj)
	{
	}

	void BaluEditorControl::OnObjectCreatedByEditor(IBaluWorldObject* new_object)
	{
		WorldTreeView->Nodes->Clear();
		CreateWorldTree(WorldTreeView, p->world);
	}

	void BaluEditorControl::InitializeEngine()
	{
		CreateWorldTree(WorldTreeView, p->world);
	}

	template<class T>
	IBaluWorldObject* CreateItem(IBaluWorld* world)
	{
		std::string new_name;
		T* existing_material;
		do
		{
			new_name = GetNewDefaultName<T>();
		} while (world->TryFind(new_name.c_str(), existing_material));

		T* new_mat;
		world->Create(new_name.c_str(), new_mat);
		return dynamic_cast<IBaluWorldObject*>(new_mat);
	}

	void BaluEditorControl::CreateMaterial()
	{
		auto new_item = CreateItem<IBaluMaterial>(p->world);
		OnObjectCreatedByEditor(new_item);
		
		//p->editor->Edit(&p->world->materials[new_name]);
	}
	void BaluEditorControl::CreateSprite()
	{
		auto new_item = CreateItem<IBaluSprite>(p->world);
		OnObjectCreatedByEditor(new_item);
	}
	void BaluEditorControl::CreateClass()
	{
		auto new_item = CreateItem<IBaluClass>(p->world);
		OnObjectCreatedByEditor(new_item);
	}
	void BaluEditorControl::CreateScene()
	{
		auto new_item = CreateItem<IBaluScene>(p->world);
		OnObjectCreatedByEditor(new_item);
	}

	void BaluEditorControl::SetSelectedWorldNode(TWolrdTreeNodeTag^ node)
	{
		TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(p->world, node->world_object);
		SelectedObjectProperty->SelectedObject = obj;
	}

	void BaluEditorControl::CreateEditorScene()
	{
		auto editor_scene = p->world->CreateScene("EditorScene");
		dynamic_cast<IBaluWorldObject*>(editor_scene)->GetProperties()->SetBool("editor_temp_object", true);

		if (editor_scene->FindViewport("main_viewport") == nullptr)
		{
			p->main_viewport = editor_scene->CreateViewport("main_viewport");
			p->main_viewport->SetTransform(TBaluTransform(TVec2(0, 0), TRot(0)));
			p->main_viewport->SetAspectRatio(1);
			p->main_viewport->SetWidth(20);

		}
		p->world->GetCallbacksActiveType().active_type = TCallbacksActiveType::EDITOR;

		p->screen = new TScreen(p->director->GetScreenSize());
		p->director->SetSymulatePhysics(false);

		p->main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));

		p->world_instance = CreateWorldInstance(p->world, p->director->GetResources());

		p->scene_instance = p->world_instance->RunScene(editor_scene);

		p->director->SetWorldInstance(p->world_instance);
		auto callback = CallbackWithData<RenderWorldCallback>(RenderWorld, &p->world->GetCallbacksActiveType(), p, TCallbacksActiveType::EDITOR);
		p->director->SetRenderWorldCallback(callback);

	}

	void BaluEditorControl::DestroyEditorScene()
	{
		IBaluScene* result;
		if (p->world->TryFind("EditorScene", result))
			p->world->DestroyScene("EditorScene");
	}


	void BaluEditorControl::SetEditedWorldNode(TWolrdTreeNodeTag^ node)
	{
		if (p->active_edited_object!=nullptr)
			DestroyEditorOfWorldObject(p->active_edited_object);

		DestroyEditorScene();

		CreateEditorScene();

		p->drawing_context.screen = p->screen;
		p->drawing_context.view = &p->main_viewport_view;
		p->drawing_context.viewport = p->main_viewport;

		p->active_editor = CreateEditorOfWorldObject(node->world_object);

		auto& tools = p->active_editor->GetAvailableTools();
		p->active_editor->SetActiveTool(tools[0].tool.get());
		TUtils::CreateEditorToolsToolBar(EditorToolsBar, tools, p->active_editor, this);

		//ed->OnSelectionChanged.connect(boost::bind(&TBaluEditor::OnSelectionChangedEvent, this, _1, _2));
		//assert(ed != nullptr);
		//if (ed != nullptr)
		//{
		//	ed->Initialize(obj_to_edit, TVec2(0, 0));
		//	p->active_editor = ed;
		//}
	}

	bool BaluEditorControl::CanSetSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		return p->active_editor != nullptr && p->active_editor->CanSetSelectedAsWork();
	}
	void BaluEditorControl::SetSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		if (p->active_editor != nullptr)
			p->active_editor->SetSelectedAsWork();

		auto &tools = p->active_editor->GetAvailableTools();
		TUtils::CreateEditorToolsToolBar(EditorToolsBar, tools, p->active_editor, this);
	}

	bool BaluEditorControl::CanEndSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		return p->active_editor != nullptr && p->active_editor->CanEndSelectedAsWork();
	}
	void BaluEditorControl::EndSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		if (p->active_editor != nullptr)
			p->active_editor->EndSelectedAsWork();
	}

	void BaluEditorControl::SetToolSelectedObject(String^ name)
	{
		auto str_name = msclr::interop::marshal_as<std::string>(name);
		EngineInterface::IBaluWorldObject* obj= nullptr;
		for (auto& v : p->active_selection_list)
			if (v->GetName() == str_name)
				obj = v;
		assert(obj != nullptr);
		p->active_editor->GetActiveTool()->SetSelectedObject(obj);
		//engine->SetToolSelectedObject();
	}

	void BaluEditorControl::SaveWorldTo(String^ path)
	{
		p->world->SaveToXML(msclr::interop::marshal_as<std::string>(path));
	}

	void BaluEditorControl::LoadDemoWorld()
	{
		WorldTreeView->Nodes->Clear();
		if (p->world != nullptr)
		{
			DestroyWorld(p->world);
			p->world = nullptr;
		}
		p->world = CreateDemoWorld(p->base_path);
		CreateWorldTree(WorldTreeView, p->world);
	}
	
	void BaluEditorControl::LoadWorldFrom(String^ path)
	{
		WorldTreeView->Nodes->Clear();
		if (p->world != nullptr)
		{
			DestroyWorld(p->world);
			p->world = nullptr;
		}
		p->world = CreateWorld();
		p->world->LoadFromXML(msclr::interop::marshal_as<std::string>(path));
		CreateWorldTree(WorldTreeView, p->world);
	}

	void BaluEditorControl::CreateWorldTree(TreeView^ WorldTreeView, IBaluWorld* world)
	{
		if (world == nullptr)
			return;
		auto world_node = gcnew TreeNode("World");
		world_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::World);
		WorldTreeView->Nodes->Add(world_node);
		{
			auto Materialst_node = gcnew TreeNode("Materials");
			Materialst_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Materialst_node);
			auto all_materials = world->GetMaterials();
			for (auto i = all_materials.begin(); i != all_materials.end(); i++)
			{
				auto new_sprite_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_sprite_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material, dynamic_cast<IBaluWorldObject*>(i->second));
				Materialst_node->Nodes->Add(new_sprite_node);
			}
		}
		{
			auto Sprites_node = gcnew TreeNode("Sprites");
			Sprites_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Sprite);
			world_node->Nodes->Add(Sprites_node);
			auto all_sprites = world->GetSprites();
			for (auto i = all_sprites.begin(); i != all_sprites.end(); i++)
			{
				auto new_sprite_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_sprite_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Sprite, dynamic_cast<IBaluWorldObject*>(i->second));
				Sprites_node->Nodes->Add(new_sprite_node);
			}
		}
		{
			auto Classes_node = gcnew TreeNode("Classes");
			Classes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Class);
			world_node->Nodes->Add(Classes_node);
			auto all_classes = world->GetClasses();
			for (auto i = all_classes.begin(); i != all_classes.end(); i++)
			{
				auto new_class_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_class_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Class, dynamic_cast<IBaluWorldObject*>(i->second));
				Classes_node->Nodes->Add(new_class_node);
			}
		}
		{
			auto Scenes_node = gcnew TreeNode("Scenes");
			Scenes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Scene);
			world_node->Nodes->Add(Scenes_node);
			auto all_scenes = world->GetScenes();
			for (auto i = all_scenes.begin(); i != all_scenes.end(); i++)
			{
				auto new_scene_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_scene_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Scene, dynamic_cast<IBaluWorldObject*>(i->second));
				Scenes_node->Nodes->Add(new_scene_node);
			}
		}
	}

	void BaluEditorControl::Render()
	{
		p->director->Render();
	}
	
	void BaluEditorControl::SetViewport(int width, int height)
	{
		p->director->SetViewport(TVec2i(width, height));
	}

	
	void BaluEditorControl::Resize(int width, int height)
	{
		*p->screen = TVec2i(width, height);
		p->director->SetScreenSize(p->screen->size);
	}

	

	BaluEditorControl::BaluEditorControl(IntPtr handle)
	{
		p = new BaluEditorControlPrivate();
		p->callbackbridge.reset(new TCallbackManagedBridge(this));

		p->director = CreateDirector();

		p->base_path = p->director->GetBasePath();

		p->director->Initialize((void*)handle.ToPointer());
		p->director->SetViewportResizeCallback(ViewportResize);
	}

	void BaluEditorControl::BeginFrame()
	{
		p->director->Step(0.01);
		p->director->BeginFrame();
	}
	void BaluEditorControl::EndFrame()
	{
		p->director->EndFrame();
	}

	BaluEditorControl::!BaluEditorControl()
	{
		delete p;
	}

	TMouseEventArgs Convert(MouseEventArgs^ e)
	{
		TMouseEventArgs result;
		switch (e->Button)
		{
		case MouseButtons::Left:
			result.button = TMouseButton::Left; break;
		case MouseButtons::Middle:
			result.button = TMouseButton::Middle; break;
		case MouseButtons::Right:
			result.button = TMouseButton::Right; break;
		}
		result.location[0] = e->X;
		result.location[1] = e->Y;
		return result;
	}

	void BaluEditorControl::MouseDown(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			if (e->Button == MouseButtons::Middle&&!p->viewport_drag_active)
			{
				p->viewport_drag_active = true;
				p->viewport_drag_last_mouse_pos = Convert(e).location;
				p->viewport_drag_last_pos = p->main_viewport->GetTransform().position;
			}
			
			p->world_instance->MouseDown(Convert(e));
		}
	}

	TVec2 ToSceneCoord(BaluEditorControlPrivate* p, TVec2i location)
	{
		auto screen_coords = p->screen->FromScreenPixels2(location);
		auto view_coord = p->screen->FromScreenToView(p->main_viewport_view, screen_coords);
		auto scene_coord = IBaluScene::FromViewportToScene(p->main_viewport, view_coord);
		return scene_coord;
	}

	void BaluEditorControl::MouseMove(MouseEventArgs^ e)
	{	
		if (p->world_instance != nullptr)
		{
			if (p->viewport_drag_active)
			{
				auto t = p->main_viewport->GetTransform();
				auto mouse_pos_diff = Convert(e).location - p->viewport_drag_last_mouse_pos;
				
				auto old_scene_coord = ToSceneCoord(p, p->viewport_drag_last_mouse_pos);
				auto new_scene_coord = ToSceneCoord(p, Convert(e).location);

				t.position = p->viewport_drag_last_pos - (new_scene_coord - old_scene_coord);
				p->main_viewport->SetTransform(t);
			}
			p->world_instance->MouseMove(Convert(e));
		}		
	}

	void BaluEditorControl::MouseUp(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			if (e->Button == MouseButtons::Middle&&p->viewport_drag_active)
			{
				p->viewport_drag_active = false;
			}
			p->world_instance->MouseUp(Convert(e));
		}
	}

	void BaluEditorControl::MouseWheel(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			p->world_instance->MouseVerticalWheel(e->Delta);
			if (p->main_viewport != nullptr)
			{
				p->main_viewport->SetWidth(p->main_viewport->GetSize()[0] * (e->Delta>0?1.1:0.9));
			}
		}
	}
}