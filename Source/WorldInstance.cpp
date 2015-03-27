#include "WorldInstance.h"

#include "ScriptClassesRegistry.h"

#include "../Source/Semantic/SMethod.h"
#include "../Source/Semantic/SClass.h"
#include "../Source/Semantic/FormalParam.h"
#include "../Source/Semantic/SStatements.h"
#include "../Source/Syntax/Statements.h"
#include "../Source/Syntax/Method.h"
#include "../Source/semanticAnalyzer.h"

TBaluWorld* TBaluWorldInstance::GetSource()
{
	return source;
}

TBaluWorldInstance::TBaluWorldInstance(TBaluWorld* source, TResources* resources)
{
	this->source = source;
	this->resources = resources;

	auto time = new TTime();
	time->Start();

	char* script_base_source;
	{
		TFileData file("../../../BaluScript/Source/NativeTypes/base_types.bscript", "rb");
		script_base_source = file.ReadAll();
		script_base_source[file.GetSize()] = '\0';
	}
	syntax.reset(new TSyntaxAnalyzer());
	syntax->Compile((char*)(("class Script{" + std::string(script_base_source) + "}").c_str()), *time);

	TClassRegistryParams params;
	params.smethods = &smethods;
	params.static_objects = &static_objects;
	params.syntax = syntax.get();
	TScriptClassesRegistry::RegisterClassesInScript(params);
}
TBaluSceneInstance* TBaluWorldInstance::RunScene(TBaluScene* scene_source)
{
	instances.push_back(std::make_unique<TBaluSceneInstance>(this, scene_source, resources));
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

EngineInterface::IBaluSceneInstance* TBaluWorldInstance::RunScene(EngineInterface::IBaluScene* scene_source)
{
	return RunScene(dynamic_cast<TBaluScene*>(scene_source));
}

void TBaluWorldInstance::StopScene(EngineInterface::IBaluSceneInstance* scene_instance)
{
	StopScene(dynamic_cast<TBaluSceneInstance*>(scene_instance));
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

void TBaluWorldInstance::KeyDown(TKey key)
{
	for (int i = 0; i < instances.size(); i++)
		instances[i]->OnKeyDown(key);
}

void TBaluWorldInstance::KeyUp(TKey key)
{
	/*for (int i = 0; i < instances.size(); i++)
		instances[i]->OnKeyUp(key);*/
}

void TBaluWorldInstance::MouseDown(TMouseEventArgs e)
{
	for (auto& v : source->mouse_down_callbacks)
	{
		v.Execute(e);
	}
}

void TBaluWorldInstance::MouseMove(TMouseEventArgs e)
{
	for (auto& v : source->mouse_move_callbacks)
	{
		v.Execute(e);
	}
}

void TBaluWorldInstance::MouseUp(TMouseEventArgs e)
{
	for (auto& v : source->mouse_up_callbacks)
	{
		v.Execute(e);
	}
}

void TBaluWorldInstance::MouseVerticalWheel(int amount)
{

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