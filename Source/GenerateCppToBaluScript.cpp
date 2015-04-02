#include "ScriptClassesRegistry.h"
#include "CppToBaluScriptBinding.h"

namespace EngineInterface
{
	DECL_SCRIPT_TYPE(int, "int");
	DECL_SCRIPT_TYPE(float, "float");
	DECL_SCRIPT_TYPE(TVec2, "vec2");
	DECL_SCRIPT_TYPE(TVec2i, "vec2i");
	DECL_SCRIPT_TYPE(string, "string");
}

//generate script bindings
#define BALU_ENGINE_SCRIPT_CLASSES
#pragma push_macro("new")
#undef new

#include "EngineInterfacesIncludes.h"

#pragma pop("new")