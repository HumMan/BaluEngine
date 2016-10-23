#include <Scripts/ScriptClassesRegistry.h>

using namespace::BaluLib;

#include "CppToBaluScriptBinding.h"

namespace EngineInterface
{
	DECL_SCRIPT_TYPE(int, "int");
	DECL_SCRIPT_TYPE(float, "float");
	DECL_SCRIPT_TYPE(bool, "bool");
	DECL_SCRIPT_TYPE(TVec2, "vec2");
	DECL_SCRIPT_TYPE(TVec2i, "vec2i");
	DECL_SCRIPT_TYPE(std::string, "string");
}

#include "EngineInterfacesIncludes.h"
namespace EngineInterface
{
#include <WorldInstance/BindingIncludes.h>
}
