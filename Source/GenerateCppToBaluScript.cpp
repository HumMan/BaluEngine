#include "ScriptClassesRegistry.h"
#include "CppToBaluScriptBinding.h"



//generate script bindings
#define BALU_ENGINE_SCRIPT_CLASSES

#include "EngineInterfacesIncludes.h"

namespace EngineInterface
{
	DECL_SCRIPT_TYPE(int, "int");
	DECL_SCRIPT_TYPE(TBaluTransform, "TTransform");
}

using namespace EngineInterface;

void IBaluInstance_register(TClassRegistryParams& params)
{
	std::vector<Unpacker*> methods;

	//short macro
	//MUnpackRp(IProperties, IBaluInstance, GetProperties);
	//MUnpackRp(IBaluClassPhysBodyIntance, IBaluInstance, GetPhysBody);
	//MUnpackRpv(IBaluSpriteInstance, IBaluInstance, GetSprite, int);

	//macro
	MUnpackRA0(WrapPointer, IProperties, IBaluInstance, GetProperties);
	MUnpackRA0(WrapPointer, IBaluClassPhysBodyIntance, IBaluInstance, GetPhysBody);
	MUnpackRA1(WrapPointer, IBaluSpriteInstance, IBaluInstance, GetSprite, WrapValue, int);
	MUnpackRA1(WrapPointer, IBaluSpriteInstance, IBaluInstance, GetSprite, WrapValue, int);
	MUnpackRA1(WrapPointer, IBaluSpriteInstance, IBaluInstance, GetSprite, WrapValue, int);
	MUnpackA1(IBaluInstance, SetTransform, WrapValue, TBaluTransform);

	auto scl = RegisterExternClass2(params, "IClassInstance", sizeof(WrapPointer<IBaluInstance>), methods);
}
static bool IBaluInstance_registered = TScriptClassesRegistry::Register("IClassInstance", IBaluInstance_register);