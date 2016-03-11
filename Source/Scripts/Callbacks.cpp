#include "ICallbacks.h"

using namespace EngineInterface;

TScript::TScript()
{
}
TScript::TScript(std::string script_source)
{
	this->script_source = script_source;
}
std::string TScript::GetScriptSource()
{
	return script_source;
}
void TScript::SetScriptSource(const char* source)
{
	script_source = source;
}

TScript* TScriptInstance::GetSource()
{
	return source;
}
TScriptInstance::TScriptInstance()
{
	source = nullptr;
	compiled_script = nullptr;
}
TScriptInstance::TScriptInstance(TScript* source, TSMethod* compiled_script)
{
	this->source = source;
	this->compiled_script = compiled_script;
}
TSMethod* TScriptInstance::GetCompiledScript()
{
	assert(compiled_script != nullptr);
	return compiled_script;
}