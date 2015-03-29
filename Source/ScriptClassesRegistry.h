#pragma once

#include "baluScript.h"

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

class TScriptClassesRegistry
{
public:
	static bool Register(const char* name, RegisterScriptClass reg);
	static void RegisterClassesInScript(TClassRegistryParams& params);
};