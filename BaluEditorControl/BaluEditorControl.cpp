#include "BaluEditorControl.h"

#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

using namespace EngineInterface;

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
				//	editor_control->ToolObjectSelect->Items->Add(gcnew System::String(v->GetName().c_str()));
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
				ToolStripItem^ i = gcnew ToolStripButton(gcnew System::String(tool.name.c_str()));
				i->Click += gcnew EventHandler(handler, &TEditorToolEvent::OnClick);
				//tool_strip->Items->Add(i);
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

		//if ((dynamic_cast<TBaluPhysBodyDef*>(obj)) != nullptr)
		//	return new TPhysBodyEditor();

		//if ((dynamic_cast<IBaluClass*>(obj)) != nullptr)
		//	return new TClassEditor();

		if ((dynamic_cast<IBaluScene*>(obj)) != nullptr)
			return CreateSceneEditor(p->screen, &p->main_viewport_view, p->main_viewport, p->world, dynamic_cast<IBaluScene*>(obj), p->scene_instance);

		return nullptr;
	}

	void BaluEditorControl::OnSelectionChangedByEditor(IBaluWorldObject* old_selection, IBaluWorldObject* new_selection)
	{
		//TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(engine->GetWorld(), new_selection);
		//SelectedObjectProperty->SelectedObject = obj;
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

	Void BaluEditorControl::CreateMaterial()
	{
		//engine->CreateMaterial();
	}
	Void BaluEditorControl::CreateSprite()
	{
		//engine->CreateSprite();
	}
	Void BaluEditorControl::CreatePhysBody()
	{
		//engine->CreatePhysBody();
	}
	Void BaluEditorControl::CreateClass()
	{
		//engine->CreateClass();
	}
	Void BaluEditorControl::CreateScene()
	{
		//engine->CreateScene();
	}

	Void BaluEditorControl::SetSelectedWorldNode(TWolrdTreeNodeTag^ node)
	{
		//TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(engine->GetWorld(), node->world_object);
		//SelectedObjectProperty->SelectedObject = obj;
	}

	Void BaluEditorControl::SetEditedWorldNode(TWolrdTreeNodeTag^ node)
	{
		//engine->Edit(node->world_object);
		//auto &tools = engine->GetAvailableTools();
		//TUtils::CreateEditorToolsToolBar(EditorToolsBar, tools,engine, this);

		//SelectionChangedCallbackRef(SelectionChangedCallbackRef_calle, NULL, obj_to_edit);
		auto ed = CreateEditorOfWorldObject(node->world_object);
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

	void BaluEditorControl::SetToolSelectedObject(System::String^ name)
	{
		//engine->SetToolSelectedObject(msclr::interop::marshal_as<std::string>(name));
	}

	void BaluEditorControl::SaveWorldTo(System::String^ path)
	{
		p->world->SaveToXML(msclr::interop::marshal_as<std::string>(path));
	}
	
	void BaluEditorControl::LoadWorldFrom(System::String^ path)
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
				auto new_sprite_node = gcnew TreeNode(gcnew System::String(i->first.c_str()));
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
				auto new_sprite_node = gcnew TreeNode(gcnew System::String(i->first.c_str()));
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
				auto new_class_node = gcnew TreeNode(gcnew System::String(i->first.c_str()));
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
				auto new_scene_node = gcnew TreeNode(gcnew System::String(i->first.c_str()));
				new_scene_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::PhysBody, dynamic_cast<IBaluWorldObject*>(i->second));
				Scenes_node->Nodes->Add(new_scene_node);
			}
		}
	}

	void BaluEditorControl::Render()
	{
		p->director->Render();
	}

	Void BaluEditorControl::Resize(int width, int height)
	{
		p->director->SetViewport(TVec2i(width,height));
	}

	BaluEditorControl::BaluEditorControl()
	{
		p = new BaluEditorControlPrivate();
		p->callbackbridge.reset(new TCallbackManagedBridge(this));

		p->world = CreateWorld();

		p->director = CreateDirector();
		p->base_path = p->director->GetBasePath();

		p->director->Initialize(false);

		p->world->GetCallbacksActiveType().active_type = TCallbacksActiveType::EDITOR;

		//p->screen = new TScreen(director->GetScreenSize());

		p->main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));

			//engine->AddSelectionChangedCallback(callbackbridge, TCallbackManagedBridge::OnSelectionChanged);
			//engine->AddPropertiesChangedCallback(callbackbridge, TCallbackManagedBridge::OnPropertiesChanged);
			//engine->AddObjectCreatedCallback(callbackbridge, TCallbackManagedBridge::OnObjectCreated);
	}
	BaluEditorControl::~BaluEditorControl()
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

	Void BaluEditorControl::MouseDown(MouseEventArgs^ e)
	{
		p->world_instance->MouseDown(Convert(e));
	}

	Void BaluEditorControl::MouseMove(MouseEventArgs^ e)
	{
		p->world_instance->MouseMove(Convert(e));
	}

	Void BaluEditorControl::MouseUp(MouseEventArgs^ e)
	{
		p->world_instance->MouseUp(Convert(e));
	}

	Void BaluEditorControl::MouseWheel(MouseEventArgs^ e)
	{
		p->world_instance->MouseVerticalWheel(e->Delta);
	}
}