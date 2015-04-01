
#include "ScriptClassesRegistry.h"
#include "CppToBaluScriptBinding.h"

//generate script bindings
#define BALU_ENGINE_SCRIPT_CLASSES

#include "EngineInterfacesIncludes.h"
//
using namespace EngineInterface;


void IBaluInstance_register(TClassRegistryParams& params)
{
	std::vector<Unpacker*> methods;
	methods.push_back(SetName("GetProperties", new UnpackR<IProperties, WrapPointer<IBaluInstance>, &IBaluInstance::GetProperties>));
	methods.push_back(SetName("GetPhysBody", new UnpackR<IBaluClassPhysBodyIntance, WrapPointer<IBaluInstance>, &IBaluInstance::GetPhysBody>));

	auto scl = RegisterExternClass2(params, "IClassInstance", sizeof(IBaluInstance*), methods);
}
static bool IBaluInstance_registered = TScriptClassesRegistry::Register("IClassInstance", IBaluInstance_register);