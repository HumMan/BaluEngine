#pragma once

#include <vector>
#include <string>

#include "WorldDirector.h"

#include "Source\PropertiesRegistry\propertiesRegistry.h"

class TCallbackManagedBridge;


namespace EngineInterface
{
	class IBaluWorldObject;
	class IBaluWorld;
	class IAbstractEditor;
	class TLayersManager;
}

namespace Editor
{
	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;

	using namespace EngineInterface;
	
	ref class TWorldDirector;
	class TWorldObjectEditorPrivate;

	public delegate void OnToolsChangeDelegate();
	public delegate void OnSelectedObjectChangeDelegate(TPropertiesObject^ new_selection);
	public delegate void OnLayersChangeDelegate(array<String^>^ names);

	public ref class TWorldObjectEditor: public TEditor
	{
	internal:
		void OnBeforeWorldLoad();
		void OnAfterWorldLoad();
		void OnEditedObjectChange(TEditor^ sender, int type, String^ name);
		void OnObjectListSelectionChange(TEditor^ sender, int type, String^ name);
	private:

		TWorldObjectEditorPrivate* p;
		TWorldDirector^ director;

		IAbstractEditor* CreateEditorOfWorldObject(IBaluWorldObject* obj);
		void DestroyEditorOfWorldObject(IBaluWorldObject* obj);

	public:
		event OnToolsChangeDelegate^ GUI_Notify_ToolsChanged;
		event OnLayersChangeDelegate^ GUI_Notify_LayersChange;
		event OnSelectedObjectChangeDelegate^ GUI_Notify_SelectionChange;
		bool NeedLayers();

		TWorldObjectEditor(IntPtr handle, int width, int height, TWorldDirector^ world_director);
		void Destroy() override;

		//bool ToolNeedObjectSelect(std::vector<IBaluWorldObject*>& selection_list);
		void Resize(int width, int height);

		void MouseDown(MouseEventArgs^ e) ;
		void MouseMove(MouseEventArgs^ e) ;
		void MouseUp(MouseEventArgs^ e) ;
		void MouseWheel(MouseEventArgs^ e) ;

		void Render();

		bool CanSetSelectedAsWork();
		void SetSelectedAsWork();

		bool CanEndSelectedAsWork();
		void EndSelectedAsWork();

		void SetActiveTool(int index);
		int GetActiveTool();
		void SetActiveToolState(int index);

		int GetToolsCount();
		String^ GetToolName(int index);
		int GetToolStatesCount(int index);
		String^ GetToolStateName(int tool_index, int tool_state_index);
	};
}
