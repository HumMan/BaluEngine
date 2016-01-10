#include "IWorld.h"

#include <pugixml.hpp>

using namespace pugi;
using namespace EngineInterface;
//needed for polygon from image contruction
#include <IL/ilut.h>

#include "../Source/WorldObjects/Material/IMaterial.h"
#include "../Source/WorldObjects/Sprite/ISprite.h"
#include "../Source/WorldObjects/Class/IClass.h"
#include "../Source/WorldObjects/Scene/IScene.h"

#include "IEventsEditor.h"

TBaluWorld::TBaluWorld()
{
	ilInit();
	events_editor.reset(new TEventsEditor());
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

bool TBaluWorld::TryFind(const char* name, IBaluWorldObject*& result)
{
	return false;
}

IBaluWorldObject* TBaluWorld::GetObjectByName(TWorldObjectType type,const char* name)
{
	return world_objects[(int)type][name].get();
}
std::vector<IBaluWorldObject*> TBaluWorld::GetObjects(TWorldObjectType type)
{
	return GetObjectsFromMap<IBaluWorldObject>(this->world_objects[(int)type]);
}

bool TBaluWorld::ObjectNameExists(TWorldObjectType type, const char* name)
{
	return false;
}
TBaluWorldObject* TBaluWorld::CreateObject(TWorldObjectType type, const char* name)
{
	TBaluWorldObject* resutl = nullptr;
	//TODO �������� ��������
	switch (type)
	{
	case EngineInterface::TWorldObjectType::Material:
		resutl = new TBaluMaterial(name, this);
		break;
	case EngineInterface::TWorldObjectType::Sprite:
		resutl = new TBaluSprite(name, this);
		break;
	case EngineInterface::TWorldObjectType::Class:
		resutl = new TBaluClass(name, this);
		break;
	case EngineInterface::TWorldObjectType::Scene:
		resutl = new TBaluScene(name, this);
		break;
	case EngineInterface::TWorldObjectType::None:
		break;
	default:
		break;
	}
	world_objects[(int)type][name].reset(resutl);
	return resutl;
}
void TBaluWorld::DestroyObject(TWorldObjectType type, const char* name)
{
	//world_objects[(int)type].erase(world_objects[(int)type].at(name));
}


IBaluMaterial* TBaluWorld::CreateMaterial(const char* name)
{
	return dynamic_cast<IBaluMaterial*>(CreateObject(TWorldObjectType::Material, name));
}

IBaluSprite* TBaluWorld::CreateSprite(const char* name)
{
	return dynamic_cast<IBaluSprite*>(CreateObject(TWorldObjectType::Sprite, name));
}

IBaluClass* TBaluWorld::CreateClass(const char* name)
{
	return dynamic_cast<IBaluClass*>(CreateObject(TWorldObjectType::Class, name));
}

IBaluScene* TBaluWorld::CreateScene(const char* name)
{
	return dynamic_cast<IBaluScene*>(CreateObject(TWorldObjectType::Scene, name));
}

IBaluScene* TBaluWorld::GetScene(const std::string& name)
{
	return dynamic_cast<IBaluScene*>(GetObjectByName(TWorldObjectType::Scene, name.c_str()));
}
IBaluMaterial* TBaluWorld::GetMaterial(const std::string& name)
{
	return dynamic_cast<IBaluMaterial*>(GetObjectByName(TWorldObjectType::Material, name.c_str()));
}
IBaluSprite* TBaluWorld::GetSprite(const std::string& name)
{
	return dynamic_cast<IBaluSprite*>(GetObjectByName(TWorldObjectType::Sprite, name.c_str()));
}
IBaluClass* TBaluWorld::GetClass(const std::string& name)
{
	return dynamic_cast<IBaluClass*>(GetObjectByName(TWorldObjectType::Class, name.c_str()));
}

void TBaluWorld::SaveToXML(const std::string& path)
{
	setlocale(LC_ALL, "C");
	xml_document doc;
	auto doc_el = doc.append_child("BaluEditorWorldFile");
	SaveToXML(doc_el, 1);
	doc.save_file(pugi::as_wide(path.c_str()).c_str());
}

void TBaluWorld::LoadFromXML(const std::string& path)
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
	throw std::invalid_argument("��� �� ���������������");
}

IEventsEditor* TBaluWorld::GetEventsEditor()
{
	return events_editor.get();
}

void TBaluWorld::AddChangesListener(TBaluWorldChangeListener* listener)
{
	listeners.AddChangesListener(listener);
}
void TBaluWorld::RemoveChangesListener(TBaluWorldChangeListener* listener)
{
	listeners.RemoveChangesListener(listener);
}