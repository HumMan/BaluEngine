
#include "WorldObjectEditor.h"

#include <baluLib.h>
#include <assert.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Converters.h"

namespace Editor
{
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

	class TWorldObjectEditorPrivate
	{
	public:
		//source edited world
		IBaluWorld* world;

		//local objects
		TScreen screen;
		TViewport main_viewport;
		TView main_viewport_view;

		IDirector* director;
		IBaluWorldInstance* world_instance;
		IBaluSceneInstance* scene_instance;	
		IAbstractEditor* active_editor;
		IBaluWorldObject* active_edited_object;

		TDrawingHelperContext drawing_context;

		bool viewport_drag_active;
		TVec2 viewport_drag_last_pos;
		TVec2i viewport_drag_last_mouse_pos;

		TWorldObjectEditorPrivate()
		{
			world = nullptr;

			director = nullptr;
			world_instance = nullptr;
			scene_instance = nullptr;
			active_editor = nullptr;
			active_edited_object = nullptr;

			viewport_drag_active = false;
		}
	};

	void TWorldObjectEditor::Render()
	{
		try
		{
			p->director->Step(0.01);
			p->director->BeginFrame();
			p->director->Render();
			p->director->EndFrame();
		}
		catch (std::exception)
		{

		}
	}

	TWorldObjectEditor::TWorldObjectEditor(IntPtr handle, int width, int height, TWorldDirector^ world_director)
	{
		WriteInfoToLog("Initializing TWorldObjectEditor");

		this->director = world_director;
		world_director->RegisterEditor(this);

		auto assets_dir = Converters::FromClrString(world_director->GetAssetsDir());
		p = new TWorldObjectEditorPrivate();
		p->director = IDirector::CreateDirector(assets_dir);
		p->director->Initialize((void*)handle.ToPointer());
		p->director->SetViewport(TVec2i(width, height));

		p->world = world_director->GetWorld();

		p->screen = TScreen(TVec2i(width, height));
		p->director->SetSymulatePhysics(false);
		p->main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));

		WriteInfoToLog("Initializing TWorldObjectEditor success");
	}

	void TWorldObjectEditor::Destroy()
	{
		OnEditedObjectChange(this, (int)TWorldObjectType::None, "");
		IDirector::DestroyDirector(p->director);
		p->director = nullptr;
		p->world = nullptr;
		director = nullptr;
		delete p;
	}
	void TWorldObjectEditor::Resize(int width, int height)
	{
		if (p->world_instance != nullptr)
		{
			p->screen = TVec2i(width, height);
			auto old_size = p->director->GetScreenSize();
			TVec2 k = TVec2(p->screen.size[0], p->screen.size[1]) / TVec2(old_size[0], old_size[1]);

			p->main_viewport.SetSize(p->main_viewport.GetSize().ComponentMul(k));
		}
		p->director->SetScreenSize(p->screen.size);
	}
	void TWorldObjectEditor::OnBeforeWorldLoad()
	{
		if (p->world != nullptr)
		{
			OnEditedObjectChange(this, (int)TWorldObjectType::None, "");
			p->director->SetWorldInstance(nullptr);
		}
	}
	void TWorldObjectEditor::OnAfterWorldLoad()
	{
		p->world = director->GetWorld();
		OnEditedObjectChange(this, (int)TWorldObjectType::None, "");
	}

	void TWorldObjectEditor::OnEditedObjectChange(TEditor^ sender, int _type, std::string name)
	{		
		TWorldObjectType type = (TWorldObjectType)_type;
		
		IBaluWorldObject* new_edit_obj = nullptr;
		if (type != TWorldObjectType::None)
		{
			new_edit_obj = p->world->GetObjectByName(type, name.c_str());		
		}
		if (new_edit_obj != p->active_edited_object)
		{
			if (p->active_edited_object != nullptr)
			{
				DestroyEditorOfWorldObject(p->active_edited_object);
				DestroyEditorScene();
			}
			if (type != TWorldObjectType::None)
			{
				new_edit_obj = p->world->GetObjectByName(type, name.c_str());
			}
			p->active_edited_object = new_edit_obj;
			if (type != TWorldObjectType::None)
			{
				if (type == TWorldObjectType::Scene)
				{
					CreateEditorScene(dynamic_cast<IBaluScene*>(new_edit_obj)->GetLayers());
					director->LayersManagerSceneChange(this, p->scene_instance);
				}
				else
				{
					CreateEditorScene(nullptr);
					director->LayersManagerSceneChange(this, nullptr);
				}
				p->drawing_context.screen = &p->screen;
				p->drawing_context.view = &p->main_viewport_view;
				p->drawing_context.viewport = &p->main_viewport;
				
				auto objects = p->world->GetObjects(type);
				p->active_editor = CreateEditorOfWorldObject(new_edit_obj);

				if (p->active_editor->GetAvailableTools().size()>0)
					SetActiveTool(0);
				OnToolsChange();
			}
		}
	}

	void TWorldObjectEditor::OnObjectListSelectionChange(TEditor^ sender, int _type, std::string name)
	{
		TWorldObjectType type = (TWorldObjectType)_type;
		IBaluWorldObject* new_edit_obj = nullptr;
		if (type != TWorldObjectType::None)
		{
			new_edit_obj = p->world->GetObjectByName(type, name.c_str());
		}

		p->active_editor->GetActiveTool()->SetSelectedObject(new_edit_obj);
	}

	bool TWorldObjectEditor::CanSetSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		return p->active_editor != nullptr && p->active_editor->CanSetSelectedAsWork();
		return false;
	}
	void TWorldObjectEditor::SetSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		if (p->active_editor != nullptr)
			p->active_editor->SetSelectedAsWork();

		auto &tools = p->active_editor->GetAvailableTools();
	}

	bool TWorldObjectEditor::CanEndSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		return p->active_editor != nullptr && p->active_editor->CanEndSelectedAsWork();
	}
	void TWorldObjectEditor::EndSelectedAsWork()
	{
		assert(p->active_editor != nullptr);
		if (p->active_editor != nullptr)
			p->active_editor->EndSelectedAsWork();
	}
	void TWorldObjectEditor::SetActiveTool(int index)
	{
		auto& tools = p->active_editor->GetAvailableTools();
		auto tool = tools[index].tool.get();
		p->active_editor->SetActiveTool(tool);
		director->OnSelectObjectsTypeChange(this, (int)tool->NeedObjectSelect());
	}
	int TWorldObjectEditor::GetActiveTool()
	{
		auto active_tool = p->active_editor->GetActiveTool();
		auto& tools = p->active_editor->GetAvailableTools();
		for (int i = 0; i < tools.size(); i++)
		{
			if (tools[i].tool.get() == active_tool)
				return i;
		}
		return -1;
	}
	void TWorldObjectEditor::SetActiveToolState(int index)
	{
		auto active_tool = p->active_editor->GetActiveTool();
		auto new_state = active_tool->GetAvailableStates()[index];
		active_tool->SetActiveState(new_state);
	}
	int TWorldObjectEditor::GetToolsCount()
	{
		auto& tools = p->active_editor->GetAvailableTools();
		return tools.size();
	}
	String^ TWorldObjectEditor::GetToolName(int index)
	{
		auto& tools = p->active_editor->GetAvailableTools();
		return Converters::ToClrString(tools[index].name);
	}
	int TWorldObjectEditor::GetToolStatesCount(int index)
	{
		auto& tools = p->active_editor->GetAvailableTools();
		return tools[index].tool->GetAvailableStates().size();
	}
	String^ TWorldObjectEditor::GetToolStateName(int tool_index, int tool_state_index)
	{
		auto& tools = p->active_editor->GetAvailableTools();
		return Converters::ToClrString(tools[tool_index].tool->GetAvailableStates()[tool_state_index]);
	}
	void TWorldObjectEditor::CreateEditorScene(TLayersManager* scene_layers)
	{
		p->main_viewport.SetTransform(TBaluTransform(TVec2(0, 0), TRot(0)));
		p->main_viewport.SetAspectRatio(((float)p->screen.size[1]) / p->screen.size[0]);
		p->main_viewport.SetWidth(20);

		p->world_instance = CreateWorldInstance(p->world, p->director->GetResources());
		p->scene_instance = p->world_instance->RunScene(scene_layers);
		p->world_instance->GetComposer()->AddToRender(p->scene_instance, &p->main_viewport);
		p->director->SetWorldInstance(p->world_instance);
	}

	void TWorldObjectEditor::DestroyEditorScene()
	{	
		DestroyWorldInstance(p->world_instance);
		p->world_instance = nullptr;
	}

	void TWorldObjectEditor::MouseDown(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			if (e->Button == MouseButtons::Middle&&!p->viewport_drag_active)
			{
				p->viewport_drag_active = true;
				p->viewport_drag_last_mouse_pos = Convert(e).location;
				p->viewport_drag_last_pos = p->main_viewport.GetTransform().position;
			}

			p->world_instance->MouseDown(Convert(e));
		}
	}

	TVec2 ToSceneCoord(TWorldObjectEditorPrivate* p, TVec2i location)
	{
		auto screen_coords = p->screen.FromScreenPixels2(location);
		auto view_coord = p->screen.FromScreenToView(p->main_viewport_view, screen_coords);
		auto scene_coord = IBaluScene::FromViewportToScene(&p->main_viewport, view_coord);
		return scene_coord;
	}

	void TWorldObjectEditor::MouseMove(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			if (p->viewport_drag_active)
			{
				auto t = p->main_viewport.GetTransform();
				auto mouse_pos_diff = Convert(e).location - p->viewport_drag_last_mouse_pos;

				auto old_scene_coord = ToSceneCoord(p, p->viewport_drag_last_mouse_pos);
				auto new_scene_coord = ToSceneCoord(p, Convert(e).location);

				t.position = p->viewport_drag_last_pos - (new_scene_coord - old_scene_coord);
				p->main_viewport.SetTransform(t);
			}
			p->world_instance->MouseMove(Convert(e));
		}
	}

	void TWorldObjectEditor::MouseUp(MouseEventArgs^ e)
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

	void TWorldObjectEditor::MouseWheel(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			p->world_instance->MouseVerticalWheel(e->Delta);
			p->main_viewport.SetWidth(p->main_viewport.GetSize()[0] * (e->Delta>0 ? 1.1 : 0.9));
		}
	}


	IAbstractEditor* TWorldObjectEditor::CreateEditorOfWorldObject(IBaluWorldObject* obj)
	{
		
		p->active_edited_object = obj;

		if ((dynamic_cast<IBaluMaterial*>(obj)) != nullptr)
			return CreateMaterialEditor(p->drawing_context, p->world, dynamic_cast<IBaluMaterial*>(obj), p->scene_instance);

		if ((dynamic_cast<IBaluSprite*>(obj)) != nullptr)
			return CreateSpriteEditor(p->drawing_context, p->world, dynamic_cast<IBaluSprite*>(obj), p->scene_instance);

		if ((dynamic_cast<IBaluClass*>(obj)) != nullptr)
			return CreateClassEditor(p->drawing_context, p->world, dynamic_cast<IBaluClass*>(obj), p->scene_instance);

		if ((dynamic_cast<IBaluScene*>(obj)) != nullptr)
			return CreateSceneEditor(p->drawing_context, p->world, dynamic_cast<IBaluScene*>(obj), p->scene_instance);

		return nullptr;
	}

	void TWorldObjectEditor::DestroyEditorOfWorldObject(IBaluWorldObject* obj)
	{
		p->active_edited_object = nullptr;

		if ((dynamic_cast<IBaluMaterial*>(obj)) != nullptr)
			return DestroyMaterialEditor(p->active_editor);

		if ((dynamic_cast<IBaluSprite*>(obj)) != nullptr)
			return DestroySpriteEditor(p->active_editor);

		if ((dynamic_cast<IBaluClass*>(obj)) != nullptr)
			return DestroyClassEditor(p->active_editor);

		if ((dynamic_cast<IBaluScene*>(obj)) != nullptr)
			DestroySceneEditor(p->active_editor);
	}
	
}