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
	class TWorldObjectsListPrivate;

	public delegate void OnListRefreshDelegate();

	public ref class TWorldObjectsList : public TEditor
	{
	internal:
		void OnSelectObjectsTypeChange(TEditor^ sender, int type);
		void OnAfterWorldLoad();
	private:

		TWorldObjectsListPrivate* p;
		TWorldDirector^ director;
	public:
		event TNotify_ObjectList_TypeChange^ GUI_Notify_TypeChange;

		TWorldObjectsList(TWorldDirector^ world_director);
		void Destroy() override;

		int GetObjectsCount();
		String^ GetObjectName(int index);
		void SetSelectedObject(int index);
		void OnNotify_All_AfterWorldLoaded();
	};
}
