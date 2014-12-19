#include "WorldInstance.h"

TBaluWorldInstance::TBaluWorldInstance(TBaluWorld* source)
{
	this->source = source;
}
TBaluSceneInstance* TBaluWorldInstance::RunScene(TBaluScene* scene_source)
{
	instances.push_back(std::make_unique<TBaluSceneInstance>(scene_source));
	return instances.back().get();
}
void TBaluWorldInstance::StopScene(TBaluSceneInstance* scene)
{
	auto iter = std::find(instances.begin(), instances.end(), scene);
	if (iter != instances.end())
	{
		instances.erase(iter);
	}
	else
	{
		throw std::invalid_argument("");
	}
}
