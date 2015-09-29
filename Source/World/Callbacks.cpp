#include "ICallbacks.h"


#pragma once

#include <string>
#include <assert.h>

#include "EngineInterfaces\ICallbacks.h"

class TSMethod;
class TBaluScriptInstance;
class NVGcontext;

namespace pugi
{
	class xml_node;
}

namespace EngineInterface
{

	enum class TScriptActiveType
	{
		DEFAULT = 0,
		EDITOR = 1
	};

	class TScript
	{
	private:
		std::string script_source;
		TScriptActiveType script_type;
	public:
		TScript()
		{
			script_type = TScriptActiveType::DEFAULT;
		}
		TScript(std::string script_source)
		{
			script_type = TScriptActiveType::DEFAULT;
			this->script_source = script_source;
		}
		TScript(std::string script_source, TScriptActiveType script_type)
		{
			this->script_type = script_type;
			this->script_source = script_source;
		}
		TScriptActiveType GetScriptType()
		{
			return script_type;
		}
		void SetScriptType(TScriptActiveType type)
		{
			this->script_type = type;
		}
		std::string GetScriptSource()
		{
			return script_source;
		}
		void SetScriptSource(const char* source)
		{
			script_source = source;
		}
		void SaveToXML(pugi::xml_node& parent_node, const int version);
		void LoadFromXML(const pugi::xml_node& document_node, const int version);
	};

	class TScriptInstance
	{
	private:
		TScript* source;
		TSMethod* compiled_script;
	public:
		TScript* GetSource()
		{
			return source;
		}
		TScriptInstance()
		{
			source = nullptr;
			compiled_script = nullptr;
		}
		TScriptInstance(TScript* source, TSMethod* compiled_script)
		{
			this->source = source;
			this->compiled_script = compiled_script;
		}
		TSMethod* GetCompiledScript()
		{
			assert(compiled_script != nullptr);
			return compiled_script;
		}
	};
}