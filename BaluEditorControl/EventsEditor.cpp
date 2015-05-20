#include "EventsEditor.h"

#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

#include "Converters.h"

using namespace EngineInterface;

namespace Editor
{
	enum class TEventParamType
	{
		WorldObject,
		Key,
		None
	};

	class TEventParam
	{
	public:
		TEventParamType param_type;
		TWorldObjectType obj_type;
		std::string selected_obj_name;
		TKey key;
		TEventParam()
		{
			param_type = TEventParamType::None;
		}
		TEventParam(TWorldObjectType obj_type, std::string selected_obj_name)
		{
			param_type = TEventParamType::WorldObject;
			this->obj_type = obj_type;
			this->selected_obj_name = selected_obj_name;
		}
		TEventParam(TKey key)
		{
			param_type = TEventParamType::Key;
			this->key = key;
		}
	};
	class TEventInfo
	{
	public:
		TEventType event_type;
		std::vector<TEventParam> params;
		TScriptData* event_data;
		TEventInfo(TEventType event_type, std::vector<TEventParam> params, TScriptData* event_data)
		{
			this->event_type = event_type;
			this->params = params;
			this->event_data = event_data;
		}
	};

	class TEventsOfType
	{
	public:
		std::vector<TEventInfo> events;
	};

	class TEventsEditorPrivate
	{
	public:
		IBaluWorld* world;
		std::string assets_dir;
		TEventsOfType event_types[(int)TEventType::End];
	};

	TEventsEditor::TEventsEditor(TWorldDirector^ director)
	{
		director->RegisterEditor(this);

		this->p = new TEventsEditorPrivate();
		this->p->world = director->GetWorld();
		this->p->assets_dir = Converters::FromClrString(director->GetAssetsDir());
	}
	void TEventsEditor::Initialize()
	{
		Clear();
		FindAllEvents();
	}
	bool TEventsEditor::CompileScripts(array<String^>^% errors_list)
	{
		std::vector<std::string> errors;
		auto script_engine = EngineInterface::CreateScriptInstance(p->assets_dir);
		bool result = EngineInterface::CompileScripts(p->world, script_engine, errors);
		EngineInterface::DestroyScriptInstance(script_engine);
		array<String^>::Resize(errors_list, errors.size());
		int i = 0;
		for (auto& v : errors)
		{
			errors_list[i] = gcnew String(v.c_str());
			i++;
		}
		return result;
	}
	void TEventsEditor::Clear()
	{
		for (int i = 0; i < (int)TEventType::End; i++)
		{
			p->event_types[i].events.clear();
		}
	}
	void TEventsEditor::FindAllEvents()
	{
		for (auto& e : p->world->GetOnWorldStart())
		{
			p->event_types[(int)TEventType::OnWorldStart].events.push_back(TEventInfo(TEventType::OnWorldStart, std::vector<TEventParam>(), &e));
		}
		for (auto& e : p->world->GetOnViewportResize())
		{
			p->event_types[(int)TEventType::OnViewportResize].events.push_back(TEventInfo(TEventType::OnViewportResize, std::vector<TEventParam>(),  &e));
		}
		for (auto& e : p->world->GetOnMouseDown())
		{
			p->event_types[(int)TEventType::OnGlobalMouseDown].events.push_back(TEventInfo(TEventType::OnGlobalMouseDown, std::vector<TEventParam>(),  &e));
		}
		for (auto& e : p->world->GetOnMouseUp())
		{
			p->event_types[(int)TEventType::OnGlobalMouseUp].events.push_back(TEventInfo(TEventType::OnGlobalMouseUp, std::vector<TEventParam>(), &e));
		}
		for (auto& e : p->world->GetOnMouseMove())
		{
			p->event_types[(int)TEventType::OnGlobalMouseMove].events.push_back(TEventInfo(TEventType::OnGlobalMouseMove, std::vector<TEventParam>(),  &e));
		}
		for (auto& some_class : p->world->GetClasses())
		{
			for (auto& e : some_class.second->GetOnBeforePhysicsStep())
			{
				std::vector<TEventParam> params;
				params.push_back(TEventParam(TWorldObjectType::Class, some_class.second->GetName()));
				p->event_types[(int)TEventType::OnClassBeforePhys].events.push_back(TEventInfo(TEventType::OnClassBeforePhys, params, &e));
			}
		}
		for (auto& some_class : p->world->GetClasses())
		{
			for (auto& e : some_class.second->GetOnKeyDown())
			{
				std::vector<TEventParam> params;
				params.push_back(TEventParam(TWorldObjectType::Class, some_class.second->GetName()));
				params.push_back(TEventParam(e.first));
				for (auto& key_event : e.second)
				{
					p->event_types[(int)TEventType::OnClassKeyDown].events.push_back(TEventInfo(TEventType::OnClassKeyDown, params, &key_event));
				}
			}
		}
		for (auto& some_class : p->world->GetClasses())
		{
			for (auto& e : some_class.second->GetOnKeyUp())
			{
				std::vector<TEventParam> params;
				params.push_back(TEventParam(TWorldObjectType::Class, some_class.second->GetName()));
				params.push_back(TEventParam(e.first));
				for (auto& key_event : e.second)
				{
					p->event_types[(int)TEventType::OnClassKeyUp].events.push_back(TEventInfo(TEventType::OnClassKeyUp, params, &key_event));
				}
			}
		}
		for (auto& some_class : p->world->GetClasses())
		{
			for (int i = 0; i < some_class.second->GetSpritesCount(); i++)
			{
				auto some_sprite = some_class.second->GetSprite(i)->GetSprite();
				for (auto& some_sprite_event : some_sprite->GetOnCollide())
				{
					std::vector<TEventParam> params;
					params.push_back(TEventParam(TWorldObjectType::Class, some_sprite_event.first->GetName()));
					params.push_back(TEventParam(TWorldObjectType::Sprite, some_sprite->GetName()));
					p->event_types[(int)TEventType::OnSpriteCollide].events.push_back(TEventInfo(TEventType::OnSpriteCollide, params, &some_sprite_event.second));
				}
			}
		}
	}
	void TEventsEditor::Destroy()
	{
		delete p;
	}

