#include "ScriptClassesRegistry.h"

#include "../Source/Semantic/SMethod.h"
#include "../Source/Semantic/SClass.h"
#include "../Source/Semantic/FormalParam.h"
#include "../Source/Semantic/SStatements.h"
#include "../Source/Syntax/Statements.h"
#include "../Source/Syntax/Method.h"
#include "../Source/semanticAnalyzer.h"

std::vector < std::pair<const char*, RegisterScriptClass>> script_class_registry;

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
