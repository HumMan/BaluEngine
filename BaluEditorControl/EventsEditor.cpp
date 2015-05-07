#include "BaluEditorControl.h"

#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Source/PropertiesRegistry/propertiesRegistry.h"

using namespace EngineInterface;

#include "../Example/DemoWorld.h"

namespace Editor
{
	class TEventInfo
	{
	public:
		TEventType event_type;
		std::vector<TWorldObjectType> params;
		std::vector<std::string> selected_params;
		TScriptData* event_data;
	};

	class TEventsOfType
	{
	public:
		std::vector<TEventInfo> events;
		TEventsOfType()
		{
		}
	};

	class TEventsEditorPrivate
	{
	public:
		IBaluWorld* world;
		std::vector<TEventsOfType> events;
	};
	TEventsEditor::TEventsEditor(IBaluWorld* world)
	{
		this->p = new TEventsEditorPrivate();
		this->p->world = world;
	}
	void TEventsEditor::FindAllEvents()
	{
		p->events.resize((int)TEventType::End);
		p->events[(int)TEventType::OnWorldStart].insert(p->world->GetOnWorldStart()
	}
	TEventsEditor::!TEventsEditor()
	{
		delete p;
	}
	array<String^>^ TEventsEditor::GetEventsList(int event_type)
	{
		p->world->GetOnMouseDown();
	}
	int TEventsEditor::GetEventsCount(int event_type)
	{

	}
	array<TNodeType>^ TEventsEditor::GetEventParameters(int event_type, int event_id)
	{

	}
	array<String^>^ TEventsEditor::GetObjectsList(TNodeType object_type)
	{

	}
	void TEventsEditor::SetEventParameter(int event_type, int event_id, String^ object_name)
	{

	}
	String^ TEventsEditor::GetEventScript(int event_type, int event_id)
	{

	}
	void TEventsEditor::SetEventScript(int event_type, int event_id, String^ script)
	{

	}
}