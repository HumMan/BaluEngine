#include "Common.h"

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
	InitAllProperties();
	this->world = world;
	this->NameValue = name;
}

IWorld* TWorldObject::GetWorld()
{
	return world;
}

//IDirector* IDirector::CreateDirector(std::string assets_dir)
//{
//	return new TDirector(assets_dir);
//}

//void IDirector::DestroyDirector(IDirector* director, bool clear_static_data)
//{
//	delete dynamic_cast<TDirector*>(director);
//	//очистка статичных данных должна выполняться только при завершении работы
//	if (clear_static_data)
//	{
//		SceneObjectFactory::UnregisterAll();
//		SceneObjectInstanceFactory::UnregisterAll();
//		PropertiesFactory::UnregisterAll();
//		AnimDescFactory::UnregisterAll();
//		PhysShapeFactory::UnregisterAll();
//	}
//}

//IWorldInstance* CreateWorldInstance(IWorld* source, IResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message)
//{
//	return new TWorldInstance(dynamic_cast<TWorld*>(source), dynamic_cast<TResources*>(resources), assets_dir, call_scripts, compile_success, error_message);
//}

//void DestroyWorldInstance(IWorldInstance* world)
//{
//	delete dynamic_cast<TWorldInstance*>(world);
//}

///*bool CompileScripts(IWorld* source, IScriptInstance* script_instance, std::vector<std::string>& errors_list)
//{
//	return TWorldInstance::CheckScriptErrors(dynamic_cast<TWorld*>(source), dynamic_cast<TBaluScriptInstance*>(script_instance), errors_list);
//}*/

bool SceneObjectFactory::Register(const char* name, SceneObjectClone clone)
{
	if (scene_object_registry == nullptr)
		scene_object_registry = new scene_object_registry_type();
	scene_object_registry->push_back(std::pair<const char*, SceneObjectClone>(name, clone));
	return true;
}

void SceneObjectFactory::UnregisterAll()
{
	delete scene_object_registry;
}

ISceneObject* SceneObjectFactory::Create(const char* name)
{
	for (int i = 0; i < scene_object_registry->size(); i++)
		if (strcmp((*scene_object_registry)[i].first, name) == 0)
			return (*scene_object_registry)[i].second();
	throw std::invalid_argument("Тип не зарегистрирован");
}



