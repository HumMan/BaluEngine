#include "IScriptInstance.h"

#include "baluScript.h"

#include <WorldObjects/Class/IClassInstance.h>
#include <World/IWorld.h>

#include "ScriptClassesRegistry.h"

#include <iostream>
#include <fstream>

using namespace EngineInterface;

namespace EngineInterface
{
	class TBaluScriptInstancePrivate
	{
	public:
		std::unique_ptr<TSyntaxAnalyzer> syntax;
		std::vector<TStaticValue> static_objects;
		std::vector < std::unique_ptr<TSMethod>> smethods;
		std::vector<std::string> errors;

		TTime time;
	};
}

TBaluScriptInstance::~TBaluScriptInstance()
{
}

TBaluScriptInstance::TBaluScriptInstance(std::string assets_dir)
{
	p = std::unique_ptr<TBaluScriptInstancePrivate>(new TBaluScriptInstancePrivate());

	p->time.Start();

	std::string script_base_source;
	{
		std::ifstream file;
		file.open((assets_dir + "//" + "scripts/base_types.bscript").c_str());

		std::string str;

		file.seekg(0, std::ios::end);
		str.reserve(file.tellg());
		file.seekg(0, std::ios::beg);

		str.assign((std::istreambuf_iterator<char>(file)),
			std::istreambuf_iterator<char>());

		script_base_source = str;
	}
	p->syntax.reset(new TSyntaxAnalyzer());
	p->syntax->Compile((char*)(("class Script{" + script_base_source + "}").c_str()), p->time);

	TClassRegistryParams params;
	params.smethods = &p->smethods;
	params.static_objects = &p->static_objects;
	params.syntax = p->syntax.get();
	TScriptClassesRegistry::RegisterClassesInScript(params);
}

EngineInterface::TScriptInstance TBaluScriptInstance::CompileMethod(TScript* script_data, const char* code)
{
	try
	{
		TMethod* m = new TMethod(p->syntax->base_class.get());
		p->syntax->lexer.ParseSource(code);
		m->AnalyzeSyntax(p->syntax->lexer);
		p->syntax->lexer.GetToken(TTokenType::Done);

		TSMethod* ms = new TSMethod(p->syntax->sem_base_class.get(), m);
		p->smethods.push_back(std::unique_ptr<TSMethod>(ms));
		ms->Build();

		std::vector<TSClassField*> static_fields;
		std::vector<TSLocalVar*> static_variables;

		TGlobalBuildContext global_build_context(&static_fields, &static_variables);

		ms->LinkSignature(global_build_context);
		ms->LinkBody(global_build_context);
		ms->CalculateParametersOffsets();

		std::vector<TSClass*> owners;
		p->syntax->sem_base_class->CalculateSizes(owners);

		InitializeStaticClassFields(static_fields, p->static_objects);
		InitializeStaticVariables(static_variables, p->static_objects);


		return TScriptInstance(script_data, ms);
	}
	catch (std::string s)
	{
		p->errors.push_back(s);
		throw;
	}
}

bool TBaluScriptInstance::HasErrors()
{
	return p->errors.size() >= 0;
}
std::vector<std::string> TBaluScriptInstance::GetErrors()
{
	return p->errors;
}

void TBaluScriptInstance::CallViewportResize(TScriptInstance &viewport_resize_callback, EngineInterface::IDirector* director, TVec2i old_size, TVec2i new_size)
{
	std::vector<TStackValue> params;
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IDirector"))));
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("vec2i"))));
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("vec2i"))));
	*(EngineInterface::IDirector**)params[0].get() = director;
	*(TVec2i*)params[1].get() = old_size;
	*(TVec2i*)params[2].get() = new_size;
	TStackValue result, object;
	viewport_resize_callback.GetCompiledScript()->Run(TMethodRunContext(&p->static_objects, &params, &result, &object));
}
void TBaluScriptInstance::CallWorldStart(TScriptInstance &start_world_callback, EngineInterface::IBaluWorldInstance* world_instance, EngineInterface::IComposer* composer)
{
	std::vector<TStackValue> params;
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IWorldInstance"))));
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IComposer"))));
	*(EngineInterface::IBaluWorldInstance**)params[0].get() = world_instance;
	*(EngineInterface::IComposer**)params[1].get() = composer;

	TStackValue result, object;
	start_world_callback.GetCompiledScript()->Run(TMethodRunContext(&p->static_objects, &params, &result, &object));
}
void TBaluScriptInstance::CallInstanceEvent(TScriptInstance &callback, IBaluTransformedClassInstance* obj)
{
	std::vector<TStackValue> params;
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IInstance"))));
	*(EngineInterface::IBaluTransformedClassInstance**)params[0].get() = obj;

	TStackValue result, object;
	callback.GetCompiledScript()->Run(TMethodRunContext(&p->static_objects, &params, &result, &object));
}

void TBaluScriptInstance::CallMouseEvent(TScriptInstance &callback, TMouseEventArgs* e)
{
	std::vector<TStackValue> params;
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("TMouseEventArgs"))));
	params[0].get_as<EngineInterface::TMouseEventArgs>() = *e;

	TStackValue result, object;
	callback.GetCompiledScript()->Run(TMethodRunContext(&p->static_objects, &params, &result, &object));
}

void TBaluScriptInstance::CallCollide(EngineInterface::TScriptInstance &callback, IBaluTransformedClassInstance* source_object, IBaluTransformedSpriteInstance* obj_a, IBaluTransformedClassInstance* obj_b)
{
	//TODO присвоение параметров с использованием wrapper классов
	std::vector<TStackValue> params;
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IInstance"))));
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IClassInstanceSpriteInstance"))));
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IInstance"))));
	params[0].get_as<IBaluTransformedClassInstance*>() = source_object;
	params[1].get_as<IBaluTransformedSpriteInstance*>() = obj_a;
	params[2].get_as<IBaluTransformedClassInstance*>() = obj_b;

	TStackValue result, object;
	callback.GetCompiledScript()->Run(TMethodRunContext(&p->static_objects, &params, &result, &object));
}
