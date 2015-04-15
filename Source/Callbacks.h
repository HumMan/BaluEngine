
#pragma once

#include <string>
#include <assert.h>

class TSMethod;
class TBaluScriptInstance;
class NVGcontext;

namespace pugi
{
	class xml_node;
}

namespace EngineInterface
{

	class TCallbacksActiveType
	{
	public:
		enum
		{
			DEFAULT = 0,
			EDITOR = 1
		};
		int active_type;
	};

	class TCallbackData
	{
	protected:
		void* user_data;
		int callback_type;
		TCallbacksActiveType* active_type;
	public:
		TCallbackData()
		{
			user_data = nullptr;
			callback_type = TCallbacksActiveType::DEFAULT;
			active_type = nullptr;
		}
		void* GetUserData()
		{
			return user_data;
		}
	};



	class TScriptData : public TCallbackData
	{
	protected:
		std::string script_source;
		TSMethod* compiled_script;
		TBaluScriptInstance* script_engine;
		bool is_script;
	public:
		TScriptData()
		{
			compiled_script = nullptr;
			script_engine = nullptr;
			is_script = false;
		}
		void SetCompiledScript(TSMethod* method, TBaluScriptInstance* script_engine)
		{
			assert(compiled_script == nullptr);
			this->compiled_script = method;
			this->script_engine = script_engine;
		}
		TSMethod* GetCompiledScript()
		{
			assert(compiled_script != nullptr);
			return compiled_script;
		}
		TBaluScriptInstance* GetScriptEngine()
		{
			assert(script_engine != nullptr);
			return script_engine;
		}
		bool IsScript()
		{
			return is_script;
		}
		std::string GetScriptSource()
		{
			assert(is_script);
			return script_source;
		}

		void SaveToXML(pugi::xml_node& parent_node, const int version);
		void LoadFromXML(const pugi::xml_node& document_node, const int version);
	};

	template<class T>
	class CallbackWithData : public TScriptData
	{
	private:
		T callback;
	public:
		bool operator==(const CallbackWithData& right)
		{
			return callback = right.callback;
		}
		template<typename... Args>
		void Execute(Args... args)
		{
			if (active_type->active_type == callback_type)
			{
				if (IsScript())
					GetScriptEngine()->CallMethod(*this, args...);
				else
					callback(this, args...);
			}
		}
		void Initialize(T callback, TCallbacksActiveType* active_type, void* user_data, int callback_type, char* script_source = nullptr)
		{
			this->callback = callback;
			this->user_data = user_data;
			this->callback_type = callback_type;
			this->active_type = active_type;
			this->is_script = script_source != nullptr;
			if (is_script)
				this->script_source = script_source;
			compiled_script = nullptr;
		}
		CallbackWithData()
		{
			callback = nullptr;
		}
		CallbackWithData(char* script_source, TCallbacksActiveType* active_type, int callback_type = TCallbacksActiveType::DEFAULT)
		{
			Initialize(nullptr, active_type, nullptr, callback_type, script_source);
		}
		CallbackWithData(T callback, TCallbacksActiveType* active_type, void* user_data, int callback_type = TCallbacksActiveType::DEFAULT)
		{
			Initialize(callback, active_type, user_data, callback_type);
		}
		CallbackWithData(T callback, TCallbacksActiveType* active_type)
		{
			Initialize(callback, active_type, nullptr, TCallbacksActiveType::DEFAULT);
		}
	};
}