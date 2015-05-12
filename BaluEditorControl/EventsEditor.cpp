#include "BaluEditorControl.h"

#include <vcclr.h>
#include <msclr\marshal_cppstd.h>

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Source/PropertiesRegistry/propertiesRegistry.h"

using namespace EngineInterface;

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
		TEventsOfType event_types[(int)TEventType::End];
	};
	TEventsEditor::TEventsEditor(IBaluWorld* world)
	{
		this->p = new TEventsEditorPrivate();
		this->p->world = world;
	}
	void TEventsEditor::FindAllEvents()
	{
		//p->events.resize((int)TEventType::End);
		//p->events[(int)TEventType::OnWorldStart].insert(p->world->GetOnWorldStart()
	}
	TEventsEditor::!TEventsEditor()
	{
		delete p;
	}
	array<String^>^ TEventsEditor::GetEventsList(int event_type)
	{
		//p->world->GetOnMouseDown();
		return nullptr;
	}
	int TEventsEditor::GetEventsCount(int event_type)
	{
		return p->event_types->events.size();
	}
	array<TNodeType>^ TEventsEditor::GetEventParameters(int event_type, int event_id)
	{
		return nullptr;
	}
	array<String^>^ TEventsEditor::GetObjectsList(TNodeType object_type)
	{
		return nullptr;
	}
	void TEventsEditor::SetEventParameter(int event_type, int event_id, String^ object_name)
	{

	}
	String^ TEventsEditor::GetEventScript(int event_type, int event_id)
	{
		return nullptr;
	}
	void TEventsEditor::SetEventScript(int event_type, int event_id, String^ script)
	{

	}
	int TEventsEditor::GetEventTypesCount()
	{
		return (int)TEventType::End;
	}
	String^ TEventsEditor::GetEventTypeName(int event_type)
	{
		return nullptr;
	}
}