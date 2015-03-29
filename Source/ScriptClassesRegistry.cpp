#include "ScriptClassesRegistry.h"

#include "../Source/Semantic/SMethod.h"
#include "../Source/Semantic/SClass.h"
#include "../Source/Semantic/FormalParam.h"
#include "../Source/Semantic/SStatements.h"
#include "../Source/Syntax/Statements.h"
#include "../Source/Syntax/Method.h"
#include "../Source/semanticAnalyzer.h"

std::vector < std::pair<const char*, RegisterScriptClass>> script_class_registry;

TSClass* RegisterExternClass(TClassRegistryParams& params, const char* source, int size)
{
	auto& syntax = params.syntax;
	TClass* cl = new TClass(syntax->base_class.get());
	syntax->base_class->AddNested(cl);
	syntax->lexer.ParseSource(source);
	cl->AnalyzeSyntax(syntax->lexer);
	syntax->lexer.GetToken(TTokenType::Done);

	TSClass* scl = new TSClass(syntax->sem_base_class.get(), cl);
	syntax->sem_base_class->AddClass(scl);
	scl->Build();

	scl->SetSize(IntSizeOf(size) / sizeof(int));
	scl->SetAutoMethodsInitialized();

	std::vector<TSClassField*> static_fields;
	std::vector<TSLocalVar*> static_variables;

	scl->LinkSignature(&static_fields, &static_variables);
	scl->CalculateMethodsSizes();

	return scl;
}

TSClass* RegisterClass(TClassRegistryParams& params, const char* source)
{
	auto syntax = params.syntax;
	TClass* cl = new TClass(syntax->base_class.get());
	syntax->base_class->AddNested(cl);
	syntax->lexer.ParseSource(source);
	cl->AnalyzeSyntax(syntax->lexer);
	syntax->lexer.GetToken(TTokenType::Done);

	TSClass* scl = new TSClass(syntax->sem_base_class.get(), cl);
	syntax->sem_base_class->AddClass(scl);
	scl->Build();

	std::vector<TSClassField*> static_fields;
	std::vector<TSLocalVar*> static_variables;

	scl->LinkSignature(&static_fields, &static_variables);
	scl->InitAutoMethods();
	scl->LinkBody(&static_fields, &static_variables);
	scl->CheckForErrors();

	std::vector<TSClass*> owners;
	scl->CalculateSizes(owners);
	scl->CalculateMethodsSizes();

	owners.clear();
	syntax->sem_base_class->CalculateSizes(owners);//т.к. в этом классе могут использоваться другие шаблонные класса, реализацию которых нужно обновить

	InitializeStaticClassFields(static_fields, *params.static_objects);
	InitializeStaticVariables(static_variables, *params.static_objects);

	return scl;
}

void RegisterMethod(TClassRegistryParams& params, TSClass* class_syntax, const char* name, TExternalSMethod func)
{
	std::vector<TSMethod*> m;
	auto& syntax = params.syntax;
	m.clear();
	class_syntax->GetMethods(m, syntax->lexer.GetIdFromName(name));
	m[0]->SetAsExternal(func);
}

bool TScriptClassesRegistry::Register(const char* name, RegisterScriptClass reg)
{
	script_class_registry.push_back(std::pair<const char*, RegisterScriptClass>(name, reg));
	return true;
}

void TScriptClassesRegistry::RegisterClassesInScript(TClassRegistryParams& params)
{
	for (int i = 0; i < script_class_registry.size(); i++)
	{
		script_class_registry[i].second(params);
	}
}

#define BALU_ENGINE_SCRIPT_CLASSES

#include "EngineInterfacesIncludes.h"
