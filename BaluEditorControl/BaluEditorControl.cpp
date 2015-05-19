#include "BaluEditorControl.h"

#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Source/PropertiesRegistry/propertiesRegistry.h"

using namespace EngineInterface;

#include "../Example/DemoWorld.h"

#include "EventsEditor.h"

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

	String^ BaluEditorControl::GetAssetsDir()
	{
		return gcnew String(p->assets_dir.c_str());
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

	TEventsEditor^ BaluEditorControl::GetEventsEditor()
	{
		return gcnew TEventsEditor(p->world, p->assets_dir.c_str());
	}

	void BaluEditorControl::SetSelectedWorldNode(TWolrdTreeNodeTag^ node)
	{
		TPropertiesObject^ obj = TPropertiesRegistry::CreateProperties(p->world, node->world_object);
		SelectedObjectProperty->SelectedObject = obj;
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
		p->world = CreateDemoWorld(p->director->GetAssetsDir());
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


	BaluEditorControl::BaluEditorControl(IntPtr handle, String^ assets_dir)
	{
		p = new BaluEditorControlPrivate();

		p->assets_dir = msclr::interop::marshal_as<std::string>(assets_dir);
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

}