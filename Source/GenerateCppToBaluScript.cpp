#include "ScriptClassesRegistry.h"
#include "CppToBaluScriptBinding.h"

//generate script bindings
#define BALU_ENGINE_SCRIPT_CLASSES

#include "EngineInterfacesIncludes.h"

using namespace EngineInterface;

void IBaluInstance_register(TClassRegistryParams& params)
{
	std::vector<Unpacker*> methods;
	MUnpackRp(IProperties, IBaluInstance, GetProperties);
	MUnpackRp(IBaluClassPhysBodyIntance, IBaluInstance, GetPhysBody);
	//methods.push_back(SetName("GetProperties", new UnpackR<WrapPointer<IProperties>, IProperties*, WrapPointer<IBaluInstance>, &IBaluInstance::GetProperties>));
	//methods.push_back(SetName("GetPhysBody", new UnpackR<WrapPointer<IBaluClassPhysBodyIntance>, IBaluClassPhysBodyIntance*, WrapPointer<IBaluInstance>, &IBaluInstance::GetPhysBody>));

	//methods.push_back(SetName("GetPhysBody", new UnpackRA1<WrapPointer<IBaluSpriteInstance>, IBaluSpriteInstance*, WrapPointer<IBaluInstance>, WrapValue<int>, int, &IBaluInstance::GetSprite >));
	//IBaluSpriteInstance* GetSprite(int index)

	auto scl = RegisterExternClass2(params, "IClassInstance", sizeof(WrapPointer<IBaluInstance>), methods);
}
static bool IBaluInstance_registered = TScriptClassesRegistry::Register("IClassInstance", IBaluInstance_register);