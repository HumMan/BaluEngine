#include "SceneInstance.h"

TBaluSceneInstance::TBaluSceneInstance(TBaluScene* source)
{
	for (int i = 0; i < source->GetInstancesCount(); i++)
	{
		auto source_instance = source->GetInstance(i);
		auto instance = CreateInstance(source_instance->balu_class);
		instance->SetTransform(source_instance->transform);
	}
}

TBaluSceneInstance::TBaluSceneInstance(TBaluSceneInstance&& right)
{
	instances = std::move(right.instances);
}

TBaluInstance* TBaluSceneInstance::CreateInstance(TBaluClass* use_class)
{
	instances.push_back(std::make_unique<TBaluInstance>(use_class));
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

void TBaluSceneInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results)
{

}