#include "WorldInstance.h"

#include "../Scene/SceneInstance.h"

#include "../Composer/Composer.h"

#include "../Scripts/IScriptInstance.h"

#include <algorithm>

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;

class TWorld::TPrivate
{
public:
	WorldDef::IWorld* source;
	std::vector<std::shared_ptr<IScene>> scene_instances;

	ISceneContactListener* contacts_listener;

	TResources* resources;

	std::shared_ptr < TComposer> composer;
	std::weak_ptr <IWorld> this_ptr;
};

WorldDef::IWorld* TWorld::GetSource()
{
	return p->source;
}

void TWorld::SetThisPtr(std::weak_ptr <IWorld> this_ptr)
{
	p->this_ptr = this_ptr;
}

TWorld::TWorld(WorldDef::IWorld* source, TResources* resources, std::string assets_dir)
{
	p.reset(new TWorld::TPrivate());
	p->source = source;
	p->resources = resources;
	p->composer = std::make_shared<TComposer>();
	std::vector<std::string> errors_list;
}

std::shared_ptr < IScene> TWorld::RunScene(WorldDef::IScene* scene_source)
{
	auto new_scene = std::make_shared<TScene>(p->this_ptr, scene_source, p->resources);
	new_scene->SetCollideListener(p->contacts_listener);
	new_scene->InitInstances(new_scene);
	p->scene_instances.push_back(new_scene);
	return p->scene_instances.back();
}

//IScene* TWorld::RunScene()
//{
//	p->scene_instances.push_back(std::unique_ptr<TScene>(new TScene(this, p->resources)));
//	return p->scene_instances.back().get();
//}
//IScene* TWorld::RunScene(TLayersManager* scene_layers)
//{
//	scene_instances.push_back(std::unique_ptr<TSceneInstance>(new TSceneInstance(this, resources, scene_layers)));
//	return scene_instances.back().get();
//}

void TWorld::StopScene(std::shared_ptr < IScene> scene)
{
	auto iter = std::find_if(p->scene_instances.begin(), p->scene_instances.end(), [&](std::shared_ptr<IScene>& p) {return p == scene; });
	if (iter != p->scene_instances.end())
	{
		p->scene_instances.erase(iter);
	}
	else
	{
		throw std::invalid_argument("Отсутствует сцена с данным имененем");
	}
}

void TWorld::CallOnProcessCollisions()
{
	for (auto& v : p->scene_instances)
		dynamic_cast<TScene*>(v.get())->OnProcessCollisions();
}

void TWorld::PhysStep(float step)
{
	for(auto& v : p->scene_instances)
		dynamic_cast<TScene*>(v.get())->PhysStep(step);
}
void TWorld::OnStep(float step)
{
	for (auto& v : p->scene_instances)
		dynamic_cast<TScene*>(v.get())->OnStep(step);
}


void TWorld::UpdateTransform()
{
	for (auto& v : p->scene_instances)
		dynamic_cast<TScene*>(v.get())->UpdateTransform();
}

void TWorld::SetCollideListener(ISceneContactListener* contacts_listener)
{
	p->contacts_listener = contacts_listener;
}

TWorld::~TWorld()
{

}

int TWorld::GetSceneCount()
{
	return p->scene_instances.size();
}
std::shared_ptr < IScene> TWorld::GetScene(int index)
{
	return p->scene_instances[index];
}

std::shared_ptr < IComposer> TWorld::GetComposer()
{
	return p->composer;
}

std::shared_ptr<IWorld> WorldInstance::CreateWorld(WorldDef::IWorld* source, TResources* resources, std::string assets_dir)
{
	return std::make_shared<TWorld>(source, dynamic_cast<TResources*>(resources), assets_dir);
}

BALUENGINEDLL_API std::shared_ptr<IEventsEditorInstance> WorldInstance::CreateEventsEditor(std::shared_ptr<IWorld> world, WorldDef::IEventsEditor* source)
{
	return std::make_shared<TScriptInstance>(world, source);
}
