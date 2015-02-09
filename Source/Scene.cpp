#include "Scene.h"

TVec2 TBaluScene::FromViewportToScene(EngineInterface::IViewport* viewport, TVec2 viewport_coord)
{
	return viewport_coord.ComponentMul(viewport->GetAABB().GetSize()) + viewport->GetAABB().GetPosition();
}

TVec2 TBaluScene::FromSceneToViewport(EngineInterface::IViewport* viewport, TVec2 scene_coord)
{
	//return (scene_coord - viewport->GetAABB().GetPosition()) / viewport->GetAABB().GetSize();
	return ((scene_coord - viewport->GetAABB().GetPosition()) / viewport->GetAABB().GetSize())*0.5+TVec2(0.5,0.5);
}

void TViewport::SetTransform(TBaluTransform transform)
{
	this->transform = transform;
}
void TViewport::SetAspectRatio(float aspect)
{
	this->aspect = aspect;
}
void TViewport::SetWidth(float width)
{
	this->width = width;
}
TAABB2 TViewport::GetAABB()
{
	TAABB2 aabb(TVec2(0, 0), TVec2(width, width / aspect));

	return TOBB<float, 2>(transform.position, transform.GetOrientation(), aabb).GetAABB();
}


TViewport* TBaluScene::CreateViewport(std::string name)
{
	auto it = viewports.find(name);
	if(it != viewports.end())
		throw std::invalid_argument("Viewport с данным именем уже существует");
	return &(viewports[name]);
}

std::string TBaluScene::GetName()
{
	return scene_name;
}

void TBaluScene::SetName(std::string name)
{
	scene_name = name;
}

int TBaluScene::GetInstancesCount()
{
	return instances.size();
}
TBaluScene::TClassInstance* TBaluScene::GetInstance(int index)
{
	return instances[index].get();
}

TBaluScene::TClassInstance* TBaluScene::CreateInstance(TBaluClass* balu_class)
{
	instances.push_back(std::make_unique<TBaluScene::TClassInstance>(balu_class));
	return instances.back().get();
}

EngineInterface::IBaluSceneClassInstance* TBaluScene::CreateInstance(EngineInterface::IBaluClass* balu_class)
{
	return CreateInstance(dynamic_cast<TBaluClass*>(balu_class));
}

void TBaluScene::DestroyInstance(TBaluScene::TClassInstance* instance)
{
	auto iter = std::find_if(instances.begin(), instances.end(), [&](std::unique_ptr<TBaluScene::TClassInstance>& p){return p.get() == instance; });
	if (iter != instances.end())
	{
		instances.erase(iter);
	}
	else
	{
		throw std::invalid_argument("Объект не находится на данной сцене");
	}
}

void TBaluScene::DestroyInstance(EngineInterface::IBaluSceneClassInstance* instance)
{
	DestroyInstance(dynamic_cast<TClassInstance*>(instance));
}