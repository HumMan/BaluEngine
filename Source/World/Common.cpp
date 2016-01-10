#include "ICommon.h"

#include "IWorld.h"

#include <World\IWorld.h>

#include <World\IDirector.h>
#include <World\IWorldInstance.h>


using namespace EngineInterface;

void TBaluWorldObject::SetName(const std::string& name)
{
	assert(!world->ObjectNameExists(TWorldObjectType::Material, name.c_str()));
	this->name = name;
}

std::string TBaluWorldObject::GetName()
{
	return name;
}

TBaluWorldObject::TBaluWorldObject(IBaluWorld* world, std::string name)
{
	this->world = world;
	this->name = name;
}

IProperties* TBaluWorldObject::GetProperties()
{
	return &properties;
}

IBaluWorld* TBaluWorldObject::GetWorld()
{
	return world;
}


namespace EngineInterface
{
	IBaluWorld* CreateWorld()
	{
		return (new TBaluWorld());
	}

	void DestroyWorld(IBaluWorld* world)
	{
		delete dynamic_cast<TBaluWorld*>(world);
	}



	IDirector* IDirector::CreateDirector(std::string assets_dir)
	{
		return new TDirector(assets_dir);
	}

	void IDirector::DestroyDirector(IDirector* director)
	{
		delete dynamic_cast<TDirector*>(director);
	}

	IBaluWorldInstance* CreateWorldInstance(IBaluWorld* source, IResources* resources)
	{
		return new TBaluWorldInstance(dynamic_cast<TBaluWorld*>(source), dynamic_cast<TResources*>(resources));
	}

	void DestroyWorldInstance(IBaluWorldInstance* world)
	{
		delete dynamic_cast<TBaluWorldInstance*>(world);
	}

	//bool CompileScripts(IBaluWorld* source, IBaluScriptInstance* script_instance, std::vector<std::string>& errors_list)
	//{
	//	return TBaluWorldInstance::CheckScriptErrors(dynamic_cast<TBaluWorld*>(source), dynamic_cast<TBaluScriptInstance*>(script_instance), errors_list);
	//}

	TVec2 TDrawingHelperContext::FromScreenPixelsToScene(TVec2i screen_pixels)
	{

		auto screen_coords = screen->FromScreenPixels2(screen_pixels);
		auto view_coord = screen->FromScreenToView(*view, screen_coords);
		auto scene_coord = IBaluScene::FromViewportToScene(viewport, view_coord);
		return scene_coord;
	}
	TVec2i TDrawingHelperContext::FromSceneToScreenPixels(TVec2 scene_coordinates)
	{
		auto viewport_coord = IBaluScene::FromSceneToViewport(viewport, scene_coordinates);
		auto screen_coord = screen->FromViewToScreen(*view, viewport_coord);
		auto screen_pixels = screen->ToScreenPixels2(screen_coord);
		return screen_pixels;
	}

	std::vector < std::pair<const char*, SceneObjectClone>> scene_object_registry;

	bool SceneObjectFactory::Register(const char* name, SceneObjectClone clone)
	{
		scene_object_registry.push_back(std::pair<const char*, SceneObjectClone>(name, clone));
		return true;
	}

	TSceneObject* SceneObjectFactory::Create(const char* name)
	{
		for (int i = 0; i < scene_object_registry.size(); i++)
			if (strcmp(scene_object_registry[i].first, name) == 0)
				return scene_object_registry[i].second();
		throw std::invalid_argument("Тип не зарегистрирован");
	}

	std::vector < std::pair<const char*, SceneObjectInstanceClone>> scene_object_instance_registry;

	bool SceneObjectInstanceFactory::Register(const char* name, SceneObjectInstanceClone clone)
	{
		scene_object_instance_registry.push_back(std::pair<const char*, SceneObjectInstanceClone>(name, clone));
		return true;
	}

	TSceneObjectInstance* SceneObjectInstanceFactory::Create(const char* name, TSceneObject* param, TBaluSceneInstance* scene)
	{
		for (int i = 0; i < scene_object_instance_registry.size(); i++)
			if (strcmp(scene_object_instance_registry[i].first, name) == 0)
				return scene_object_instance_registry[i].second(param, scene);
		throw std::invalid_argument("Тип не зарегистрирован");
	}
}