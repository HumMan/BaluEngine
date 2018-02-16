#include "ICommon.h"

#include <WorldDef/IWorld.h>

#include <Common/IDirector.h>
#include <WorldInstance/IWorldInstance.h>


using namespace EngineInterface;

typedef std::vector < std::pair<const char*, SceneObjectClone>> scene_object_registry_type;
scene_object_registry_type *scene_object_registry = nullptr;

typedef std::vector < std::pair<const char*, SceneObjectInstanceClone>> scene_object_instance_registry_type;
scene_object_instance_registry_type *scene_object_instance_registry = nullptr;

void TWorldObject::SetName(const std::string& name)
{
	assert(!world->ObjectNameExists(TWorldObjectType::Material, name.c_str()));
	this->name = name;
}

std::string TWorldObject::GetName()
{
	return name;
}

TWorldObject::TWorldObject(IWorld* world, std::string name)
{
	this->world = world;
	this->name = name;
}

IProperties* TWorldObject::GetProperties()
{
	return &properties;
}

IWorld* TWorldObject::GetWorld()
{
	return world;
}


namespace EngineInterface
{
	IWorld* CreateWorld()
	{
		return (new TWorld());
	}

	void DestroyWorld(IWorld* world)
	{
		delete dynamic_cast<TWorld*>(world);
	}



	IDirector* IDirector::CreateDirector(std::string assets_dir)
	{
		return new TDirector(assets_dir);
	}

	void IDirector::DestroyDirector(IDirector* director, bool clear_static_data)
	{
		delete dynamic_cast<TDirector*>(director);
		//очистка статичных данных должна выполняться только при завершении работы
		if (clear_static_data)
		{
			SceneObjectFactory::UnregisterAll();
			SceneObjectInstanceFactory::UnregisterAll();
			PropertiesFactory::UnregisterAll();
			AnimDescFactory::UnregisterAll();
			PhysShapeFactory::UnregisterAll();
		}
	}

	IWorldInstance* CreateWorldInstance(IWorld* source, IResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message)
	{
		return new TWorldInstance(dynamic_cast<TWorld*>(source), dynamic_cast<TResources*>(resources), assets_dir, call_scripts, compile_success, error_message);
	}

	void DestroyWorldInstance(IWorldInstance* world)
	{
		delete dynamic_cast<TWorldInstance*>(world);
	}

	/*bool CompileScripts(IWorld* source, IScriptInstance* script_instance, std::vector<std::string>& errors_list)
	{
		return TWorldInstance::CheckScriptErrors(dynamic_cast<TWorld*>(source), dynamic_cast<TBaluScriptInstance*>(script_instance), errors_list);
	}*/

	TVec2 TDrawingHelperContext::FromScreenPixelsToScene(TVec2i screen_pixels)
	{

		auto screen_coords = screen->FromScreenPixels2(screen_pixels);
		auto view_coord = screen->FromScreenToView(*view, screen_coords);
		auto scene_coord = IScene::FromViewportToScene(viewport, view_coord);
		return scene_coord;
	}
	TVec2i TDrawingHelperContext::FromSceneToScreenPixels(TVec2 scene_coordinates)
	{
		auto viewport_coord = IScene::FromSceneToViewport(viewport, scene_coordinates);
		auto screen_coord = screen->FromViewToScreen(*view, viewport_coord);
		auto screen_pixels = screen->ToScreenPixels2(screen_coord);
		return screen_pixels;
	}

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

	TSceneObject* SceneObjectFactory::Create(const char* name)
	{
		for (int i = 0; i < scene_object_registry->size(); i++)
			if (strcmp((*scene_object_registry)[i].first, name) == 0)
				return (*scene_object_registry)[i].second();
		throw std::invalid_argument("Тип не зарегистрирован");
	}

	bool SceneObjectInstanceFactory::Register(const char* name, SceneObjectInstanceClone clone)
	{
		if (scene_object_instance_registry == nullptr)
			scene_object_instance_registry = new scene_object_instance_registry_type();
		scene_object_instance_registry->push_back(std::pair<const char*, SceneObjectInstanceClone>(name, clone));
		return true;
	}

	void SceneObjectInstanceFactory::UnregisterAll()
	{
		delete scene_object_instance_registry;
	}

	TSceneObjectInstance* SceneObjectInstanceFactory::Create(const char* name, TSceneObject* param, TBaluSceneInstance* scene)
	{
		for (int i = 0; i < scene_object_instance_registry->size(); i++)
			if (strcmp((*scene_object_instance_registry)[i].first, name) == 0)
				return (*scene_object_instance_registry)[i].second(param, scene);
		throw std::invalid_argument("Тип не зарегистрирован");
	}
}
