#include "ScriptClassesRegistry.h"

#include "../Source/Semantic/SMethod.h"
#include "../Source/Semantic/SClass.h"
#include "../Source/Semantic/FormalParam.h"
#include "../Source/Semantic/SStatements.h"
#include "../Source/Syntax/Statements.h"
#include "../Source/Syntax/Method.h"
#include "../Source/semanticAnalyzer.h"

//https://isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
std::vector < std::unique_ptr<TClassBinding>>& get_script_class_registry()
{
	static std::vector <std::unique_ptr<TClassBinding>> script_class_registry;
	return script_class_registry;
}

std::vector < std::pair<const char*, RegisterScriptClass>>& get_script_enum_registry()
{
	static std::vector < std::pair<const char*, RegisterScriptClass>> script_enum_registry;
	return script_enum_registry;
}

TSClass* RegisterEnum(TClassRegistryParams& params, const char* source)
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

	TGlobalBuildContext global_build_context(&static_fields, &static_variables);

	scl->LinkSignature(global_build_context);
	scl->InitAutoMethods();
	scl->LinkBody(global_build_context);
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

std::string BuildExternClassSource(const char* name, std::vector<std::unique_ptr<Unpacker>>& methods)
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

void DeclareMethod(TClassRegistryParams& params, TSClass* class_syntax, Unpacker* method)
{
	std::vector<TSMethod*> m;
	auto& syntax = params.syntax;
	m.clear();
	if (method->IsConstructor())
	{
		class_syntax->GetCopyConstructors(m);
		m[0]->SetAsExternal(method->GetUnpackMethod());
	}
	else
	{
		class_syntax->GetMethods(m, syntax->lexer.GetIdFromName(method->GetFuncName()));
		m[0]->SetAsExternal(method->GetUnpackMethod());
	}
}

void DeclareExternClass(TClassRegistryParams& params, TClassBinding* binding)
{
	std::string source = BuildExternClassSource(binding->class_name, binding->methods);

	auto& syntax = params.syntax;
	TClass* cl = new TClass(syntax->base_class.get());
	syntax->base_class->AddNested(cl);
	syntax->lexer.ParseSource(source.c_str());
	cl->AnalyzeSyntax(syntax->lexer);
	syntax->lexer.GetToken(TTokenType::Done);

	binding->compiled = new TSClass(syntax->sem_base_class.get(), cl);
	syntax->sem_base_class->AddClass(binding->compiled);
	binding->compiled->Build();

	binding->compiled->SetSize(IntSizeOf(binding->size) / sizeof(int));
	//binding->compiled->SetAutoMethodsInitialized();
}

void BuildExternClass(TClassRegistryParams& params, TClassBinding* binding)
{
	std::vector<TSClassField*> static_fields;
	std::vector<TSLocalVar*> static_variables;

	TGlobalBuildContext global_build_context(&static_fields, &static_variables);

	binding->compiled->LinkSignature(global_build_context);
	binding->compiled->InitAutoMethods();
	binding->compiled->CalculateMethodsSizes();

	for (auto& v : binding->methods)
	{
		DeclareMethod(params, binding->compiled, v.get());
	}
}

void TScriptClassesRegistry::RegisterClassBinding(TClassBinding* binding)
{
	get_script_class_registry().push_back(std::unique_ptr<TClassBinding>(binding));
}

Unpacker* SetName(const char* name, Unpacker* method)
{
	method->SetFuncName(name);
	return method;
}

Unpacker* SetAsConstructor(Unpacker* method)
{
	method->SetAsConstructor();
	return method;
}

bool TScriptClassesRegistry::RegisterEnum(const char* name, RegisterScriptClass reg)
{
	get_script_enum_registry().push_back(std::pair<const char*, RegisterScriptClass>(name, reg));
	return true;
}

void TScriptClassesRegistry::RegisterClassesInScript(TClassRegistryParams& params)
{
	for (auto& v : get_script_enum_registry())
	{
		v.second(params);
	}

	for (auto& v : get_script_class_registry())
	{
		DeclareExternClass(params, v.get());
	}

	for (auto& v : get_script_class_registry())
	{
		BuildExternClass(params, v.get());
	}
}