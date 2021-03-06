#include "IWorldInstance.h"

#include "Scripts/ScriptClassesRegistry.h"

#include "../Source/Semantic/SMethod.h"
#include "../Source/Semantic/SClass.h"
#include "../Source/Semantic/FormalParam.h"
#include "../Source/Semantic/SStatements.h"
#include "../Source/Syntax/Statements.h"
#include "../Source/Syntax/Method.h"
#include "../Source/semanticAnalyzer.h"

#include <Common/IDirector.h>

#include "Scripts/IEventsEditorInstance.h"

namespace EngineInterface
{

	TBaluWorld* TBaluWorldInstance::GetSource()
	{
		return source;
	}

	TBaluWorldInstance::TBaluWorldInstance(TBaluWorld* source, TResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message)
	{
		this->source = source;
		this->resources = resources;

		this->events_editor.reset(new TEventsEditorInstance(source->GetEventsEditor(), assets_dir));

		std::vector<std::string> errors_list;
		compile_success = this->events_editor->CompileScripts(error_message);

		if (call_scripts && compile_success)
		{
			this->events_editor->WorldStart(this, &composer);
		}
	}

	TBaluSceneInstance* TBaluWorldInstance::RunScene(TBaluScene* scene_source)
	{
		scene_instances.push_back(std::unique_ptr<TBaluSceneInstance>(new TBaluSceneInstance(this, scene_source, resources)));
		return scene_instances.back().get();
	}
	TBaluSceneInstance* TBaluWorldInstance::RunScene()
	{
		scene_instances.push_back(std::unique_ptr<TBaluSceneInstance>(new TBaluSceneInstance(this, resources)));
		return scene_instances.back().get();
	}
	TBaluSceneInstance* TBaluWorldInstance::RunScene(TLayersManager* scene_layers)
	{
		scene_instances.push_back(std::unique_ptr<TBaluSceneInstance>(new TBaluSceneInstance(this, resources, scene_layers)));
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
			throw std::invalid_argument("����������� ����� � ������ ��������");
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
