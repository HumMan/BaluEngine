#include "WorldInstance.h"

TBaluWorldInstance::TBaluWorldInstance(TBaluWorld* source, TResourses* resources)
{
	this->source = source;
	this->resources = resources;
}
TBaluSceneInstance* TBaluWorldInstance::RunScene(TBaluScene* scene_source)
{
	instances.push_back(std::make_unique<TBaluSceneInstance>(scene_source, resources));
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
	for (int i = 0; i < instances.size(); i++)
		instances[i]->OnPrePhysStep();
}

void TBaluWorldInstance::PhysStep(float step)
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->PhysStep(step);
}

void TBaluWorldInstance::OnProcessCollisions()
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->OnProcessCollisions();
}
void TBaluWorldInstance::OnStep(float step)
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->OnStep(step);
}

void TBaluWorldInstance::OnKeyDown(TKey key)
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->OnKeyDown(key);
}


void TBaluWorldInstance::UpdateTransform()
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->UpdateTransform();
}

void TBaluWorldInstance::DebugDraw()
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->DebugDraw();
}