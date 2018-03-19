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
	std::vector<std::unique_ptr<IScene>> scene_instances;

	TResources* resources;

	TComposer composer;

	std::unique_ptr<TScriptInstance> script_instance;

};


WorldDef::IWorld* TWorld::GetSource()
{
	return p->source;
}

TWorld::TWorld(WorldDef::IWorld* source, TResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message)
{
	p.reset(new TWorld::TPrivate());
	p->source = source;
	p->resources = resources;

	p->script_instance.reset(new TScriptInstance(this, source->GetEventsEditor()));

	p->script_instance->Compile();

	//this->events_editor.reset(new TEventsEditorInstance(source->GetEventsEditor(), assets_dir));

	std::vector<std::string> errors_list;
	//compile_success = this->events_editor->CompileScripts(error_message);

	//if (call_scripts && compile_success)
	//{
	//	this->events_editor->WorldStart(this, &composer);
	//}
	if (call_scripts)
		p->script_instance->WorldStart(this, &p->composer);
}

IScene* TWorld::RunScene(WorldDef::IScene* scene_source)
{
	p->scene_instances.push_back(std::unique_ptr<IScene>(new TScene(this, scene_source, p->resources)));
	return p->scene_instances.back().get();
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

void TWorld::StopScene(IScene* scene)
{
	auto iter = std::find_if(p->scene_instances.begin(), p->scene_instances.end(), [&](std::unique_ptr<IScene>& p) {return p.get() == scene; });
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

TWorld::~TWorld()
{

}

IEventsEditorInstance* TWorld::GetEventsEditor()
{
	return p->script_instance.get();
}

int TWorld::GetSceneCount()
{
	return p->scene_instances.size();
}
IScene* TWorld::GetScene(int index)
{
	return p->scene_instances[index].get();
}

IComposer* TWorld::GetComposer()
{
	return &p->composer;
}

IWorld* WorldInstance::CreateWorld(WorldDef::IWorld* source, TResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message)
{
	return new TWorld(source, dynamic_cast<TResources*>(resources), assets_dir, call_scripts, compile_success, error_message);
}

void WorldInstance::DestroyWorld(IWorld* world)
{
	delete dynamic_cast<TWorld*>(world);
}
