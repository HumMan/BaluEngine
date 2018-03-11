#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
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
				static std::vector <TExternalClassInfo>& get_external_class_registry();
				static std::vector <TEnumInfo>& get_enum_registry();
			};
		}
	}
}