#include "EventsEditor.h"

#include <pugixml.hpp>

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace pugi;

void TSpriteWithClassCollide::SaveToXML(pugi::xml_node& parent_node, const int version)
{
	auto node = parent_node.append_child("Event");
	node.append_attribute("source_class").set_value(source_class.c_str());
	node.append_attribute("source_sprite_id").set_value(source_sprite_id);
	node.append_attribute("with_class").set_value(with_class.c_str());
	node.set_value(script.c_str());
}
void TSpriteWithClassCollide::LoadFromXML(const pugi::xml_node& instance_node, const int version)
{
	source_class = instance_node.attribute("source_class").as_string();
	source_sprite_id = instance_node.attribute("source_sprite_id").as_int();
	with_class = instance_node.attribute("with_class").as_string();
	script = instance_node.value();
}

void TEventsEditor::SaveToXML(pugi::xml_node& parent_node, const int version)
{
	xml_node events_node = parent_node.append_child("Events");
	{
		{
			xml_node callbacks_node = events_node.append_child("Global");
			for (int i = 0; i < (int)GlobalCallbackType::Count; i++)
			{
				auto& v = global[i];
				xml_node node = callbacks_node.append_child("Type");
				node.append_attribute("id").set_value(i);
				for (auto& script : v)
				{
					node.append_child("Event").set_value(script.c_str());
				}
			}
		}
		{
			xml_node callbacks_node = events_node.append_child("GlobalKey");
			for (int i = 0; i < (int)GlobalKeyCallbackType::Count; i++)
			{
				auto& v = global_key[i];
				xml_node node = callbacks_node.append_child("Type");
				node.append_attribute("id").set_value(i);
				for (auto& script : v)
				{
					auto event_node = node.append_child("Event");
					event_node.append_attribute("key").set_value(std::get<0>(script));
					event_node.set_value(std::get<1>(script).c_str());
				}
			}
		}
		{
			xml_node callbacks_node = events_node.append_child("ClassKey");
			for (int i = 0; i < (int)ClassKeyCallbackType::Count; i++)
			{
				auto& v = class_key[i];
				xml_node node = callbacks_node.append_child("Type");
				node.append_attribute("id").set_value(i);
				for (auto& script : v)
				{
					auto event_node = node.append_child("Event");
					event_node.append_attribute("key").set_value(std::get<0>(script));
					event_node.append_attribute("class").set_value(std::get<2>(script).c_str());
					event_node.set_value(std::get<1>(script).c_str());
				}
			}
		}
		{
			xml_node callbacks_node = events_node.append_child("Class");
			for (int i = 0; i < (int)ClassCallbackType::Count; i++)
			{
				auto& v = class_callbacks[i];
				xml_node node = callbacks_node.append_child("Type");
				node.append_attribute("id").set_value(i);
				for (auto& script : v)
				{
					auto event_node = node.append_child("Event");
					event_node.append_attribute("class").set_value(std::get<1>(script).c_str());
					event_node.set_value(std::get<0>(script).c_str());
				}
			}
		}
		{
			xml_node callbacks_node = events_node.append_child("Collide");
			{
				for (auto& script : on_collide)
				{
					script.SaveToXML(callbacks_node, version);
				}
			}
		}
	}
}

void TEventsEditor::LoadFromXML(const pugi::xml_node& document_node, const int version)
{
	xml_node events_node = document_node.child("Events");
	{
		//for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			xml_node callbacks_node = events_node.child("Global");
			for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
			{
				int id = callback_node.attribute("id").as_int();
				global[id].push_back(callback_node.child("Event").value());
			}
		}
		{
			xml_node callbacks_node = events_node.child("GlobalKey");
			for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
			{
				int id = callback_node.attribute("id").as_int();
				auto node = callback_node.child("Event");
				global_key[id].push_back(std::tuple<TKey, TScript>((TKey)node.attribute("key").as_int(),node.value()));
			}
		}
		{
			xml_node callbacks_node = events_node.child("ClassKey");
			for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
			{
				int id = callback_node.attribute("id").as_int();
				auto node = callback_node.child("Event");
				class_key[id].push_back(std::tuple<TKey, TScript, std::string>(
					(TKey)node.attribute("key").as_int(), 
					node.value(),
					node.attribute("class").as_string()
				));
			}
		}
		{
			xml_node callbacks_node = events_node.child("Class");
			for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
			{
				int id = callback_node.attribute("id").as_int();
				auto node = callback_node.child("Event");
				class_callbacks[id].push_back(std::tuple<TScript, std::string>(
					node.value(),
					node.attribute("class").as_string()
				));
			}
		}
		{
			xml_node callbacks_node = events_node.child("Collide");
			for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
			{
				on_collide.push_back(TSpriteWithClassCollide());
				on_collide.back().LoadFromXML(callback_node, version);
			}
		}
	}
}

