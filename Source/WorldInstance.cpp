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

void TBaluWorldInstance::AddMouseEventListener(TMouseEventListener* listener)
{
	auto it = std::find(OnMouseEventListeners.begin(), OnMouseEventListeners.end(), listener);
	if (it != OnMouseEventListeners.end())
		assert(false);
	OnMouseEventListeners.push_back(listener);
}

void TBaluWorldInstance::RemoveMouseEventListener(TMouseEventListener* listener)
{
	auto it = std::find(OnMouseEventListeners.begin(), OnMouseEventListeners.end(), listener);
	if (it == OnMouseEventListeners.end())
		assert(false);
	OnMouseEventListeners.erase(it);
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
	CompileScripts();

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
	for (auto& v : OnMouseEventListeners)
		v->OnMouseDown(e);
	for (auto& v : mouse_down_callbacks)
	{
		script_engine.CallMouseEvent(v, &e);
	}
}

void TBaluWorldInstance::MouseMove(TMouseEventArgs e)
{
	for (auto& v : OnMouseEventListeners)
		v->OnMouseMove(e);
	for (auto& v : mouse_move_callbacks)
	{
		script_engine.CallMouseEvent(v, &e);
	}
}

void TBaluWorldInstance::MouseUp(TMouseEventArgs e)
{
	for (auto& v : OnMouseEventListeners)
		v->OnMouseUp(e);
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

bool TBaluWorldInstance::CompileScripts()
{
	TBaluScriptInstance& script_engine = *GetScriptEngine();
	TBaluWorld* world = GetSource();
	try
	{
		for (auto& v : world->on_start_world_callback)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("func static StartWorld(IWorldInstance world_instance, IComposer composer)\n{\n") + method_body + "\n}\n";
				this->on_start_world_callback.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}
		for (auto& v : world->viewport_resize_callback)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("func static ViewportResize(IDirector director, vec2i old_size, vec2i new_size)\n{\n") + method_body + "\n}\n";
				this->viewport_resize_callback.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}

		for (auto& v : world->mouse_up_callbacks)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("") + method_body + "";
				this->mouse_up_callbacks.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}
		for (auto& v : world->mouse_down_callbacks)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("") + method_body + "";
				this->mouse_down_callbacks.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}
		for (auto& v : world->mouse_move_callbacks)
		{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("") + method_body + "";
				this->mouse_move_callbacks.push_back(script_engine.CompileMethod(&v, method.c_str()));
		}
		for (auto& k : this->class_instances)
		{
			k->CompileScripts();
		}
	}
	catch (std::string ex)
	{
		return false;
	}
	return true;
}

bool TBaluWorldInstance::CheckScriptErrors(TBaluWorld* source, TBaluScriptInstance* script_engine, std::vector<std::string>& errors_list)
{
	try
	{
		for (auto& v : source->on_start_world_callback)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static StartWorld(IWorldInstance world_instance, IComposer composer)\n{\n") + method_body + "\n}\n";
			script_engine->CompileMethod(&v, method.c_str());
		}
		for (auto& v : source->viewport_resize_callback)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static ViewportResize(IDirector director, vec2i old_size, vec2i new_size)\n{\n") + method_body + "\n}\n";
			script_engine->CompileMethod(&v, method.c_str());
		}

		for (auto& v : source->mouse_up_callbacks)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			script_engine->CompileMethod(&v, method.c_str());
		}
		for (auto& v : source->mouse_down_callbacks)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			script_engine->CompileMethod(&v, method.c_str());
		}
		for (auto& v : source->mouse_move_callbacks)
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			script_engine->CompileMethod(&v, method.c_str());
		}
		for (auto& k : source->classes)
		{
			TBaluClassInstance::CheckScriptErrors(k.second.get(), script_engine, errors_list);
		}
	}
	catch (std::string ex)
	{
		errors_list = script_engine->GetErrors();
		return false;
	}
	return true;
}

void TBaluWorldInstance::ViewportResize(TDirector* director, TVec2i old_size, TVec2i new_size)
{
	for (auto& v : viewport_resize_callback)
		script_engine.CallViewportResize(v, director, old_size, new_size);
}
