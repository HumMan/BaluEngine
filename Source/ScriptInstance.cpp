#include "ScriptInstance.h"

#include "baluScript.h"

#include "ClassInstance.h"
#include "EngineInterfaces\IWorld.h"

#include "ScriptClassesRegistry.h"

using namespace EngineInterface;

class TBaluScriptInstancePrivate
{
public:
	std::unique_ptr<TSyntaxAnalyzer> syntax;
	std::vector<TStaticValue> static_objects;
	std::vector < std::unique_ptr<TSMethod>> smethods;
	std::vector<std::string> errors;

	TScriptActiveType script_type_to_run;

	TTime time;
};

TBaluScriptInstance::~TBaluScriptInstance()
{
}

TBaluScriptInstance::TBaluScriptInstance(std::string assets_dir, TScriptActiveType script_type_to_run)
{
	p = std::make_unique<TBaluScriptInstancePrivate>();

	p->script_type_to_run = script_type_to_run;
	p->time.Start();

	char* script_base_source;
	{
		TFileData file((assets_dir+"//"+"scripts/base_types.bscript").c_str(), "rb");

		script_base_source = file.ReadAll();
		script_base_source[file.GetSize()] = '\0';
	}
	p->syntax.reset(new TSyntaxAnalyzer());
	p->syntax->Compile((char*)(("class Script{" + std::string(script_base_source) + "}").c_str()), p->time);

	delete script_base_source;

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
	if (viewport_resize_callback.GetSource()->GetScriptType() != this->p->script_type_to_run)
		return;
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
	if (start_world_callback.GetSource()->GetScriptType() != this->p->script_type_to_run)
		return;
	std::vector<TStackValue> params;
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IWorldInstance"))));
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IComposer"))));
	*(EngineInterface::IBaluWorldInstance**)params[0].get() = world_instance;
	*(EngineInterface::IComposer**)params[1].get() = composer;

	TStackValue result, object;
	start_world_callback.GetCompiledScript()->Run(TMethodRunContext(&p->static_objects, &params, &result, &object));
}
void TBaluScriptInstance::CallInstanceEvent(TScriptInstance &callback, IBaluInstance* obj)
{
	if (callback.GetSource()->GetScriptType() != this->p->script_type_to_run)
		return;
	std::vector<TStackValue> params;
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IInstance"))));
	*(EngineInterface::IBaluInstance**)params[0].get() = obj;

	TStackValue result, object;
	callback.GetCompiledScript()->Run(TMethodRunContext(&p->static_objects, &params, &result, &object));
}

void TBaluScriptInstance::CallMouseEvent(TScriptInstance &callback, EngineInterface::TMouseEventArgs* e)
{
	if (callback.GetSource()->GetScriptType() != this->p->script_type_to_run)
		return;
	std::vector<TStackValue> params;
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("TMouseEventArgs"))));
	params[0].get_as<EngineInterface::TMouseEventArgs>() = *e;

	TStackValue result, object;
	callback.GetCompiledScript()->Run(TMethodRunContext(&p->static_objects, &params, &result, &object));
}

void TBaluScriptInstance::CallCollide(EngineInterface::TScriptInstance &callback, EngineInterface::IBaluPhysShapeInstance* obj_a, EngineInterface::IBaluInstance* obj_b)
{
	if (callback.GetSource()->GetScriptType() != this->p->script_type_to_run)
		return;
	std::vector<TStackValue> params;
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IPhysShapeInstance"))));
	params.push_back(TStackValue(false, p->syntax->sem_base_class->GetClass(p->syntax->lexer.GetIdFromName("IInstance"))));
	params[0].get_as<IBaluPhysShapeInstance*>() = obj_a;
	params[1].get_as<IBaluInstance*>() = obj_b;

	TStackValue result, object;
	callback.GetCompiledScript()->Run(TMethodRunContext(&p->static_objects, &params, &result, &object));
}