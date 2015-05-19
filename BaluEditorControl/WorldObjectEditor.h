#pragma once

#include <vector>

class TCallbackManagedBridge;

namespace EngineInterface
{
	class IBaluWorldObject;
	class IBaluWorld;
	class IAbstractEditor;
}

class TWorldObjectEditorPrivate;

namespace Editor
{
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
	using namespace System::Threading;
	using namespace System::Collections::Generic;

	using namespace EngineInterface;

	public ref class TWorldObjectEditor
	{
	internal:

		TWorldObjectEditorPrivate* p;

		IAbstractEditor* CreateEditorOfWorldObject(IBaluWorldObject* obj);
		void DestroyEditorOfWorldObject(IBaluWorldObject* obj);
		void CreateEditorScene();
		void DestroyEditorScene();

		TWorldObjectEditor(int handle, IBaluWorld* world, const char* assets_dir);

		void Destroy();
	public:

		bool ToolNeedObjectSelect(std::vector<IBaluWorldObject*>& selection_list);

		void Resize(int width, int height);

		void MouseDown(MouseEventArgs^ e) ;
		void MouseMove(MouseEventArgs^ e) ;
		void MouseUp(MouseEventArgs^ e) ;
		void MouseWheel(MouseEventArgs^ e) ;

		void Render();

		//void SetSelectedWorldNode(TWolrdTreeNodeTag^ node);
		//void SetEditedWorldNode(TWolrdTreeNodeTag^ node);

		bool CanSetSelectedAsWork();
		void SetSelectedAsWork();

		bool CanEndSelectedAsWork();
		void EndSelectedAsWork();

		void SetToolSelectedObject(String^ name);
	};
}
