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
				bool is_shared;
				const char* c_name;
				TExternalClassInfo(const char* source, const char* name, size_t size, bool is_interface, bool is_shared, const char* c_name)
				{
					this->source = source;
					this->name = name;
					this->size = size;
					this->is_interface = is_interface;
					this->is_shared = is_shared;
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
				static void RegisterExternal(const char* source, const char* name, size_t size, bool is_interface, bool is_shared, const char* c_name);
				static void RegisterEnum(const char* source, const char* name, const char* c_name);
				static std::vector <TExternalClassInfo>& get_external_class_registry();
				static std::vector <TEnumInfo>& get_enum_registry();
			};

			template<class T>
			class TScriptSharedPointer
			{
			public:
				std::shared_ptr<T>* v;
				int* refs_count;

				void Init()
				{
					v = nullptr;
					refs_count = nullptr;
				}

				TScriptSharedPointer(const std::shared_ptr<T>& source)
				{
					Init();
					refs_count = new int(1);
					v = new std::shared_ptr<T>(source);
				}

				void def_constr()
				{
					Init();
				}

				void destructor()
				{
					if (v == nullptr)
						return;
					(*refs_count)--;
					if (*refs_count == 0)
					{
						delete v;
						delete refs_count;
					}

					refs_count = nullptr;
					v = nullptr;
				}

				void copy_constr(TScriptSharedPointer* copy_from)
				{
					v = copy_from->v;
					refs_count = copy_from->refs_count;
					if(v!=nullptr)
						(*refs_count)++;
				}

				void operator_Assign( TScriptSharedPointer* right)
				{
					if (v == right->v)
						return;
					destructor();

					v = right->v;
					refs_count = right->refs_count;
					if (v != nullptr)
						(*refs_count)++;
				}
				T* operator->()
				{
					return v->get();
				}
			};
		}
	}
}