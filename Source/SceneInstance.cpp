#include "SceneInstance.h"

TViewport* TBaluSceneInstance::GetViewport(std::string name)
{
	return &viewports[name];
}

TBaluSceneInstance::TBaluSceneInstance(TBaluScene* source)
{
	phys_world = std::make_unique<b2World>(b2Vec2(0, -1));

	for (int i = 0; i < source->GetInstancesCount(); i++)
	{
		auto source_instance = source->GetInstance(i);
		auto instance = CreateInstance(source_instance->balu_class);
		instance->SetTransform(source_instance->transform);
	}
}

TBaluSceneInstance::TBaluSceneInstance(TBaluSceneInstance&& right)
{
	phys_world = std::move(right.phys_world);
	instances = std::move(right.instances);
}

TBaluInstance* TBaluSceneInstance::CreateInstance(TBaluClass* use_class)
{
	instances.push_back(std::make_unique<TBaluInstance>(use_class, phys_world.get()));
	return instances.back().get();
}

TVec2 TBaluSceneInstance::WorldToScene(const TVec2& v)
{
	//TODO
	return TVec2();
}

TVec2 TBaluSceneInstance::SceneToWorld(const TVec2& v)
{
	//TODO
	return TVec2();
}

void TBaluSceneInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
	for (int i = 0; i < instances.size(); i++)
	{
		instances[i]->QueryAABB(frustum, results);
	}
}

void TBaluSceneInstance::OnStep(float step)
{
	phys_world->Step(step, 3, 5);
}