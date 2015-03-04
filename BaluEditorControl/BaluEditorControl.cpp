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

	TDrawingHelperContext drawing_context;

	TMyEditorSelectionChangedListener selection_change_listener;
	BaluEditorControlPrivate()
	{
		selection_change_listener.p = this;
	}
};



namespace Editor
{
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

		static bool ToolNeedObjectSelect(std::vector<IBaluWorldObject*>& selection_list)
		{
			selection_list.clear();
			//assert(p->active_editor != nullptr);
			//if (p->active_editor != nullptr)
			//{
			//	auto need_obj = p->active_editor->active_tool->NeedObjectSelect();
			//	switch (need_obj)
			//	{
			//	case TWorldObjectType::Material:
			//		for (const auto& v : p->world->materials)
			//			selection_list.push_back((TWorldObjectDef*)&(v.second));
			//		break;
			//	case TWorldObjectType::Sprite:
			//		for (const auto& v : p->world->sprites)
			//			selection_list.push_back((TWorldObjectDef*)&(v.second));
			//		break;
			//	case TWorldObjectType::PhysBody:
			//		for (const auto& v : p->world->phys_bodies)
			//			selection_list.push_back((TWorldObjectDef*)&(v.second));
			//		break;
			//	case TWorldObjectType::Class:
			//		for (const auto& v : p->world->classes)
			//			selection_list.push_back((TWorldObjectDef*)&(v.second));
			//		break;
			//	default:
			//		assert(false);
			//		return false;
			//		break;
			//	}
			//	return true;
			//}
			return false;
		}

