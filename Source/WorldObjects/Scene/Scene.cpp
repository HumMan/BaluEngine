#include "IScene.h"

#include <World/IWorld.h>

#include "SceneEditor/sceneEditor.h"

TVec2 EngineInterface::IBaluScene::FromViewportToScene(EngineInterface::IViewport* viewport, TVec2 viewport_coord)
{
	return ((viewport_coord - TVec2(0.5, 0.5))).ComponentMul(viewport->GetAABB().GetSize()) + viewport->GetAABB().GetPosition();
}

TVec2 EngineInterface::IBaluScene::FromSceneToViewport(EngineInterface::IViewport* viewport, TVec2 scene_coord)
{
	//return (scene_coord - viewport->GetAABB().GetPosition()) / viewport->GetAABB().GetSize();
	return ((scene_coord - viewport->GetAABB().GetPosition()) / viewport->GetAABB().GetSize())+TVec2(0.5,0.5);
}

TViewport* TBaluScene::CreateViewport(const std::string& name)
{
	auto it = viewports.find(name);
	if(it != viewports.end())
		throw std::invalid_argument("Viewport с данным именем уже существует");
	return &(viewports[name]);
}

TBaluScene::TBaluScene(const char* name, TBaluWorld* world) 
	:layers(this), TBaluWorldObject(world, name)
{
}

IProperties* TBaluScene::GetProperties()
{
	return &properties;
}

TViewport* TBaluScene::FindViewport(const std::string& name)
{
	auto it = viewports.find(name);
	if (it == viewports.end())
		return nullptr;
	return &it->second;
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
	instances.push_back(std::unique_ptr<TBaluTransformedClass>(new TBaluTransformedClass(balu_class)));
	TChangeListenerArray::OnElementAdded(TWorldObjectSubType::SceneClassInstance);
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

IAbstractEditor* TBaluScene::CreateEditor(TDrawingHelperContext drawing_context, IBaluWorldInstance* world_instance)
{
	auto result = new TSceneEditor(drawing_context, world, this, world_instance);
	return result;
}
