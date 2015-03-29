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

TBaluScriptInstance::TBaluScriptInstance()
{
	time.Start();

	char* script_base_source;
	{
		TFileData file("../../BaluScript/Source/NativeTypes/base_types.bscript", "rb");
		script_base_source = file.ReadAll();
		script_base_source[file.GetSize()] = '\0';
	}
	syntax.reset(new TSyntaxAnalyzer());
	syntax->Compile((char*)(("class Script{" + std::string(script_base_source) + "}").c_str()), time);

	TClassRegistryParams params;
	params.smethods = &smethods;
	params.static_objects = &static_objects;
	params.syntax = syntax.get();
	TScriptClassesRegistry::RegisterClassesInScript(params);
}

void TBaluScriptInstance::CreateMethod(TScriptData* script_data, const char* code)
{
	try
	{
		TMethod* m = new TMethod(syntax->base_class.get());
		syntax->lexer.ParseSource(code);
		m->AnalyzeSyntax(syntax->lexer);
		syntax->lexer.GetToken(TTokenType::Done);

		TSMethod* ms = new TSMethod(syntax->sem_base_class.get(), m);
		smethods.push_back(std::unique_ptr<TSMethod>(ms));
		ms->Build();

		std::vector<TSClassField*> static_fields;
		std::vector<TSLocalVar*> static_variables;

		ms->LinkSignature(&static_fields, &static_variables);
		ms->LinkBody(&static_fields, &static_variables);
		ms->CalculateParametersOffsets();

		std::vector<TSClass*> owners;
		syntax->sem_base_class->CalculateSizes(owners);

		InitializeStaticClassFields(static_fields, static_objects);
		InitializeStaticVariables(static_variables, static_objects);

		script_data->SetCompiledScript(ms, this);
	}
	catch (std::string s)
	{
		errors.push_back(s);
	}
}

TBaluWorld* TBaluWorldInstance::GetSource()
{
	return source;
}

TBaluWorldInstance::TBaluWorldInstance(TBaluWorld* source, TResources* resources)
{
	this->source = source;
	this->resources = resources;


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

void TBaluWorldInstance::CompileScripts()
{
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
				std::string method = std::string("") 
					+ method_body 
					+ "";
				script_engine.CreateMethod(&v, method.c_str());
			}
		}
		for (auto& s : k.second.on_key_down_callbacks)
		{
			for (auto& v: s.second)
			if (v.IsScript())
			{
				auto method_body = v.GetScriptSource();
				std::string method = std::string("func static KeyDown(Key key, IClassInstance instance)\n{\n") + method_body + "\n}\n";
				script_engine.CreateMethod(&v, method.c_str());
			}
		}
		for (auto& s : k.second.on_key_up_callbacks)
		{
			for (auto& v : s.second)
				if (v.IsScript())
				{
					auto method_body = v.GetScriptSource();
					std::string method = std::string("") + method_body + "";
					script_engine.CreateMethod(&v, method.c_str());
				}
		}
	}
}

void TBaluWorldInstance::ViewportResize(TDirector* director, TVec2i old_size, TVec2i new_size)
{
	if (GetSource()->viewport_resize_callback.IsScript())
		GetSource()->viewport_resize_callback.GetScriptEngine()->CallMethod(GetSource()->viewport_resize_callback, director, old_size, new_size);
	else
		GetSource()->viewport_resize_callback.Execute(director, old_size, new_size);
}

void TBaluWorldInstance::Render(TDirector* director, TRender* render)
{
	if (GetSource()->render_world_callback.IsScript())
		GetSource()->render_world_callback.GetScriptEngine()->CallMethod(GetSource()->render_world_callback, director, this, render);
	else
		GetSource()->render_world_callback.Execute(director, this, render);
}
