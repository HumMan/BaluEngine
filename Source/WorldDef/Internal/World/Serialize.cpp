#include "World.h"

#include <pugixml.hpp>

using namespace pugi;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

#include "WorldPrivate.h"

#include "../Material/Material.h"
#include "../Sprite/Sprite.h"
#include "../Class/Class.h"
#include "../Scene/Scene.h"

void TWorld::SaveToXML(pugi::xml_node& parent_node, const int version)const
{
	p->events_editor->SaveToXML(parent_node, version);
	xml_node new_node = parent_node.append_child("World");
	{
		xml_node materials_node = new_node.append_child("Materials");
		for (auto& i : p->world_objects[(int)TWorldObjectType::Material])
		{
			i.second->Save(materials_node, version);
		}
	}
	{
		xml_node sprites_node = new_node.append_child("Sprites");
		for (auto& i : p->world_objects[(int)TWorldObjectType::Sprite])
		{
			i.second->Save(sprites_node, version);
		}
	}
	{
		xml_node classes_node = new_node.append_child("Classes");
		for (auto& i : p->world_objects[(int)TWorldObjectType::Class])
		{
			i.second->Save(classes_node, version);
		}
	}
	{
		xml_node scenes_node = new_node.append_child("Scenes");
		for (auto& i : p->world_objects[(int)TWorldObjectType::Scene])
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

void TWorld::LoadFromXML(const pugi::xml_node& document_node, const int version)
{
	p->events_editor.reset(new TEventsEditor());
	p->events_editor->LoadFromXML(document_node, version);
	xml_node world_node = document_node.child("World");
	{
		xml_node materials_node = world_node.child("Materials");
		for (pugi::xml_node material = materials_node.first_child(); material; material = material.next_sibling())
		{
			std::string material_name = materials_node.attribute("name").as_string();
			TMaterial* new_material = new TMaterial(material_name, this);
			new_material->Load(material, version, this);
			p->world_objects[(int)TWorldObjectType::Material][new_material->GetName()].reset(new_material);
		}
	}
	//предварительно создаем классы, т.к. их имена используются в OnCollide
	{
		xml_node classes_node = world_node.child("Classes");
		for (pugi::xml_node class_node = classes_node.first_child(); class_node; class_node = class_node.next_sibling())
		{
			std::string class_name = class_node.attribute("name").as_string();
			p->world_objects[(int)TWorldObjectType::Class].emplace(class_name, std::unique_ptr<TClass>(new TClass(class_name.c_str(), this)));
		}
	}
	{
		xml_node sprites_node = world_node.child("Sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			std::string sprite_name = sprite_node.attribute("name").as_string();
			TSprite* sprite = new TSprite(sprite_name.c_str(), this);
			sprite->Load(sprite_node, version, this);
			p->world_objects[(int)TWorldObjectType::Sprite][sprite_name].reset(sprite);
		}
	}
	//загружаем классы полностью
	{
		xml_node classes_node = world_node.child("Classes");
		auto curr_class = p->world_objects[(int)TWorldObjectType::Class].begin();
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
			TScene* scene = new TScene(scene_name.c_str(), this);
			scene->Load(scene_node, version, this);
			p->world_objects[(int)TWorldObjectType::Scene][scene->GetName()].reset(scene);
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


void TWorld::SaveToXML(const std::string& path)const
{
	setlocale(LC_ALL, "C");
	xml_document doc;
	auto doc_el = doc.append_child("BaluEditorWorldFile");
	SaveToXML(doc_el, 1);
	doc.save_file(pugi::as_wide(path.c_str()).c_str());
}

void TWorld::LoadFromXML(const std::string& path)
{
	setlocale(LC_ALL, "C");
	xml_document doc;
	doc.load_file(pugi::as_wide(path.c_str()).c_str());
	LoadFromXML(doc.child("BaluEditorWorldFile"), 1);
}

IMaterial* TWorld::CreateMaterial(const char* name, const std::string& serialized)
{
	xml_document doc;
	doc.load_string(serialized.c_str());

	auto new_obj = dynamic_cast<IMaterial*>(CreateObject(TWorldObjectType::Material, name));
	new_obj->Load(doc.child("Material"),1,this);
	return new_obj;
}
ISprite* TWorld::CreateSprite(const char* name, const std::string& serialized)
{
	xml_document doc;
	doc.load_string(serialized.c_str());

	auto new_obj = dynamic_cast<ISprite*>(CreateObject(TWorldObjectType::Sprite, name));
	new_obj->Load(doc.child("Sprite"), 1, this);
	return new_obj;
}
IClass* TWorld::CreateClass(const char* name, const std::string& serialized)
{
	xml_document doc;
	doc.load_string(serialized.c_str());

	auto new_obj = dynamic_cast<IClass*>(CreateObject(TWorldObjectType::Class, name));
	new_obj->Load(doc.child("Class"), 1, this);
	return new_obj;
}
IScene* TWorld::CreateScene(const char* name, const std::string& serialized)
{
	xml_document doc;
	doc.load_string(serialized.c_str());

	auto new_obj = dynamic_cast<IScene*>(CreateObject(TWorldObjectType::Scene, name));
	new_obj->Load(doc.child("Scene"), 1, this);
	return new_obj;
}
