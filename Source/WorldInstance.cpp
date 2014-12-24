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
	auto iter = std::find_if(instances.begin(), instances.end(), [&](std::unique_ptr<TBaluSceneInstance>& p){return p.get() == scene; });
	if (iter != instances.end())
	{
		instances.erase(iter);
	}
	else
	{
		throw std::invalid_argument("Отсутствует сцена с данным имененем");
	}
}

void TBaluWorldInstance::OnPrePhysStep()
{

}

void TBaluWorldInstance::PhysStep()
{

}

void TBaluWorldInstance::OnProcessCollisions()
{

}
void TBaluWorldInstance::OnStep(float step)
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->OnStep(step);
}