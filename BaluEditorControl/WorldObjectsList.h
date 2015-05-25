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
		void OnSelectObjectsTypeChange(TEditor^ sender, int type)override;
		//void OnObjectListSelectionChange(TEditor^ sender, int type, int index)override;
		void OnAfterWorldLoad()override;
	private:

		TWorldObjectsListPrivate* p;
		TWorldDirector^ director;
	public:
		TWorldObjectsList(TWorldDirector^ world_director);
		void Destroy() override;

		int GetObjectsCount();
		String^ GetObjectName(int index);
		void SetSelectedObject(int index);
	};
}
