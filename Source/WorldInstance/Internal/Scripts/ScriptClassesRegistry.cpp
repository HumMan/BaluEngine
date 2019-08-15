#include "ScriptClassesRegistry.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;


//https://isocpp.org/wiki/faq/ctors#static-init-order-on-first-use
std::vector <TExternalClassInfo>& TScriptClassesRegistry::get_external_class_registry()
{
	static std::vector <TExternalClassInfo> external_class_registry;
	return external_class_registry;
}

std::vector <TEnumInfo>& TScriptClassesRegistry::get_enum_registry()
{
	static std::vector <TEnumInfo> enum_registry;
	return enum_registry;
}

void TScriptClassesRegistry::RegisterExternal(const char* source, const char* name, size_t size, bool is_interface, bool is_shared, const char* c_name)
{
	get_external_class_registry().push_back(TExternalClassInfo(source,name, size, is_interface, is_shared, c_name));
}

void TScriptClassesRegistry::RegisterEnum(const char* source, const char* name, const char* c_name)
{
	get_enum_registry().push_back(TEnumInfo(source,name, c_name));
}