	int TEventsEditor::GetEventsCount(int event_type)
	{
		return p->event_types[event_type].events.size();
	}
	array<int>^ TEventsEditor::GetEventParameters(int event_type, int event_id)
	{
		return nullptr;
	}

	String^ TEventsEditor::GetEventSignature(int event_type, int event_id)
	{
		return nullptr;
	}

	array<String^>^ TEventsEditor::GetEventParameterVariants(int object_type)
	{
		return nullptr;
	}
	void TEventsEditor::SetEventParameter(int event_type, int event_id, String^ object_name)
	{

	}
	String^ TEventsEditor::GetEventScript(int event_type, int event_id)
	{
		return gcnew String(p->event_types[event_type].events[event_id].event_data->GetScriptSource().c_str());
	}
	void TEventsEditor::SetEventScript(int event_type, int event_id, String^ script)
	{
		p->event_types[event_type].events[event_id].event_data->SetScriptSource(Converters::FromClrString(script).c_str());
	}
	int TEventsEditor::GetEventTypesCount()
	{
		return (int)TEventType::End;
	}
	String^ TEventsEditor::GetEventTypeName(int event_type)
	{
		return gcnew String(TEventTypeString::Get((TEventType)event_type));
	}
	int TEventsEditor::EventTypeFromName(String^ name)
	{
		auto s = Converters::FromClrString(name);
		return (int)TEventTypeString::From(s.c_str());
	}

	void TEventsEditor::CreateEvent(int event_type)
	{

	}
	void TEventsEditor::DestroyEvent(int event_type, int event_id)
	{

	}
	void TEventsEditor::MoveEvent(int event_type, int from_id, int to_id, bool before)
	{

	}
}