		void OnClick(Object ^ sender, EventArgs ^ e)
		{
			editor->SetActiveTool(tool);
			auto obj_sel = tool->NeedObjectSelect();
			if (obj_sel != TWorldObjectType::None)
			{
				editor_control->ToolObjectSelect->Enabled = true;
				editor_control->ToolObjectSelect->Items->Clear();
				std::vector<IBaluWorldObject*> selection_list;
				ToolNeedObjectSelect(selection_list);
				//for (auto v : selection_list)
				//	editor_control->ToolObjectSelect->Items->Add(gcnew String(v->GetName().c_str()));
			}
			else
			{
				editor_control->ToolObjectSelect->Enabled = false;
				editor_control->ToolObjectSelect->Items->Clear();
			}

			
		}
	};

	ref class TUtils
	{
	public:
		static void CreateEditorToolsToolBar(ToolStrip^ tool_strip, const std::vector<TToolWithDescription>& tools, IAbstractEditor* engine, BaluEditorControl^ editor_control)
		{
			tool_strip->Items->Clear();
			for (const TToolWithDescription& tool : tools)
			{
				auto handler = gcnew TEditorToolEvent(tool.tool.get(), engine, editor_control);
				ToolStripItem^ i = gcnew ToolStripButton(gcnew String(tool.name.c_str()));
				i->Click += gcnew EventHandler(handler, &TEditorToolEvent::OnClick);
				tool_strip->Items->Add(i);
			}
		}
	};

	IAbstractEditor* BaluEditorControl::CreateEditorOfWorldObject(IBaluWorldObject* obj)
	{
		//if ((dynamic_cast<IBaluMaterial*>(obj)) != nullptr)
		//	return new TMaterialEditor();

		//if ((dynamic_cast<TBaluSpritePolygonDef*>(obj)) != nullptr)
		//	return new TSpritePolygonEditor();

		//if ((dynamic_cast<IBaluSprite*>(obj)) != nullptr)
		//	return new TSpriteEditor();

		//if ((dynamic_cast<IBaluClass*>(obj)) != nullptr)
		//	return new TClassEditor();

		if ((dynamic_cast<IBaluScene*>(obj)) != nullptr)
			return CreateSceneEditor(p->drawing_context, p->world, dynamic_cast<IBaluScene*>(obj), p->scene_instance);

		return nullptr;
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

	void BaluEditorControl::SetEditedWorldNode(TWolrdTreeNodeTag^ node)
	{
		p->drawing_context.screen = p->screen;
		p->drawing_context.view = &p->main_viewport_view;
		p->drawing_context.viewport = p->main_viewport;

		//engine->Edit(node->world_object);
		//auto &tools = engine->GetAvailableTools();
		//TUtils::CreateEditorToolsToolBar(EditorToolsBar, tools,engine, this);

		//SelectionChangedCallbackRef(SelectionChangedCallbackRef_calle, NULL, obj_to_edit);
		auto ed = CreateEditorOfWorldObject(node->world_object);

		auto& tools = ed->GetAvailableTools();
		ed->SetActiveTool(tools[1].tool.get());

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
		//engine->SetToolSelectedObject(msclr::interop::marshal_as<std::string>(name));
	}

	void BaluEditorControl::SaveWorldTo(String^ path)
	{
		p->world->SaveToXML(msclr::interop::marshal_as<std::string>(path));
	}
	
	void BaluEditorControl::LoadWorldFrom(String^ path)
	{
		WorldTreeView->Nodes->Clear();
		p->world->LoadFromXML(msclr::interop::marshal_as<std::string>(path));
		CreateWorldTree(WorldTreeView, p->world);
	}

	void BaluEditorControl::CreateWorldTree(TreeView^ WorldTreeView, IBaluWorld* world)
	{
		
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
			Sprites_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
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
			Classes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Classes_node);
			auto all_classes = world->GetClasses();
			for (auto i = all_classes.begin(); i != all_classes.end(); i++)
			{
				auto new_class_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_class_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::PhysBody, dynamic_cast<IBaluWorldObject*>(i->second));
				Classes_node->Nodes->Add(new_class_node);
			}
		}
		{
			auto Scenes_node = gcnew TreeNode("Scenes");
			Scenes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Scenes_node);
			auto all_scenes = world->GetScenes();
			for (auto i = all_scenes.begin(); i != all_scenes.end(); i++)
			{
				auto new_scene_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_scene_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::PhysBody, dynamic_cast<IBaluWorldObject*>(i->second));
				Scenes_node->Nodes->Add(new_scene_node);
			}
		}
	}

	void BaluEditorControl::Render()
	{
		p->director->Render();
	}
	

	IDirector* director;
	TView main_viewport_view;
	IBaluSceneInstance* scene_instance;
	TScreen* screen;
	IViewport* main_viewport;

	TVec2i size;
	void BaluEditorControl::SetViewport(int width, int height)
	{
		size = TVec2i(width, height);
		p->director->SetViewport(size);
	}

	
	void BaluEditorControl::Resize(int width, int height)
	{
		TVec2i old_size(size);
		//TVec2i size(width, height);
		size = TVec2i(width, height);
		*(p->screen) = TScreen(size);
		p->director->SetViewport(size);

		//TODO не в виде отношений
		TVec2 k = TVec2((float)size[0], (float)size[1]) / TVec2((float)old_size[0], (float)old_size[1]);
		auto old_vieport_size = main_viewport->GetSize();
		auto new_vieport_size = old_vieport_size.ComponentMul(k);
		main_viewport->SetSize(new_vieport_size);
	}

	void RenderWorld(IBaluWorldInstance* world, TRender* render)
	{
		*screen = TScreen(size);

		std::vector<TRenderCommand> render_commands;
		std::vector<TCustomDrawCommand> custom_draw_commands;
		auto viewport_aabb = main_viewport->GetAABB();
		scene_instance->QueryAABB(viewport_aabb, render_commands, custom_draw_commands);

		for (auto& v : custom_draw_commands)
		{
			v.screen = screen;
			v.view = &main_viewport_view;
			v.viewport = &viewport_aabb;
		}

		//render->EnableScissor(true);
		//render->SetScissorRect(*screen, main_viewport_view);
		render->Render(render_commands, custom_draw_commands, main_viewport);
		//render->EnableScissor(false);
	}

	BaluEditorControl::BaluEditorControl(IntPtr handle)
	{
		p = new BaluEditorControlPrivate();
		p->callbackbridge.reset(new TCallbackManagedBridge(this));

		p->director = CreateDirector();
		director = p->director;

		p->base_path = p->director->GetBasePath();

		p->director->Initialize((void*)handle.ToPointer());

		p->world = CreateDemoWorld(p->base_path);

		p->world->GetCallbacksActiveType().active_type = TCallbacksActiveType::EDITOR;

		p->screen = new TScreen(TVec2i(32,32));
		screen = p->screen;
		p->director->SetSymulatePhysics(false);

		p->main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));
		main_viewport_view = p->main_viewport_view;

		p->world_instance = CreateWorldInstance(p->world, p->director->GetResources());
		auto demo_scene = p->world->GetScene("scene0");
		
		main_viewport = demo_scene->FindViewport("main_viewport");

		p->scene_instance = p->world_instance->RunScene(demo_scene);
		scene_instance = p->scene_instance;
		p->director->SetWorldInstance(p->world_instance);
		p->director->SetRenderWorldCallback(RenderWorld);

		TDrawingHelperContext drawing_context;
		drawing_context.screen = screen;
		drawing_context.view = &main_viewport_view;
		drawing_context.viewport = main_viewport;

		auto scene_editor = CreateSceneEditor(drawing_context, p->world, demo_scene, scene_instance);
		auto& tools = scene_editor->GetAvailableTools();
		scene_editor->SetActiveTool(tools[1].tool.get());
			//engine->AddSelectionChangedCallback(callbackbridge, TCallbackManagedBridge::OnSelectionChanged);
			//engine->AddPropertiesChangedCallback(callbackbridge, TCallbackManagedBridge::OnPropertiesChanged);
		//engine->AddObjectCreatedCallback(callbackbridge, TCallbackManagedBridge::OnObjectCreated);
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
			p->world_instance->MouseDown(Convert(e));
	}

	void BaluEditorControl::MouseMove(MouseEventArgs^ e)
	{	
		if (p->world_instance != nullptr)
			p->world_instance->MouseMove(Convert(e));
	}

	void BaluEditorControl::MouseUp(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
			p->world_instance->MouseUp(Convert(e));
	}

	void BaluEditorControl::MouseWheel(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
			p->world_instance->MouseVerticalWheel(e->Delta);
	}
}