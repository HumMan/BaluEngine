#pragma once

#include <vector>
#include "Common.h"

class TCallbackManagedBridge;

namespace EngineInterface
{
	class IBaluWorldObject;
	class IBaluWorld;
	class IAbstractEditor;
}

class BaluEditorControlPrivate;
class BaluEditorOpenglWindowPrivate;

namespace Editor
{
	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
	using namespace System::Threading;
	using namespace System::Collections::Generic;

	using namespace EngineInterface;

	class TEventsEditorPrivate;

	public ref class TEventsEditor
	{
	internal:
		TEventsEditorPrivate* p;
		TEventsEditor(IBaluWorld* world, const char* assets_dir);
		void FindAllEvents();
		void Clear();
	public:
		bool TEventsEditor::CompileScripts(array<String^>^% errors_list);
		void Initialize();
		!TEventsEditor();

		int GetEventsCount(int event_type);
		array<TNodeType>^ GetEventParameters(int event_type, int event_id);
		array<String^>^ GetObjectsList(TNodeType object_type);
		void SetEventParameter(int event_type, int event_id, String^ object_name);

		String^ GetEventScript(int event_type, int event_id);
		void SetEventScript(int event_type, int event_id, String^ script);

		int GetEventTypesCount();
		String^ GetEventTypeName(int event_type);
		int EventTypeFromName(String^ name);
	};

}
