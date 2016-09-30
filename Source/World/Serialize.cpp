#include "IWorld.h"

#include <Common/SerializeCommon.h>

#include "../Source/WorldObjects/Material/IMaterial.h"
#include "../Source/WorldObjects/Sprite/ISprite.h"
#include "../Source/WorldObjects/Class/IClass.h"
#include "../Source/WorldObjects/Scene/IScene.h"
#include "../Source/Scripts/IEventsEditor.h"

using namespace EngineInterface;

void TProperties::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node props_node = parent_node.append_child("Properties");
	for (auto& v : properties)
	{
		v.second->Save(props_node, version);
		props_node.last_child().append_attribute("name").set_value(v.first.c_str());
	}
}

void TProperties::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
{
	xml_node props_node = instance_node.child("Properties");
	for (pugi::xml_node prop_node = props_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		auto new_prop = PropertiesFactory::Create(prop_node.attribute("type").as_string());
		new_prop->Load(prop_node, version, world);
		auto name = prop_node.attribute("name").as_string();
		properties[name].reset(new_prop);
	}
}


void TBaluWorld::SaveToXML(pugi::xml_node& parent_node, const int version)
{
	this->events_editor->SaveToXML(parent_node, version);
	xml_node new_node = parent_node.append_child("World");
	{
		xml_node materials_node = new_node.append_child("Materials");
		for (auto& i : world_objects[(int)TWorldObjectType::Material])
		{
			i.second->Save(materials_node, version);
		}
	}
	{
		xml_node sprites_node = new_node.append_child("Sprites");
		for (auto& i : world_objects[(int)TWorldObjectType::Sprite])
		{
			i.second->Save(sprites_node, version);
		}
	}
	{
		xml_node classes_node = new_node.append_child("Classes");
		for (auto& i : world_objects[(int)TWorldObjectType::Class])
		{
			i.second->Save(classes_node, version);
		}
	}
	{
		xml_node scenes_node = new_node.append_child("Scenes");
		for (auto& i : world_objects[(int)TWorldObjectType::Scene])
		{
			i.second->Save(scenes_node, version);
		}
	}

	/*{
		xml_node callbacks_node = new_node.append_child("MouseDownScripts");
		for (auto& v : mouse_down_callbacks)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
	{
		xml_node callbacks_node = new_node.append_child("MouseUpScripts");
		for (auto& v : mouse_up_callbacks)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
	{
		xml_node callbacks_node = new_node.append_child("MouseMoveScripts");
		for (auto& v : mouse_move_callbacks)
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
	}*/
}

void TBaluWorld::LoadFromXML(const pugi::xml_node& document_node, const int version)
{
	this->events_editor.reset(new TEventsEditor());
	this->events_editor->LoadFromXML(document_node, version);
	xml_node world_node = document_node.child("World");
	{
		xml_node materials_node = world_node.child("Materials");
		for (pugi::xml_node material = materials_node.first_child(); material; material = material.next_sibling())
		{
			std::string material_name = materials_node.attribute("name").as_string();
			TBaluMaterial* new_material = new TBaluMaterial(material_name, this);
			new_material->Load(material, version, this);
			world_objects[(int)TWorldObjectType::Material][new_material->GetName()].reset(new_material);
		}
	}
	//предварительно создаем классы, т.к. их имена используются в OnCollide
	{
		xml_node classes_node = world_node.child("Classes");
		for (pugi::xml_node class_node = classes_node.first_child(); class_node; class_node = class_node.next_sibling())
		{
			std::string class_name = class_node.attribute("name").as_string();
			world_objects[(int)TWorldObjectType::Class].emplace(class_name, std::unique_ptr<TBaluClass>(new TBaluClass(class_name.c_str(), this)));
		}
	}
	{
		xml_node sprites_node = world_node.child("Sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			std::string sprite_name = sprite_node.attribute("name").as_string();
			TBaluSprite* sprite = new TBaluSprite(sprite_name.c_str(), this);
			sprite->Load(sprite_node, version, this);
			world_objects[(int)TWorldObjectType::Sprite][sprite_name].reset(sprite);
		}
	}
	//загружаем классы полностью
	{
		xml_node classes_node = world_node.child("Classes");
		auto curr_class = world_objects[(int)TWorldObjectType::Class].begin();
		for (pugi::xml_node class_node = classes_node.first_child(); class_node; class_node = class_node.next_sibling())
		{
			curr_class->second->Load(class_node, version, this);
			curr_class++;
		}
	}
	{
		xml_node scenes_node = world_node.child("Scenes");
		for (pugi::xml_node scene_node = scenes_node.first_child(); scene_node; scene_node = scene_node.next_sibling())
		{
			std::string scene_name = scenes_node.attribute("name").as_string();
			TBaluScene* scene = new TBaluScene(scene_name.c_str(), this);
			scene->Load(scene_node, version, this);
			world_objects[(int)TWorldObjectType::Scene][scene->GetName()].reset(scene);
		}
	}

	/*{
		xml_node callbacks_node = world_node.child("MouseDownScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TScript new_callback;
			new_callback.LoadFromXML(callback_node, version);
			mouse_down_callbacks.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("MouseUpScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TScript new_callback;
			new_callback.LoadFromXML(callback_node, version);
			mouse_up_callbacks.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("MouseMoveScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TScript new_callback;
			new_callback.LoadFromXML(callback_node, version);
			mouse_move_callbacks.push_back(new_callback);
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
	}*/
}

void TScript::SaveToXML(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Script");

	xml_node ndAvatarData = new_node.append_child(pugi::node_pcdata);
	ndAvatarData.set_value(script_source.c_str());
}

void TScript::LoadFromXML(const pugi::xml_node& document_node, const int version)
{
	script_source = document_node.child_value();
}
