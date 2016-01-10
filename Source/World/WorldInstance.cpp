#include "IWorldInstance.h"

#include "ScriptClassesRegistry.h"

#include "../Source/Semantic/SMethod.h"
#include "../Source/Semantic/SClass.h"
#include "../Source/Semantic/FormalParam.h"
#include "../Source/Semantic/SStatements.h"
#include "../Source/Syntax/Statements.h"
#include "../Source/Syntax/Method.h"
#include "../Source/semanticAnalyzer.h"

#include "IDirector.h"

#include "IEventsEditorInstance.h"

namespace EngineInterface
{

	TBaluWorld* TBaluWorldInstance::GetSource()
	{
		return source;
	}

	
	TBaluWorldInstance::TBaluWorldInstance(TBaluWorld* source, TResources* resources)
		//:script_engine(resources->GetAssetsDir())
	{
		this->source = source;
		this->resources = resources;

		this->events_editor.reset(new TEventsEditorInstance(dynamic_cast<TEventsEditor*>(source->GetEventsEditor())));



		//for (auto& k : source->GetObjects(TWorldObjectType::Class))
		//{
		//	auto curr_class = dynamic_cast<TBaluClass*>(&(*k));
		//	auto new_class_instance = new TBaluClassCompiledScripts(this, curr_class);
		//	class_compiled_instances.emplace_back(new_class_instance);
		//}

		std::vector<std::string> errors_list;
		this->events_editor->CompileScripts();

		//for (auto& v : on_start_world_callback)
		//	script_engine.CallWorldStart(v, this, &composer);
	}

	TBaluSceneInstance* TBaluWorldInstance::RunScene(TBaluScene* scene_source)
	{
		scene_instances.push_back(std::make_unique<TBaluSceneInstance>(this, scene_source, resources));
		return scene_instances.back().get();
	}
	TBaluSceneInstance* TBaluWorldInstance::RunScene()
	{
		scene_instances.push_back(std::make_unique<TBaluSceneInstance>(this, resources));
		return scene_instances.back().get();
	}
	TBaluSceneInstance* TBaluWorldInstance::RunScene(TLayersManager* scene_layers)
	{
		scene_instances.push_back(std::make_unique<TBaluSceneInstance>(this, resources, scene_layers));
		return scene_instances.back().get();
	}

	void TBaluWorldInstance::StopScene(TBaluSceneInstance* scene)
	{
		auto iter = std::find_if(scene_instances.begin(), scene_instances.end(), [&](std::unique_ptr<TBaluSceneInstance>& p){return p.get() == scene; });
		if (iter != scene_instances.end())
		{
			scene_instances.erase(iter);
		}
		else
		{
			throw std::invalid_argument("Отсутствует сцена с данным имененем");
		}
	}

	IBaluSceneInstance* TBaluWorldInstance::RunScene(IBaluScene* scene_source)
	{
		return RunScene(dynamic_cast<TBaluScene*>(scene_source));
	}

	void TBaluWorldInstance::StopScene(EngineInterface::IBaluSceneInstance* scene_instance)
	{
		StopScene(dynamic_cast<TBaluSceneInstance*>(scene_instance));
	}


	void TBaluWorldInstance::PhysStep(float step)
	{
		for (int i = 0; i < scene_instances.size(); i++)
			scene_instances[i]->PhysStep(step);
	}
	void TBaluWorldInstance::OnStep(float step)
	{
		for (int i = 0; i < scene_instances.size(); i++)
			scene_instances[i]->OnStep(step);
	}


	void TBaluWorldInstance::UpdateTransform()
	{
		for (int i = 0; i < scene_instances.size(); i++)
			scene_instances[i]->UpdateTransform();
	}

	TBaluWorldInstance::~TBaluWorldInstance()
	{
	}
}