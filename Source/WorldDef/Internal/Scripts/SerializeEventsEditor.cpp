#include "IEventsEditor.h"

#include <Common/SerializeCommon.h>

using namespace EngineInterface;

void TEventsEditor::SaveToXML(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Events");
	{
		xml_node callbacks_node = new_node.append_child("GlobalMouseDownScripts");
		for (auto& v : global_mouse_down_callbacks)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
	{
		xml_node callbacks_node = new_node.append_child("GlobalMouseUpScripts");
		for (auto& v : global_mouse_up_callbacks)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
	{
		xml_node callbacks_node = new_node.append_child("GlobalMouseMoveScripts");
		for (auto& v : global_mouse_move_callbacks)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
	{
		xml_node callbacks_node = new_node.append_child("StartWorldScripts");
		for (auto& v : on_start_world_callback)
		{
			v.SaveToXML(callbacks_node, version);
		}
		callbacks_node = new_node.append_child("ViewportResizeScripts");
		for (auto& v : viewport_resize_callback)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
}

void TEventsEditor::LoadFromXML(const pugi::xml_node& document_node, const int version)
{
	xml_node world_node = document_node.child("Events");
	{
		xml_node callbacks_node = world_node.child("GlobalMouseDownScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TScript new_callback;
			new_callback.LoadFromXML(callback_node, version);
			global_mouse_down_callbacks.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("GlobalMouseUpScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TScript new_callback;
			new_callback.LoadFromXML(callback_node, version);
			global_mouse_up_callbacks.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("GlobalMouseMoveScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TScript new_callback;
			new_callback.LoadFromXML(callback_node, version);
			global_mouse_move_callbacks.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("StartWorldScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TScript new_callback;
			new_callback.LoadFromXML(callback_node, version);
			on_start_world_callback.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("ViewportResizeScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TScript new_callback;
			new_callback.LoadFromXML(callback_node, version);
			viewport_resize_callback.push_back(new_callback);
		}
	}
}

