#include "ScriptClassesRegistry.h"

#include "../Source/Semantic/SMethod.h"
#include "../Source/Semantic/SClass.h"
#include "../Source/Semantic/FormalParam.h"
#include "../Source/Semantic/SStatements.h"
#include "../Source/Syntax/Statements.h"
#include "../Source/Syntax/Method.h"
#include "../Source/semanticAnalyzer.h"

//std::vector < std::pair<const char*, RegisterScriptClass>> script_class_registry;


std::vector < std::pair<const char*, RegisterScriptClass>>& get_script_class_registry()
{
	static std::vector < std::pair<const char*, RegisterScriptClass>> script_class_registry;// = new std::vector < std::pair<const char*, RegisterScriptClass>>();
	return script_class_registry;
}

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



void RegisterMethod2(TClassRegistryParams& params, TSClass* class_syntax, Unpacker* method)
{
	std::vector<TSMethod*> m;
	auto& syntax = params.syntax;
	m.clear();
	class_syntax->GetMethods(m, syntax->lexer.GetIdFromName(method->GetFuncName()));
	m[0]->SetAsExternal(method->GetUnpackMethod());
}

std::string BuildExternClassSource(const char* name, std::vector<Unpacker*> methods)
{
	std::string result;
	result += (std::string("class extern ") + name + "\n{\n");
	for (auto& v : methods)
	{
		result += v->GetSyntax() + "\n";
	}
	result += "\n}\n";
	return result;
}

TSClass* RegisterExternClass2(TClassRegistryParams& params, const char* name, int size, std::vector<Unpacker*> methods)
{
	std::string source = BuildExternClassSource(name, methods);

	auto& syntax = params.syntax;
	TClass* cl = new TClass(syntax->base_class.get());
	syntax->base_class->AddNested(cl);
	syntax->lexer.ParseSource(source.c_str());
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

	for (auto& v : methods)
	{
		RegisterMethod2(params, scl, v);
	}

	return scl;
}

Unpacker* SetName(const char* name, Unpacker* method)
{
	method->SetFuncName(name);
	return method;
}

bool TScriptClassesRegistry::Register(const char* name, RegisterScriptClass reg)
{
	get_script_class_registry().push_back(std::pair<const char*, RegisterScriptClass>(name, reg));
	return true;
}

void TScriptClassesRegistry::RegisterClassesInScript(TClassRegistryParams& params)
{
	for (int i = 0; i < get_script_class_registry().size(); i++)
	{
		get_script_class_registry()[i].second(params);
	}
}

void TScriptClassesRegistry::Clear()
{
	//TODO
}