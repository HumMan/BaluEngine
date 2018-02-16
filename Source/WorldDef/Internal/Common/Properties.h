#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TProperty
			{
			public:
				virtual const char* GetTypeString() = 0;
				virtual PropertyType GetType() = 0;
				void Save(pugi::xml_node& parent_node, const int version)const;
				virtual void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
				virtual ~TProperty();
			};

			typedef TProperty*(*PropertyClone)();
			class PropertiesFactory
			{
			public:
				static bool Register(const char* name, PropertyClone clone);
				static void UnregisterAll();
				static TProperty* Create(const char* name);
			};

			template<class T>
			class TPropertyValue : public TProperty
			{
			protected:
				T value;
			public:
				TPropertyValue()
				{

				}
				TPropertyValue(const T& value)
				{
					this->value = value;
				}
				T* GetValue()
				{
					return &value;
				}
				void SetValue(const T& value)
				{
					this->value = value;
				}
			};

			class TProperties : public IProperties
			{
			public:

				std::map<std::string, std::unique_ptr<TProperty>> properties;

				template<class T>
				void Get(const std::string& name, T*& value)
				{
					auto it = properties.find(name);
					if (it == properties.end())
					{
						throw std::invalid_argument("Неправильное имя свойства");
					}
					auto ptr = dynamic_cast<TPropertyValue<T>*>(it->second.get());
					if (ptr == nullptr)
						throw std::invalid_argument("Неправильный тип свойства");
					value = ptr->GetValue();
				}
				bool is_wrapper;
			public:
				TProperties();
				TProperties(bool is_wrapper);
				void AddProperty(const char* name, TProperty* prop);
				bool HasProperty(const std::string& name, PropertyType& type);
				void SetBool(const std::string& name, bool value);
				bool GetBool(const std::string& name);
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
		}
	}
}
