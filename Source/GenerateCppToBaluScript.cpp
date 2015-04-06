#include "ScriptClassesRegistry.h"
#include "CppToBaluScriptBinding.h"

namespace EngineInterface
{
	DECL_SCRIPT_TYPE(int, "int");
	DECL_SCRIPT_TYPE(float, "float");
	DECL_SCRIPT_TYPE(bool, "bool");
	DECL_SCRIPT_TYPE(TVec2, "vec2");
	DECL_SCRIPT_TYPE(TVec2i, "vec2i");
	DECL_SCRIPT_TYPE(string, "string");
}

#define BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "EngineInterfacesIncludes.h"

//generate script bindings
#define BALU_ENGINE_SCRIPT_CLASSES
#include "EngineInterfacesIncludes.h"