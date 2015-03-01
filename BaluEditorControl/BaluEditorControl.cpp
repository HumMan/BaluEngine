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
	std::unique_ptr<IDirector> director;
	std::unique_ptr<IBaluWorld> world;

	IBaluSceneInstance* scene_instance;
	TScreen* screen;
	IViewport* main_viewport;
	TView main_viewport_view;

	IAbstractEditor* active_editor;

	TCallbackManagedBridge* callbackbridge;
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
		void OnClick(Object ^ sender, EventArgs ^ e)
		{
			editor->SetActiveTool(tool);
			auto obj_sel = tool->NeedObjectSelect();
			if (obj_sel != TWorldObjectType::None)
			{
				editor_control->ToolObjectSelect->Enabled = true;
				editor_control->ToolObjectSelect->Items->Clear();
				std::vector<IBaluWorldObject*> selection_list;
				editor->ToolNeedObjectSelect(selection_list);
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
				tool_strip->Items->Add(i);
			}
		}
	};

	void BaluEditorControl::OnSelectionChangedByEditor(IBaluWorldObject* old_selection, IBaluWorldObject* new_selection)
	{
		TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(engine->GetWorld(), new_selection);
		SelectedObjectProperty->SelectedObject = obj;
	}
	
	void BaluEditorControl::OnPropertiesChangedByEditor(IBaluWorldObject* changed_obj)
	{
	}

	void BaluEditorControl::OnObjectCreatedByEditor(IBaluWorldObject* new_object)
	{
		WorldTreeView->Nodes->Clear();
		CreateWorldTree(WorldTreeView, p->world.get());
	}

	void BaluEditorControl::InitializeEngine()
	{
		CreateWorldTree(WorldTreeView, p->world.get());
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
		TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(engine->GetWorld(), node->world_object);
		SelectedObjectProperty->SelectedObject = obj;
	}

	Void BaluEditorControl::SetEditedWorldNode(TWolrdTreeNodeTag^ node)
	{
		engine->Edit(node->world_object);
		auto &tools = engine->GetAvailableTools();
		TUtils::CreateEditorToolsToolBar(EditorToolsBar, tools,engine, this);
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
		engine->SetToolSelectedObject(msclr::interop::marshal_as<std::string>(name));
	}

	void BaluEditorControl::SaveWorldTo(String^ path)
	{
		engine->SaveWorldTo(msclr::interop::marshal_as<std::string>(path));
	}
	
	void BaluEditorControl::LoadWorldFrom(String^ path)
	{
		WorldTreeView->Nodes->Clear();
		engine->LoadWorldFrom(msclr::interop::marshal_as<std::string>(path));
		CreateWorldTree(WorldTreeView, engine->GetWorld());
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
				new_sprite_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material, i->second->CastToWorldObject());
				Materialst_node->Nodes->Add(new_sprite_node);
			}
		}
		{
			auto Sprites_node = gcnew TreeNode("Sprites");
			Sprites_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Sprites_node);
			for (auto i = world->sprites.begin(); i != world->sprites.end(); i++)
			{
				auto new_sprite_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_sprite_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Sprite,&i->second);
				Sprites_node->Nodes->Add(new_sprite_node);
			}
		}
		{
			auto PhysBodies_node = gcnew TreeNode("PhysBodies");
			PhysBodies_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(PhysBodies_node);
			for (auto i = world->phys_bodies.begin(); i != world->phys_bodies.end(); i++)
			{
				auto new_physbody_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_physbody_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::PhysBody, &i->second);
				PhysBodies_node->Nodes->Add(new_physbody_node);
			}
		}
		{
			auto Classes_node = gcnew TreeNode("Classes");
			Classes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Classes_node);
			for (auto i = world->classes.begin(); i != world->classes.end(); i++)
			{
				auto new_class_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_class_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::PhysBody, &i->second);
				Classes_node->Nodes->Add(new_class_node);
			}
		}
		{
			auto Scenes_node = gcnew TreeNode("Scenes");
			Scenes_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::Material);
			world_node->Nodes->Add(Scenes_node);
			for (auto i = world->scenes.begin(); i != world->scenes.end(); i++)
			{
				auto new_scene_node = gcnew TreeNode(gcnew String(i->first.c_str()));
				new_scene_node->Tag = gcnew TWolrdTreeNodeTag(TNodeType::PhysBody, &i->second);
				Scenes_node->Nodes->Add(new_scene_node);
			}
		}
	}

	void BaluEditorControl::Render()
	{
			engine->Render();
	}

	Void BaluEditorControl::OnResize(EventArgs^ e)
	{
		engine->SetViewport(TVec2i(this->Width, this->Height));
	}

	BaluEditorControl::BaluEditorControl()
	{
			callbackbridge = new TCallbackManagedBridge(this);

			hWnd = static_cast<HWND>(this->Handle.ToPointer());
			RECT rect;
			GetClientRect(hWnd, &rect);

			engine = new TBaluEditor(*(int*)&hWnd, TVec2i(rect.right - rect.left, rect.bottom - rect.top));

			engine->AddSelectionChangedCallback(callbackbridge, TCallbackManagedBridge::OnSelectionChanged);
			engine->AddPropertiesChangedCallback(callbackbridge, TCallbackManagedBridge::OnPropertiesChanged);
			engine->AddObjectCreatedCallback(callbackbridge, TCallbackManagedBridge::OnObjectCreated);
	}
	BaluEditorControl::~BaluEditorControl()
	{
		delete callbackbridge;
	}

	Void BaluEditorControl::OnKeyDown(KeyEventArgs^ e)
	{
	}

	Void BaluEditorControl::OnKeyPress(KeyPressEventArgs^ e)
	{
	}

	Void BaluEditorControl::OnKeyUp(KeyEventArgs^ e)
	{
	}

	Void BaluEditorControl::OnMouseClick(MouseEventArgs^ e)
	{
	}

	Void BaluEditorControl::OnMouseDoubleClick(MouseEventArgs^ e)
	{
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

	Void BaluEditorControl::OnMouseDown(MouseEventArgs^ e)
	{
		engine->OnMouseDown(Convert(e));
	}

	Void BaluEditorControl::OnMouseMove(MouseEventArgs^ e)
	{
		engine->OnMouseMove(Convert(e));
	}

	Void BaluEditorControl::OnMouseUp(MouseEventArgs^ e)
	{
		engine->OnMouseUp(Convert(e));
	}

	Void BaluEditorControl::OnMouseWheel(MouseEventArgs^ e)
	{
		engine->OnMouseWheel(e->Delta);
	}
}