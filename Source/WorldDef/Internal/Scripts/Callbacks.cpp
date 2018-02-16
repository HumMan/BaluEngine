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
