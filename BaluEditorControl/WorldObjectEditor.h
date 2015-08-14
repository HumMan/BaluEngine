#pragma once

#include <vector>
#include <string>

#include "WorldDirector.h"

class TCallbackManagedBridge;
class TLayersManager;

namespace EngineInterface
{
	class IBaluWorldObject;
	class IBaluWorld;
	class IAbstractEditor;
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
	public delegate void OnSelectedObjectChangeDelegate(int type, int subtype, int index);

	public ref class TWorldObjectEditor: public TEditor
	{
	internal:
		void OnBeforeWorldLoad()override;
		void OnAfterWorldLoad()override;
		void OnEditedObjectChange(TEditor^ sender, int type, String^ name)override;
		void OnObjectListSelectionChange(TEditor^ sender, int type, String^ name)override;
	private:

		TWorldObjectEditorPrivate* p;
		TWorldDirector^ director;

		IAbstractEditor* CreateEditorOfWorldObject(IBaluWorldObject* obj);
		void DestroyEditorOfWorldObject(IBaluWorldObject* obj);
		void CreateEditorScene(TLayersManager* scene_layers);
		void DestroyEditorScene();

	public:
		event OnToolsChangeDelegate^ GUI_Notify_ToolsChanged;

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
