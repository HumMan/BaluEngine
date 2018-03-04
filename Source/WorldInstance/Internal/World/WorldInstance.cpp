#include "WorldInstance.h"

#include "../Scene/ISceneInstance.h"

#include <algorithm>

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;


	WorldDef::IWorld* TWorld::GetSource()
	{
		return source;
	}

	TWorld::TWorld(WorldDef::IWorld* source/*, TResources* resources*/, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message)
	{
		this->source = source;
		//this->resources = resources;

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
		scene_instances.push_back(std::unique_ptr<IScene>(new TScene(this, scene_source/*, resources*/)));
		return scene_instances.back().get();
	}
	IScene* TWorld::RunScene()
	{
		scene_instances.push_back(std::unique_ptr<TScene>(new TScene(this/*, resources*/)));
		return scene_instances.back().get();
	}
	//IScene* TWorld::RunScene(TLayersManager* scene_layers)
	//{
	//	scene_instances.push_back(std::unique_ptr<TSceneInstance>(new TSceneInstance(this, resources, scene_layers)));
	//	return scene_instances.back().get();
	//}

	void TWorld::StopScene(IScene* scene)
	{
		auto iter = std::find_if(scene_instances.begin(), scene_instances.end(), [&](std::unique_ptr<IScene>& p){return p.get() == scene; });
		if (iter != scene_instances.end())
		{
			scene_instances.erase(iter);
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
