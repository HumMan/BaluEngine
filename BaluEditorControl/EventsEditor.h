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
	using namespace System::Diagnostics;
	using namespace System::Windows::Forms;
	using namespace System::ComponentModel;
	using namespace System::Threading;
	using namespace System::Collections::Generic;

	using namespace EngineInterface;

	class TEventsEditorPrivate;

	public ref class TEventsEditor:public TEditor
	{
	internal:
		TWorldDirector^ director;
		TEventsEditorPrivate* p;
		
		void FindAllEvents();
		void Clear();
	public:

		TEventsEditor(TWorldDirector^ world);

		bool TEventsEditor::CompileScripts(array<String^>^% errors_list);
		void Initialize();
		void Destroy() override;

		int GetEventsCount(int event_type);
		array<int>^ GetEventParameters(int event_type, int event_id);
		String^ GetEventSignature(int event_type, int event_id);
		array<String^>^ GetEventParameterVariants(int object_type);
		void SetEventParameter(int event_type, int event_id, String^ object_name);

		String^ GetEventScript(int event_type, int event_id);
		void SetEventScript(int event_type, int event_id, String^ script);

		int GetEventTypesCount();
		String^ GetEventTypeName(int event_type);
		int EventTypeFromName(String^ name);

		void CreateEvent(int event_type);
		void DestroyEvent(int event_type, int event_id);
		void MoveEvent(int event_type, int from_id, int to_id, bool before);
	};

}
