#include "ICallbacks.h"

using namespace EngineInterface;

TScript::TScript()
{
	script_type = TScriptActiveType::DEFAULT;
}
TScript::TScript(std::string script_source)
{
	script_type = TScriptActiveType::DEFAULT;
	this->script_source = script_source;
}
TScript::TScript(std::string script_source, TScriptActiveType script_type)
{
	this->script_type = script_type;
	this->script_source = script_source;
}
TScriptActiveType TScript::GetScriptType()
{
	return script_type;
}
void TScript::SetScriptType(TScriptActiveType type)
{
	this->script_type = type;
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