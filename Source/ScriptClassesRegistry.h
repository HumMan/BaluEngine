#pragma once

#include <baluScript.h>

class Unpacker
{
protected:
	const char* func_name;
public:
	
	virtual TExternalSMethod GetUnpackMethod() = 0;
	virtual std::string GetSyntax() = 0;
	const char* GetFuncName()
	{
		return func_name;
	}
	void SetFuncName(const char* func_name)
	{
		this->func_name = func_name;
	}
};

class TClassRegistryParams
{
public:
	TSyntaxAnalyzer* syntax;
	std::vector<TStaticValue> *static_objects;
	std::vector < std::unique_ptr<TSMethod>> *smethods;
};

typedef void(*RegisterScriptClass)(TClassRegistryParams& params);

TSClass* RegisterExternClass(TClassRegistryParams& params, const char* source, int size);
TSClass* RegisterClass(TClassRegistryParams& params, const char* source);
void RegisterMethod(TClassRegistryParams& params, TSClass* class_syntax, const char* name, TExternalSMethod func);

void RegisterMethod2(TClassRegistryParams& params, TSClass* class_syntax, Unpacker* method);
TSClass* RegisterExternClass2(TClassRegistryParams& params, const char* name, int size, std::vector<Unpacker*> methods);
Unpacker* SetName(const char* name, Unpacker* method);

class TScriptClassesRegistry
{
public:
	static bool Register(const char* name, RegisterScriptClass reg);
	static void RegisterClassesInScript(TClassRegistryParams& params);
	static void Clear();
};