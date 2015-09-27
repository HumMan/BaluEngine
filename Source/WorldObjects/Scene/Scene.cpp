#include "Scene.h"

#include <World\World.h>

#include "SceneEditor\sceneEditor.h"

TVec2 EngineInterface::IBaluScene::FromViewportToScene(EngineInterface::IViewport* viewport, TVec2 viewport_coord)
{
	return ((viewport_coord - TVec2(0.5, 0.5))).ComponentMul(viewport->GetAABB().GetSize()) + viewport->GetAABB().GetPosition();
}

TVec2 EngineInterface::IBaluScene::FromSceneToViewport(EngineInterface::IViewport* viewport, TVec2 scene_coord)
{
	//return (scene_coord - viewport->GetAABB().GetPosition()) / viewport->GetAABB().GetSize();
	return ((scene_coord - viewport->GetAABB().GetPosition()) / viewport->GetAABB().GetSize())+TVec2(0.5,0.5);
}

TViewport* TBaluScene::CreateViewport(std::string name)
{
	auto it = viewports.find(name);
	if(it != viewports.end())
		throw std::invalid_argument("Viewport с данным именем уже существует");
	return &(viewports[name]);
}

TViewport* TBaluScene::FindViewport(std::string name)
{
	auto it = viewports.find(name);
	if (it == viewports.end())
		return nullptr;
	return &it->second;
}

std::string TBaluScene::GetName()
{
	return scene_name;
}

void TBaluScene::SetName(std::string name)
{
	assert(!world->ObjectNameExists(TWorldObjectType::Scene, name.c_str()));
	scene_name = name;
}

int TBaluScene::GetInstancesCount()
{
	return instances.size();
}
TSceneObject* TBaluScene::GetInstance(int index)
{
	return instances[index].get();
}

TSceneObject* TBaluScene::CreateInstance(TBaluClass* balu_class)
{
	instances.push_back(std::make_unique<TBaluSceneClassInstance>(balu_class));
	return instances.back().get();
}

TSceneObject* TBaluScene::CreateInstance(EngineInterface::IBaluClass* balu_class)
{
	return CreateInstance(dynamic_cast<TBaluClass*>(balu_class));
}

void TBaluScene::DestroyInstance(TSceneObject* instance)
{
	auto iter = std::find_if(instances.begin(), instances.end(), [&](std::unique_ptr<TSceneObject>& p){return p.get() == instance; });
	if (iter != instances.end())
	{
		instances.erase(iter);
	}
	else
	{
		throw std::invalid_argument("Объект не находится на данной сцене");
	}
}

IAbstractEditor* TBaluScene::CreateEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluSceneInstance* editor_scene_instance)
{
	auto result = new TSceneEditor();
	result->Initialize(drawing_context, world, this, editor_scene_instance);
	return result;
}