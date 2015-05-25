#pragma once

#include <vector>

#include "WorldDirector.h"

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
	class TPropertiesEditorPrivate;

	public ref class TPropertiesEditor: public TEditor
	{
	private:

		TPropertiesEditorPrivate* p;

	public:

		TPropertiesEditor(IntPtr handle, TWorldDirector world_director);
		void Destroy() override;

	};
}
