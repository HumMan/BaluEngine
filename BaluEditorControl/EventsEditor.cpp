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
	class TEventParams
	{
	public:
		TEventType event_type;
		std::vector<TWorldObjectType> params;
		std::vector<std::string> selected_params;
		TScriptData* event_data;
	};

	class TEventsEditorPrivate
	{
	public:
		IBaluWorld* world;
		std::vector<TEventParams> events;
	};
	TEventsEditor::TEventsEditor(IBaluWorld* world)
	{
		this->p = new TEventsEditorPrivate();
		this->p->world = world;
	}
	TEventsEditor::!TEventsEditor()
	{
		delete p;
	}
	array<String^>^ TEventsEditor::GetEventsList()
	{
		//p->world->GetOnMouseDown();
	}
	int TEventsEditor::GetEventsCount()
	{

	}
	array<TNodeType>^ TEventsEditor::GetEventParameters()
	{

	}
	array<String^>^ TEventsEditor::GetObjectsList(TNodeType object_type)
	{

	}
	void TEventsEditor::SetEventParameter(int event_id, String^ object_name)
	{

	}
	String^ TEventsEditor::GetEventScript(int event_id)
	{

	}
	void TEventsEditor::SetEventScript(int event_id, String^ script)
	{

	}
}