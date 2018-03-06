#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			class TRuntimeProperty
			{
			public:
				virtual const char* GetTypeString()const = 0;
				virtual RuntimePropertyType GetType() = 0;
				virtual void Save(pugi::xml_node& property_node, const int version)const=0;
				virtual void Load(const pugi::xml_node& property_node, const int version)=0;
				virtual ~TRuntimeProperty() {};
				virtual TRuntimeProperty* Clone() = 0;
			};

			typedef TRuntimeProperty*(*PropertyClone)();
			class RuntimePropertiesFactory
			{
			public:
				static bool Register(const char* name, PropertyClone clone);
				static void UnregisterAll();
				static TRuntimeProperty* Create(const char* name);
			};

			template<class T>
			class TRuntimePropertyValue : public TRuntimeProperty
			{
			protected:
				T value;
				typedef T ValueType;
			public:
				TRuntimePropertyValue()
				{

				}
				TRuntimePropertyValue(const T& value)
				{
					this->value = value;
				}
				T GetValue()
				{
					return value;
				}
				void SetValue(const T& value)
				{
					this->value = value;
				}
			};

			class TRuntimeProperties : public IRuntimeProperties
			{
			public:

				std::map<std::string, std::unique_ptr<TRuntimeProperty>> properties;

				template<class T>
				void Get(const std::string& name, T& value)
				{
					auto it = properties.find(name);
					if (it == properties.end())
					{
						throw std::invalid_argument("Неправильное имя свойства");
					}
					auto ptr = dynamic_cast<TRuntimePropertyValue<T>*>(it->second.get());
					if (ptr == nullptr)
						throw std::invalid_argument("Неправильный тип свойства");
					value = ptr->GetValue();
				}

				template<class PropT>
				void Set(const std::string& name, typename PropT::ValueTypeAlias value)
				{
					auto it = properties.find(name);
					if (it != properties.end())
					{
						auto prop = dynamic_cast<PropT*>(it->second.get());
						if(prop==nullptr)
							throw std::invalid_argument("Неправильный тип свойства");
						else
							prop->SetValue(value);
					}
					else
						properties[name].reset(new PropT(value));
				}
			public:
				TRuntimeProperties();
				~TRuntimeProperties();
				TRuntimeProperties(const TRuntimeProperties& copy_from);
				void AddProperty(const char* name, TRuntimeProperty* prop);
				bool HasProperty(const std::string& name, RuntimePropertyType& type);

				void SetBool(const std::string& name, const bool& value);
				bool GetBool(const std::string& name);

				void SetInt(const std::string& name, const int& value);
				int GetInt(const std::string& name);

				void SetFloat(const std::string& name, const float& value);
				float GetFloat(const std::string& name);

				void SetString(const std::string& name, const std::string& value);
				std::string GetString(const std::string& name);

				void SetVec2(const std::string& name, const BaluLib::TVec2& value);
				BaluLib::TVec2 GetVec2(const std::string& name);

				void SetVec3(const std::string& name, const BaluLib::TVec3& value);
				BaluLib::TVec3 GetVec3(const std::string& name);

				void SetVec4(const std::string& name, const BaluLib::TVec4& value);
				BaluLib::TVec4 GetVec4(const std::string& name);

				void SetTransformWithScale(const std::string& name, const TTransformWithScale& value);
				TTransformWithScale GetTransformWithScale(const std::string& name);

				void SetTransform(const std::string& name, const TTransform& value);
				TTransform GetTransform(const std::string& name);

				void SetRotation(const std::string& name, const TRot& value);
				TRot GetRotation(const std::string& name);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
		}
	}
}