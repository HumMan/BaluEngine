#include "IWorld.h"

#include <pugixml.hpp>

using namespace pugi;
using namespace EngineInterface;
//needed for polygon from image contruction
#include <IL/ilut.h>

TBaluWorld::TBaluWorld()
{
	callback_active_type = TScriptActiveType::DEFAULT;
	ilInit();
}

TBaluWorld::~TBaluWorld()
{
	ilShutDown();
}

template<class T, class find_array>
bool TryFindT(find_array& map, const char* class_name, T*& result)
{
	auto iter = map.find(class_name);
	if (iter == map.end())
		return false;
	else
	{
		result = iter->second.get();
		return true;
	}
}

template<class T, class I, class find_array>
bool TryFindI(find_array& map, const char* class_name, I*& result)
{
	T* r;
	auto result0 = TryFindT<T>(map, class_name, r);
	result = static_cast<I*>(r);
	return result0;
}

template<class T, class M>
std::vector<T*> GetObjectsFromMap(M& map)
{
	std::vector<T*> result;
	for (auto& v : map)
	{
		result.push_back(v.second.get());
	}
	return result;
}

bool TBaluWorld::TryFind(const char* name, TBaluWorldObject*& result)
{
	return false;
}

TBaluWorldObject* TBaluWorld::GetObjectByName(const char* name)
{
	return world_objects[name].get();
}
std::vector<TBaluWorldObject*> TBaluWorld::GetObjects(TWorldObjectType type)
{
	return GetObjectsFromMap<TBaluWorldObject>(this->world_objects);
}

bool TBaluWorld::ObjectNameExists(TWorldObjectType type, const char* name)
{
	return false;
}
void TBaluWorld::CreateObject(TWorldObjectType type, const char* name)
{

}
void TBaluWorld::DestroyObject(TWorldObjectType type, const char* name)
{

}

void TBaluWorld::AddOnMouseDown(TScript callback)
{
	mouse_down_callbacks.push_back(callback);
}

void TBaluWorld::AddOnMouseUp(TScript callback)
{
	mouse_up_callbacks.push_back(callback);
}

void TBaluWorld::AddOnMouseMove(TScript callback)
{
	mouse_move_callbacks.push_back(callback);
}

std::vector<TScript>& TBaluWorld::GetOnMouseDown()
{
	return mouse_down_callbacks;
}
std::vector<TScript>& TBaluWorld::GetOnMouseUp()
{
	return mouse_up_callbacks;
}
std::vector<TScript>& TBaluWorld::GetOnMouseMove()
{
	return mouse_move_callbacks;
}

void TBaluWorld::RemoveOnMouseDown(int index)
{
	mouse_down_callbacks.erase(mouse_down_callbacks.begin() + index);
}

void TBaluWorld::RemoveOnMouseUp(int index)
{
	mouse_up_callbacks.erase(mouse_up_callbacks.begin() + index);
}

void TBaluWorld::RemoveOnMouseMove(int index)
{
	mouse_move_callbacks.erase(mouse_move_callbacks.begin() + index);
}

void TBaluWorld::AddOnWorldStart(TScript callback)
{
	on_start_world_callback.push_back(callback);
}

std::vector<TScript>& TBaluWorld::GetOnWorldStart()
{
	return on_start_world_callback;
}

void TBaluWorld::RemoveOnWorldStart(int index)
{
	on_start_world_callback.erase(on_start_world_callback.begin() + index);
}

void TBaluWorld::AddOnViewportResize(TScript callback)
{
	viewport_resize_callback.push_back(callback);
}

std::vector<TScript>& TBaluWorld::GetOnViewportResize()
{
	return viewport_resize_callback;
}

void TBaluWorld::RemoveOnViewportResize(int index)
{
	viewport_resize_callback.erase(viewport_resize_callback.begin() + index);
}

void TBaluWorld::SaveToXML(std::string path)
{
	setlocale(LC_ALL, "C");
	xml_document doc;
	auto doc_el = doc.append_child("BaluEditorWorldFile");
	SaveToXML(doc_el, 1);
	doc.save_file(pugi::as_wide(path.c_str()).c_str());
}

void TBaluWorld::LoadFromXML(std::string path)
{
	setlocale(LC_ALL, "C");
	xml_document doc;
	doc.load_file(pugi::as_wide(path.c_str()).c_str());
	LoadFromXML(doc.child("BaluEditorWorldFile"), 1);
}

std::vector < std::pair<const char*, PropertyClone>> properties_registry;

bool PropertiesFactory::Register(const char* name, PropertyClone clone)
{
	properties_registry.push_back(std::pair<const char*, PropertyClone>(name, clone));
	return true;
}

TProperty* PropertiesFactory::Create(const char* name)
{
	for (int i = 0; i < properties_registry.size(); i++)
		if (strcmp(properties_registry[i].first, name) == 0)
			return properties_registry[i].second();
	throw std::invalid_argument("Тип не зарегистрирован");
}
