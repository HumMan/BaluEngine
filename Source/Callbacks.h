
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

	class TCallback
	{
	protected:
		std::string script_source;
		bool is_script;
		void* user_data;
		int callback_type;
	public:
		TCallback()
		{
			is_script = false;
			user_data = nullptr;
			callback_type = TCallbacksActiveType::DEFAULT;
			
		}
		void* GetUserData()
		{
			return user_data;
		}	
		bool IsScript()
		{
			return is_script;
		}
		int GetCallbackType()
		{
			return callback_type;
		}
		std::string GetScriptSource()
		{
			assert(is_script);
			return script_source;
		}
		void SetScriptSource(const char* source)
		{
			script_source = source;
		}
		void SaveToXML(pugi::xml_node& parent_node, const int version);
		void LoadFromXML(const pugi::xml_node& document_node, const int version);
	};

	class TCallbackInstance
	{
	protected:
		TCallback* source;

		TSMethod* compiled_script;
		TBaluScriptInstance* script_engine;
		TCallbacksActiveType* active_type;
	public:
		TCallbackInstance()
		{
			source = nullptr;
			compiled_script = nullptr;
			script_engine = nullptr;
			active_type = nullptr;
		}
		void SetCompiledScript(TSMethod* method, TBaluScriptInstance* script_engine)
		{
			//TODO compiled_script не очищается после смены сцены редактора
			//assert(compiled_script == nullptr);
			this->compiled_script = method;
			this->script_engine = script_engine;
		}
		TBaluScriptInstance* GetScriptEngine()
		{
			assert(script_engine != nullptr);
			return script_engine;
		}
		TSMethod* GetCompiledScript()
		{
			assert(compiled_script != nullptr);
			return compiled_script;
		}
	};

	template<class T>
	class TSpecialCallback: public TCallback
	{
	private:
		T callback;
	public:
		T GetCallback()
		{
			return callback;
		}
		void Initialize(T callback, TCallbacksActiveType* active_type, void* user_data, int callback_type, char* script_source = nullptr)
		{
			this->callback = callback;
			this->user_data = user_data;
			this->callback_type = callback_type;
			this->is_script = script_source != nullptr;
			if (is_script)
				this->script_source = script_source;
		}
		TSpecialCallback()
		{
			callback = nullptr;
		}
		TSpecialCallback(char* script_source, TCallbacksActiveType* active_type, int callback_type = TCallbacksActiveType::DEFAULT)
		{
			Initialize(nullptr, active_type, nullptr, callback_type, script_source);
		}
		TSpecialCallback(T callback, TCallbacksActiveType* active_type, void* user_data, int callback_type = TCallbacksActiveType::DEFAULT)
		{
			Initialize(callback, active_type, user_data, callback_type);
		}
		TSpecialCallback(T callback, TCallbacksActiveType* active_type)
		{
			Initialize(callback, active_type, nullptr, TCallbacksActiveType::DEFAULT);
		}
	};

	template<class T>
	class TSpecialCallbackInstance : public TCallbackInstance
	{
	private:
		TSpecialCallback<T>* source;
	public:
		template<typename... Args>
		void Execute(Args... args)
		{
			if ((active_type != nullptr && active_type->active_type == source->GetCallbackType()) || (active_type == nullptr && source->GetCallbackType() == TCallbacksActiveType::DEFAULT))
			{
				if (source->IsScript())
					GetScriptEngine()->CallMethod(*this, args...);
				else if (source->GetCallback() != nullptr)
					source->GetCallback() (this, args...);
			}
		}
	};
}