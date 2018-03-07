#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			//
			//class TClassBinding
			//{
			//public:
			//	const char* class_name;
			//	int size;
			//	std::vector<std::unique_ptr<Unpacker>> methods;
			//	TSClass* compiled;
			//	TClassBinding()
			//	{
			//		class_name = nullptr;
			//		size = 0;
			//		compiled = nullptr;
			//	}
			//
			//	void SetMethods(std::vector<Unpacker*> methods)
			//	{
			//		for (auto v : methods)
			//			this->methods.push_back(std::unique_ptr<Unpacker>(v));
			//	}
			//};

			//class TClassRegistryParams
			//{
			//public:
			//	TSyntaxAnalyzer* syntax;
			//	std::vector<TStaticValue> *static_objects;
			//	//std::vector < std::unique_ptr<TSMethod>> *smethods;
			//};

			//typedef void(*RegisterScriptClass)(const char* source);
			//
			//TSClass* RegisterEnum(TClassRegistryParams& params, const char* source);
			//
			//Unpacker* SetName(const char* name, Unpacker* method);
			//Unpacker* SetAsConstructor(Unpacker* method);

			class TExternalClassInfo
			{
			public:
				const char* source;
				const char* name;
				size_t size;
				bool is_interface;
				const char* c_name;
				TExternalClassInfo(const char* source, const char* name, size_t size, bool is_interface, const char* c_name)
				{
					this->source = source;
					this->name = name;
					this->size = size;
					this->is_interface = is_interface;
					this->c_name = c_name;
				}
			};

			class TEnumInfo
			{
			public:
				const char* source;
				const char* name;
				const char* c_name;
				TEnumInfo(const char* source, const char* name, const char* c_name)
				{
					this->source = source;
					this->name = name;
					this->c_name = c_name;
				}
			};

			class TScriptClassesRegistry
			{
			public:
				static void RegisterExternal(const char* source, const char* name, size_t size, bool is_interface, const char* c_name);
				static void RegisterEnum(const char* source, const char* name, const char* c_name);
				//static bool RegisterEnum(const char* name, RegisterScriptClass reg);
				//static void RegisterClassBinding(TClassBinding* binding);
				//static void RegisterClassesInScript(TClassRegistryParams& params);
				static std::vector <TExternalClassInfo>& get_external_class_registry();
				static std::vector <TEnumInfo>& get_enum_registry();
			};
		}
	}
}