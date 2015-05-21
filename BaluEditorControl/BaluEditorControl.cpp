#include "BaluEditorControl.h"

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Source/PropertiesRegistry/propertiesRegistry.h"

using namespace EngineInterface;

#include "../Example/DemoWorld.h"

#include "EventsEditor.h"

class BaluEditorControlPrivate
{
public:
	std::string assets_dir;
	IDirector* director;
	IBaluWorld* world;
	IBaluWorldInstance* world_instance;

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

		viewport_drag_active = false;
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
			auto t = Converters::FromClrString(state->ToString());
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

	void BaluEditorControl::SetSelectedWorldNode(TWolrdTreeNodeTag^ node)
	{
		TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(p->world, node->world_object);
		SelectedObjectProperty->SelectedObject = obj;
	}

	BaluEditorControl::BaluEditorControl(IntPtr handle, String^ assets_dir)
	{
		p = new BaluEditorControlPrivate();

		p->assets_dir = Converters::FromClrString(assets_dir);
		p->callbackbridge.reset(new TCallbackManagedBridge(this));

		p->director = IDirector::CreateDirector(p->assets_dir, "editor_control.log");

		p->director->Initialize((void*)handle.ToPointer());
		
	}


	void BaluEditorControl::Destroy()
	{
		if (p->active_edited_object != nullptr)
		DestroyEditorOfWorldObject(p->active_edited_object);

		DestroyEditorScene();

		if (p->world_instance!=nullptr)
			DestroyWorldInstance(p->world_instance);

		DestroyWorld(p->world);
		IDirector::DestroyDirector(p->director);

		delete p;
		p = nullptr;
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	BaluEditorControl::!BaluEditorControl()
	{
		//DestroyEditorScene();

		//DestroyWorldInstance(p->world_instance);
		//DestroyWorld(p->world);
		//IDirector::DestroyDirector(p->director);

		//delete p;
		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	}

	

}