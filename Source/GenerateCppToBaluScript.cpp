#include "ScriptClassesRegistry.h"
#include "CppToBaluScriptBinding.h"

namespace EngineInterface
{
	DECL_SCRIPT_TYPE(int, "int");
}

//generate script bindings
#define BALU_ENGINE_SCRIPT_CLASSES

#include "EngineInterfacesIncludes.h"

using namespace EngineInterface;

void IBaluInstance_register(TClassRegistryParams& params)
{
	std::vector<Unpacker*> methods;
	MUnpackRp(IProperties, IBaluInstance, GetProperties);
	MUnpackRp(IBaluClassPhysBodyIntance, IBaluInstance, GetPhysBody);
	MUnpackRpv(IBaluSpriteInstance, IBaluInstance, GetSprite, int);

	auto scl = RegisterExternClass2(params, "IClassInstance", sizeof(WrapPointer<IBaluInstance>), methods);
}
static bool IBaluInstance_registered = TScriptClassesRegistry::Register("IClassInstance", IBaluInstance_register);