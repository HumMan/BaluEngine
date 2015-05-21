#pragma once

#include <vector>

#include "WorldDirector.h"

class TCallbackManagedBridge;

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

	public ref class TWorldObjectEditor: public TEditor
	{
	private:

		TWorldObjectEditorPrivate* p;
		TWorldDirector^ director;

		IAbstractEditor* CreateEditorOfWorldObject(IBaluWorldObject* obj);
		void DestroyEditorOfWorldObject(IBaluWorldObject* obj);
		void CreateEditorScene();
		void DestroyEditorScene();

	public:

		TWorldObjectEditor(IntPtr handle, int width, int height, TWorldDirector^ worl_director);
		void Destroy() override;

		//bool ToolNeedObjectSelect(std::vector<IBaluWorldObject*>& selection_list);
		//void SetEditedWorldNode(TWolrdTreeNodeTag^ node);
		void SetEditedObject(int type, int index);
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

		void SetToolSelectedObject(String^ name);
	};
}
