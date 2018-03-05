#include "WorldInstance.h"

#include "../Scene/SceneInstance.h"

#include "../Composer/Composer.h"

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

	//std::unique_ptr<TEventsEditorInstance> events_editor;

};


WorldDef::IWorld* TWorld::GetSource()
{
	return p->source;
}

TWorld::TWorld(WorldDef::IWorld* source, TResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message)
{
	p->source = source;
	p->resources = resources;

	//this->events_editor.reset(new TEventsEditorInstance(source->GetEventsEditor(), assets_dir));

	std::vector<std::string> errors_list;
	//compile_success = this->events_editor->CompileScripts(error_message);

	//if (call_scripts && compile_success)
	//{
	//	this->events_editor->WorldStart(this, &composer);
	//}
}

IScene* TWorld::RunScene(WorldDef::IScene* scene_source)
{
	p->scene_instances.push_back(std::unique_ptr<IScene>(new TScene(this, scene_source/*, resources*/)));
	return p->scene_instances.back().get();
}
IScene* TWorld::RunScene()
{
	p->scene_instances.push_back(std::unique_ptr<TScene>(new TScene(this/*, resources*/)));
	return p->scene_instances.back().get();
}
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

void TWorld::PhysStep(float step)
{
	//for (int i = 0; i < scene_instances.size(); i++)
	//	scene_instances[i]->PhysStep(step);
}
void TWorld::OnStep(float step)
{
	//for (int i = 0; i < scene_instances.size(); i++)
	//	scene_instances[i]->OnStep(step);
}


void TWorld::UpdateTransform()
{
	//for (int i = 0; i < scene_instances.size(); i++)
	//	scene_instances[i]->UpdateTransform();
}

TWorld::~TWorld()
{
}
//IEventsEditorInstance* TWorld::GetEventsEditor()
//{
//	return dynamic_cast<IEventsEditorInstance*>(events_editor.get());
//}

int TWorld::GetSceneInstancesCount()
{
	return p->scene_instances.size();
}
IScene* TWorld::GetSceneInstance(int index)
{
	return p->scene_instances[index].get();
}

IComposer* TWorld::GetComposer()
{
	return &p->composer;
}
