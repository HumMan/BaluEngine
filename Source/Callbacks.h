
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

	enum class TCallbacksActiveType
	{
		DEFAULT = 0,
		EDITOR = 1
	};

	class TCallback
	{
	private:
		std::string script_source;
		TCallbacksActiveType callback_type;
	public:
		TCallback()
		{
			callback_type = TCallbacksActiveType::DEFAULT;	
		}
		TCallbacksActiveType GetCallbackType()
		{
			return callback_type;
		}
		void SetCallbackType(TCallbacksActiveType type)
		{
			this->callback_type = type;
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

	class TCallbackInstance
	{
	private:
		TCallback* source;
		TSMethod* compiled_script;
	public:
		TCallbackInstance(TCallback* source, TSMethod* compiled_script)
		{
			source = nullptr;
			compiled_script = nullptr;
		}
		TSMethod* GetCompiledScript()
		{
			assert(compiled_script != nullptr);
			return compiled_script;
		}
	};

	//template<class T>
	//class TSpecialCallback: public TCallback
	//{
	//private:
	//	T callback;
	//public:
	//	T GetCallback()
	//	{
	//		return callback;
	//	}
	//	void Initialize(T callback, TCallbacksActiveType* active_type, int callback_type, char* script_source)
	//	{
	//		this->callback = callback;
	//		this->callback_type = callback_type;
	//		this->script_source = script_source;
	//	}
	//	TSpecialCallback()
	//	{
	//		callback = nullptr;
	//	}
	//	TSpecialCallback(char* script_source, TCallbacksActiveType* active_type, int callback_type = TCallbacksActiveType::DEFAULT)
	//	{
	//		Initialize(nullptr, active_type, nullptr, callback_type, script_source);
	//	}
	//};

	//template<class T>
	//class TSpecialCallbackInstance : public TCallbackInstance
	//{
	//private:
	//	TSpecialCallback<T>* source;
	//public:
	//	template<typename... Args>
	//	void Execute(Args... args)
	//	{
	//		if ((active_type != nullptr && active_type->active_type == source->GetCallbackType()) || (active_type == nullptr && source->GetCallbackType() == TCallbacksActiveType::DEFAULT))
	//		{
	//			GetScriptEngine()->CallMethod(*this, args...);
	//		}
	//	}
	//};
}