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

	CompileScripts();

	for (auto& v : source->on_start_world_callback)
		v.Execute(this, &composer);
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
		v.Execute(&e);
	}
}

void TBaluWorldInstance::MouseMove(TMouseEventArgs e)
{
	for (auto& v : source->mouse_move_callbacks)
	{
		v.Execute(&e);
	}
}

void TBaluWorldInstance::MouseUp(TMouseEventArgs e)
{
	for (auto& v : source->mouse_up_callbacks)
	{
		v.Execute(&e);
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

void TBaluWorldInstance::CompileScripts()
{
	for(auto& v:source->on_start_world_callback)
	{
		if (v.IsScript())
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static StartWorld(IWorldInstance world_instance, IComposer composer)\n{\n") + method_body + "\n}\n";
			script_engine.CreateMethod(&v, method.c_str());
		}
	}
	for (auto& v : source->viewport_resize_callback)
	{
		if (v.IsScript())
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("func static ViewportResize(IDirector director, vec2i old_size, vec2i new_size)\n{\n") + method_body + "\n}\n";
			script_engine.CreateMethod(&v, method.c_str());
		}
	}

	for (auto& v : source->mouse_up_callbacks)
	{
		if (v.IsScript())
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			script_engine.CreateMethod(&v, method.c_str());
		}
	}
	for (auto& v : source->mouse_down_callbacks)
	{
		if (v.IsScript())
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			script_engine.CreateMethod(&v, method.c_str());
		}
	}
	for (auto& v : source->mouse_move_callbacks)
	{
		if (v.IsScript())
		{
			auto method_body = v.GetScriptSource();
			std::string method = std::string("") + method_body + "";
			script_engine.CreateMethod(&v, method.c_str());
		}
	}
	for (auto& k : source->classes)
	{
		for (auto& v : k.second.before_physics_callbacks)
		{
			if (v.IsScript())
			{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("func static BeforePhys(IInstance object)\n{\n") + method_body + "\n}\n";
				script_engine.CreateMethod(&v, method.c_str());
			}
		}
		for (auto& s : k.second.on_key_down_callbacks)
		{
			for (auto& v: s.second)
			if (v.IsScript())
			{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("func static KeyDown(IInstance object)\n{\n") + method_body + "\n}\n";
				script_engine.CreateMethod(&v, method.c_str());
			}
		}
		for (auto& s : k.second.on_key_up_callbacks)
		{
			for (auto& v : s.second)
				if (v.IsScript())
				{
					auto method_body = v.GetScriptSource();
					std::string method = std::string("func static KeyUp(IInstance object)\n{\n") + method_body + "\n}\n";
					script_engine.CreateMethod(&v, method.c_str());
				}
		}
	}

	for (auto& k : source->sprites)
	{
		for(auto& v :k.second.collide_callbacks)
		{
			if (v.second.IsScript())
			{
				auto method_body = v.second.GetScriptSource();
				std::string method = std::string("func static Collide(IPhysShapeInstance source, IInstance obstancle)\n{\n") + method_body + "\n}\n";
				script_engine.CreateMethod(&v.second, method.c_str());
			}
		}
	}
}

void TBaluWorldInstance::ViewportResize(TDirector* director, TVec2i old_size, TVec2i new_size)
{
	for (auto& v : GetSource()->viewport_resize_callback)
		v.Execute(director, old_size, new_size);
}
