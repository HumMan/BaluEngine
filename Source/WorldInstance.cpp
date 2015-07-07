#include "WorldInstance.h"

#include "ScriptClassesRegistry.h"

#include "../Source/Semantic/SMethod.h"
#include "../Source/Semantic/SClass.h"
#include "../Source/Semantic/FormalParam.h"
#include "../Source/Semantic/SStatements.h"
#include "../Source/Syntax/Statements.h"
#include "../Source/Syntax/Method.h"
#include "../Source/semanticAnalyzer.h"

#include "Director.h"

TBaluWorld* TBaluWorldInstance::GetSource()
{
	return source;
}

TBaluWorldInstance::TBaluWorldInstance(TBaluWorld* source, TResources* resources)
	:script_engine(resources->GetAssetsDir())
{
	this->source = source;
	this->resources = resources;

	for (auto& k : source->classes)
	{
		auto new_class_instance = new TBaluClassInstance(this, k.second.get());
		class_instances.emplace_back(new_class_instance);
	}

	std::vector<std::string> errors_list;
	CompileScripts(this, errors_list);

	for (auto& v : on_start_world_callback)
		script_engine.CallWorldStart(v, this, &composer);
}

TBaluSceneInstance* TBaluWorldInstance::RunScene(TBaluScene* scene_source)
{
	scene_instances.push_back(std::make_unique<TBaluSceneInstance>(this, scene_source, resources));
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
	for (int i = 0; i < scene_instances.size(); i++)
		scene_instances[i]->OnPrePhysStep();
}

void TBaluWorldInstance::PhysStep(float step)
{
	for (int i = 0; i < scene_instances.size(); i++)
		scene_instances[i]->PhysStep(step);
}

void TBaluWorldInstance::OnProcessCollisions()
{
	for (int i = 0; i < scene_instances.size(); i++)
		scene_instances[i]->OnProcessCollisions();
}
void TBaluWorldInstance::OnStep(float step)
{
	for (int i = 0; i < scene_instances.size(); i++)
		scene_instances[i]->OnStep(step);
}

void TBaluWorldInstance::KeyDown(TKey key)
{
	for (int i = 0; i < scene_instances.size(); i++)
		scene_instances[i]->OnKeyDown(key);
}

void TBaluWorldInstance::KeyUp(TKey key)
{
	/*for (int i = 0; i < instances.size(); i++)
		instances[i]->OnKeyUp(key);*/
}

void TBaluWorldInstance::MouseDown(TMouseEventArgs e)
{
	for (auto& v : mouse_down_callbacks)
	{
		script_engine.CallMouseEvent(v, &e);
	}
}

void TBaluWorldInstance::MouseMove(TMouseEventArgs e)
{
	for (auto& v : mouse_move_callbacks)
	{
		script_engine.CallMouseEvent(v, &e);
	}
}

void TBaluWorldInstance::MouseUp(TMouseEventArgs e)
{
	for (auto& v : mouse_up_callbacks)
	{
		script_engine.CallMouseEvent(v, &e);
	}
}

void TBaluWorldInstance::MouseVerticalWheel(int amount)
{

}

void TBaluWorldInstance::UpdateTransform()
{
	for (int i = 0; i < scene_instances.size(); i++)
		scene_instances[i]->UpdateTransform();
}

bool TBaluWorldInstance::CompileScripts(TBaluWorldInstance* world_instance, std::vector<std::string>& errors_list)
{
	TBaluScriptInstance& script_engine = *world_instance->GetScriptEngine();
	TBaluWorld* world = world_instance->GetSource();
	try
	{
		for (auto& v : world->on_start_world_callback)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("func static StartWorld(IWorldInstance world_instance, IComposer composer)\n{\n") + method_body + "\n}\n";
				world_instance->on_start_world_callback.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}
		for (auto& v : world->viewport_resize_callback)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("func static ViewportResize(IDirector director, vec2i old_size, vec2i new_size)\n{\n") + method_body + "\n}\n";
				world_instance->viewport_resize_callback.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}

		for (auto& v : world->mouse_up_callbacks)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("") + method_body + "";
				world_instance->mouse_up_callbacks.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}
		for (auto& v : world->mouse_down_callbacks)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("") + method_body + "";
				world_instance->mouse_down_callbacks.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}
		for (auto& v : world->mouse_move_callbacks)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("") + method_body + "";
				world_instance->mouse_move_callbacks.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}
		for (auto& k : world_instance->class_instances)
		{
			k->CompileScripts(errors_list);
		}
	}
	catch (std::string ex)
	{
		errors_list = script_engine.GetErrors();
		return false;
	}
	return true;
}

void TBaluWorldInstance::ViewportResize(TDirector* director, TVec2i old_size, TVec2i new_size)
{
	for (auto& v : viewport_resize_callback)
		script_engine.CallViewportResize(v, director, old_size, new_size);
}
