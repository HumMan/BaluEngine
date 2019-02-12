#include "Common.h"

#include "RuntimeProperties.h"

#include <algorithm>

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

typedef std::vector < std::pair<const char*, SceneObjectClone>> scene_object_registry_type;
scene_object_registry_type *scene_object_registry = nullptr;


//void TWorldObject::SetName(const std::string& name)
//{
//	assert(!world->ObjectNameExists(TWorldObjectType::Material, name.c_str()));
//	this->name = name;
//}
//
//std::string TWorldObject::GetName()
//{
//	return name;
//}

TWorldObject::TWorldObject(IWorld* world, std::string name)
{
	runtime_properties.reset(new TRuntimeProperties());
	InitAllProperties();
	this->world = world;
	this->NameValue = name;
}

IWorld* TWorldObject::GetWorld()
{
	return world;
}


///*bool CompileScripts(IWorld* source, IScriptInstance* script_instance, std::vector<std::string>& errors_list)
//{
//	return TWorldInstance::CheckScriptErrors(dynamic_cast<TWorld*>(source), dynamic_cast<TBaluScriptInstance*>(script_instance), errors_list);
//}*/

bool SceneObjectFactory::Register(const char* name, SceneObjectClone clone)
{
	if (scene_object_registry == nullptr)
		scene_object_registry = new scene_object_registry_type();

	auto iter = std::find_if(scene_object_registry->begin(), scene_object_registry->end(),
		[&](std::pair<const char*, SceneObjectClone>& p) {return p.first == name; });
	if (iter == scene_object_registry->end())
	{
		scene_object_registry->push_back(std::pair<const char*, SceneObjectClone>(name, clone));		
	}
	return true;
}

void SceneObjectFactory::UnregisterAll()
{
	delete scene_object_registry;
}

ISceneObject* SceneObjectFactory::Create(const char* name, TScene* scene)
{
	for (int i = 0; i < scene_object_registry->size(); i++)
		if (strcmp((*scene_object_registry)[i].first, name) == 0)
			return (*scene_object_registry)[i].second(scene);
	throw std::invalid_argument("Тип не зарегистрирован");
}



