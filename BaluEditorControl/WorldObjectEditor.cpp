
#include "WorldObjectEditor.h"

#include <baluLib.h>
#include <assert.h>

#include <Interfaces\BaluEngineInterface.h>

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

	class TSelectionChangeListener :public ISelectionChangeListener
	{
	public:
		virtual void OnSelectionChange(EngineInterface::IProperties* new_selection)
		{

		}
	};

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

		IAbstractEditor* active_editor;
		IBaluWorldObject* active_edited_object;

		EngineInterface::TDrawingHelperContext drawing_context;

		bool viewport_drag_active;
		TVec2 viewport_drag_last_pos;
		TVec2i viewport_drag_last_mouse_pos;

		TSelectionChangeListener selection_change_listener;

		TWorldObjectEditorPrivate()
		{
			world = nullptr;

			director = nullptr;
			world_instance = nullptr;
			active_editor = nullptr;
			active_edited_object = nullptr;

			viewport_drag_active = false;
		}
	};

	void TWorldObjectEditor::Render()
	{
		if (p != nullptr)
		{
			p->director->Step(0.01);
			p->director->BeginFrame();
			p->director->Render();
			p->director->EndFrame();
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

		director->Notify_All_AfterWorldLoaded += gcnew TNotify_All_AfterWorldLoaded(this, &TWorldObjectEditor::OnAfterWorldLoad);
		director->Notify_All_BeforeWorldLoaded += gcnew TNotify_All_BeforeWorldLoaded(this, &TWorldObjectEditor::OnBeforeWorldLoad);
		director->Notify_ObjectEditor_EditedObjectChange += gcnew TNotify_ObjectEditor_EditedObjectChange(this, &TWorldObjectEditor::OnEditedObjectChange);
		director->Notify_ObjectEditor_ObjectListSelectionChange += gcnew TNotify_ObjectEditor_ObjectListSelectionChange(this, &TWorldObjectEditor::OnObjectListSelectionChange);

		p->world = world_director->GetWorld();

		p->screen = TScreen(TVec2i(width, height));
		p->director->SetSymulatePhysics(false);
		p->main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));

		WriteInfoToLog("Initializing TWorldObjectEditor success");

		p->drawing_context.screen = &p->screen;
		p->drawing_context.view = &p->main_viewport_view;
		p->drawing_context.viewport = &p->main_viewport;
	}

	void TWorldObjectEditor::Destroy()
	{
		OnEditedObjectChange(this, (int)TWorldObjectType::None, "");
		IDirector::DestroyDirector(p->director, true);
		p->director = nullptr;
		p->world = nullptr;
		director = nullptr;
		delete p;
		p = nullptr;
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

	void TWorldObjectEditor::OnEditedObjectChange(TEditor^ sender, int _type, String^ _name)
	{		
		std::string name = Converters::FromClrString(_name);
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
			}
			if (type != TWorldObjectType::None)
			{
				new_edit_obj = p->world->GetObjectByName(type, name.c_str());
			}
			p->active_edited_object = new_edit_obj;
			if (type != TWorldObjectType::None)
			{

				auto objects = p->world->GetObjects(type);
				p->active_editor = CreateEditorOfWorldObject(new_edit_obj);

				auto editor_scene = p->active_editor->GetEditorSceneInstance();

				//оповещаем редактор слоёв о смене сцены
				if (type == TWorldObjectType::Scene)
					director->Perform_Notify_LayersManager_SceneChange(this, editor_scene);
				else
					director->Perform_Notify_LayersManager_SceneChange(this, nullptr);

				//подключаем отслеживание изменения выделенных объектов
				auto ed_selection_listeners = dynamic_cast<TSelectionChangeListeners*>(p->active_editor);

				ed_selection_listeners->AddSelectionChangeListener(&p->selection_change_listener);

				//по умолчанию выбран первый инструмент
				if (p->active_editor->GetAvailableTools().size()>0)
					SetActiveTool(0);

				GUI_Notify_ToolsChanged();
			}
		}
	}

	void TWorldObjectEditor::OnObjectListSelectionChange(TEditor^ sender, int _type, String^ name)
	{
		TWorldObjectType type = (TWorldObjectType)_type;
		IBaluWorldObject* new_edit_obj = nullptr;
		if (type != TWorldObjectType::None)
		{
			new_edit_obj = p->world->GetObjectByName(type, Converters::FromClrString(name).c_str());
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
		director->Perform_Notify_ObjectList_TypeChange(this, (int)tool->NeedObjectSelect());
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

	bool TWorldObjectEditor::NeedLayers()
	{
		//return (p->active_editor);
		return false;
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
			else if(e->Button == MouseButtons::Left)
			{
				p->active_editor->GetActiveTool()->OnMouseDown(Convert(e));
			}
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
			else
			{
				p->active_editor->GetActiveTool()->OnMouseMove(Convert(e));
			}
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
			else if (e->Button == MouseButtons::Left)
			{
				p->active_editor->GetActiveTool()->OnMouseUp(Convert(e));
			}
		}
	}

	void TWorldObjectEditor::MouseWheel(MouseEventArgs^ e)
	{
		if (p->world_instance != nullptr)
		{
			p->main_viewport.SetWidth(p->main_viewport.GetSize()[0] * (e->Delta>0 ? 1.1 : 0.9));
		}
	}


	IAbstractEditor* TWorldObjectEditor::CreateEditorOfWorldObject(IBaluWorldObject* obj)
	{	
		p->main_viewport.SetTransform(TBaluTransform(TVec2(0, 0), TRot(0)));
		p->main_viewport.SetAspectRatio(((float)p->screen.size[1]) / p->screen.size[0]);
		p->main_viewport.SetWidth(20);
		
		bool compile_success;
		std::string error_message;
		p->world_instance = CreateWorldInstance(p->world, p->director->GetResources(), p->director->GetAssetsDir(), false, compile_success, error_message);
		p->director->SetWorldInstance(p->world_instance);

		p->active_edited_object = obj;
		return obj->CreateEditor(p->drawing_context, p->world_instance);
	}

	void TWorldObjectEditor::DestroyEditorOfWorldObject(IBaluWorldObject* obj)
	{
		p->active_edited_object = nullptr;

		auto ed_selection_listeners = dynamic_cast<TSelectionChangeListeners*>(p->active_editor);
		ed_selection_listeners->RemoveSelectionChangeListener(&p->selection_change_listener);

		DestroyEditor(p->active_editor);

		DestroyWorldInstance(p->world_instance);
	}
	
}