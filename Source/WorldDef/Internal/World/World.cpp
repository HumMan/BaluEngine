#include "World.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

#include "WorldPrivate.h"

#include "../Scene/Scene.h"
#include "../Class/Class.h"
#include "../Sprite/Sprite.h"
#include "../Material/Material.h"

TWorld::TWorld()
{
	p.reset(new TWorld::TPrivate());
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
	switch (type)
	{
	case TWorldObjectType::Material:
		resutl = new TMaterial(name, this);
		break;
	case TWorldObjectType::Sprite:
		resutl = new TSprite(name, this);
		break;
	case TWorldObjectType::Class:
		resutl = new TClass(name, this);
		break;
	case TWorldObjectType::Scene:
		resutl = new TScene(name, this);
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
	throw std::runtime_error("not realized");
	//p->world_objects[(int)type].erase(p->world_objects[(int)type].at(name));
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


IEventsEditor* TWorld::GetEventsEditor()
{
	return p->events_editor.get();
}

ICommandList* TWorld::GetCommandList()
{
	return p->command_list.get();
}

IWorld* WorldDef::CreateWorld()
{
	return (new TWorld());
}

void WorldDef::DestroyWorld(IWorld* world)
{
	delete dynamic_cast<TWorld*>(world);
}

void WorldDef::UnregisterAll()
{
	SceneObjectFactory::UnregisterAll();
	RuntimePropertiesFactory::UnregisterAll();
	AnimDescFactory::UnregisterAll();
	PhysShapeFactory::UnregisterAll();
}