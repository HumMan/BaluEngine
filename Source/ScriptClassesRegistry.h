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

class TScriptClassesRegistry
{
public:
	static bool Register(const char* name, RegisterScriptClass reg);
	static void RegisterClassesInScript(TClassRegistryParams& params);
};