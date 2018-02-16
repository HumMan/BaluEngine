#include "World.h"

#include <pugixml.hpp>

using namespace pugi;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

#include "WorldPrivate.h"

typedef std::vector < std::pair<const char*, PropertyClone>> properties_registry_type;
properties_registry_type *properties_registry;

TWorld::TWorld()
{
	//p->events_editor.reset(new TEventsEditor());
}

TWorld::~TWorld()
{
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

bool TWorld::TryFind(const char* name, IWorldObject*& result)
{
	return false;
}

IWorldObject* TWorld::GetObjectByName(TWorldObjectType type,const char* name)
{
	return p->world_objects[(int)type][name].get();
}
std::vector<IWorldObject*> TWorld::GetObjects(TWorldObjectType type)
{
	return GetObjectsFromMap<IWorldObject>(p->world_objects[(int)type]);
}

bool TWorld::ObjectNameExists(TWorldObjectType type, const char* name)
{
	return false;
}
TWorldObject* TWorld::CreateObject(TWorldObjectType type, const char* name)
{
	TWorldObject* resutl = nullptr;
	//TODO заменить фабрикой
	switch (type)
	{
	case TWorldObjectType::Material:
		resutl = new TBaluMaterial(name, this);
		break;
	case TWorldObjectType::Sprite:
		resutl = new TBaluSprite(name, this);
		break;
	case TWorldObjectType::Class:
		resutl = new TClass(name, this);
		break;
	case TWorldObjectType::Scene:
		resutl = new TBaluScene(name, this);
		break;
	case TWorldObjectType::None:
		break;
	default:
		break;
	}
	p->world_objects[(int)type][name].reset(resutl);
	return resutl;
}
void TWorld::DestroyObject(TWorldObjectType type, const char* name)
{
	//world_objects[(int)type].erase(world_objects[(int)type].at(name));
}


IMaterial* TWorld::CreateMaterial(const char* name)
{
	return dynamic_cast<IMaterial*>(CreateObject(TWorldObjectType::Material, name));
}

ISprite* TWorld::CreateSprite(const char* name)
{
	return dynamic_cast<ISprite*>(CreateObject(TWorldObjectType::Sprite, name));
}

IClass* TWorld::CreateClass(const char* name)
{
	return dynamic_cast<IClass*>(CreateObject(TWorldObjectType::Class, name));
}

IScene* TWorld::CreateScene(const char* name)
{
	return dynamic_cast<IScene*>(CreateObject(TWorldObjectType::Scene, name));
}

IScene* TWorld::GetScene(const std::string& name)
{
	return dynamic_cast<IScene*>(GetObjectByName(TWorldObjectType::Scene, name.c_str()));
}
IMaterial* TWorld::GetMaterial(const std::string& name)
{
	return dynamic_cast<IMaterial*>(GetObjectByName(TWorldObjectType::Material, name.c_str()));
}
ISprite* TWorld::GetSprite(const std::string& name)
{
	return dynamic_cast<ISprite*>(GetObjectByName(TWorldObjectType::Sprite, name.c_str()));
}
IClass* TWorld::GetClass(const std::string& name)
{
	return dynamic_cast<IClass*>(GetObjectByName(TWorldObjectType::Class, name.c_str()));
}

void TWorld::SaveToXML(const std::string& path)
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

bool PropertiesFactory::Register(const char* name, PropertyClone clone)
{
	if (properties_registry == nullptr)
		properties_registry = new properties_registry_type();
	properties_registry->push_back(std::pair<const char*, PropertyClone>(name, clone));
	return true;
}

void PropertiesFactory::UnregisterAll()
{
	delete properties_registry;
}

TProperty* PropertiesFactory::Create(const char* name)
{
	for (int i = 0; i < properties_registry->size(); i++)
		if (strcmp((*properties_registry)[i].first, name) == 0)
			return (*properties_registry)[i].second();
	throw std::invalid_argument("Тип не зарегистрирован");
}

IEventsEditor* TWorld::GetEventsEditor()
{
	//return events_editor.get();
	return nullptr;
}

void TWorld::AddChangesListener(TWorldChangeListener* listener)
{
	p->listeners.AddChangesListener(listener);
}
void TWorld::RemoveChangesListener(TWorldChangeListener* listener)
{
	p->listeners.RemoveChangesListener(listener);
}