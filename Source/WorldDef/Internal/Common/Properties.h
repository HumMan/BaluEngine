#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{


#define BALU_ENGINE_REGISTER_PROPERTY(property_name, property_type, default_value)\
protected:\
	PropertyToTypeMap<(int)property_type>::Result property_name##Value; \
	void InitProperty_##property_name()\
	{\
		property_name##Value = default_value;\
		AddProperty(#property_name, property_type, &property_name##Value);\
	}\
public:\
	void Set##property_name(const PropertyToTypeMap<(int)property_type>::Result& value){\
		PropertyType temp_property_type;\
		assert(HasProperty(#property_name, temp_property_type));\
		((TProperty*)GetProperty(#property_name))->Set<(int)property_type>(value);}\
	PropertyToTypeMap<(int)property_type>::Result Get##property_name()const {\
		PropertyType temp_property_type;\
		assert(HasProperty(#property_name, temp_property_type));\
		assert(property_type == temp_property_type);\
		return property_name##Value;}


			class IPropertyChangeWatcher
			{
			public:
				virtual void PropertyChanged(const std::string& name, const std::string& old_value, const std::string& new_value)=0;
			};

			class TProperty :public IProperty
			{
			private:
				PropertyType type;
				void* value;
				std::string name;
				IPropertyChangeWatcher* watcher;
			public:
				TProperty(PropertyType type, const std::string& name, void* value, IPropertyChangeWatcher* watcher=nullptr)
				{
					this->type = type;
					this->name = name;
					this->value = value;
					this->watcher = watcher;
				}
				PropertyType GetType()const
				{
					return type;
				}

#define BALU_ENGINE_PROPERTY_SETGET(property_type)\
				void SetAs##property_type(const PropertyToTypeMap<(int)PropertyType::##property_type>::Result& value)\
				{\
					Set<(int)PropertyType::##property_type>(value);\
				}\
				PropertyToTypeMap<(int)PropertyType::##property_type>::Result GetAs##property_type()const\
				{\
					return *(PropertyToTypeMap<(int)PropertyType::##property_type>::Result*)value;\
				}

					BALU_ENGINE_PROPERTY_SETGET(Bool)
					BALU_ENGINE_PROPERTY_SETGET(Int)
					BALU_ENGINE_PROPERTY_SETGET(Number)
					BALU_ENGINE_PROPERTY_SETGET(Float)
					BALU_ENGINE_PROPERTY_SETGET(String)
					BALU_ENGINE_PROPERTY_SETGET(Color)
					BALU_ENGINE_PROPERTY_SETGET(ColorWithAlpha)
					BALU_ENGINE_PROPERTY_SETGET(TransparentMode)
					BALU_ENGINE_PROPERTY_SETGET(AlphaTestFunc)
					BALU_ENGINE_PROPERTY_SETGET(BlendFunc)
					BALU_ENGINE_PROPERTY_SETGET(BlendEquation)
					BALU_ENGINE_PROPERTY_SETGET(TexFilter)
					BALU_ENGINE_PROPERTY_SETGET(TexClamp)
					BALU_ENGINE_PROPERTY_SETGET(Size)
					BALU_ENGINE_PROPERTY_SETGET(TransformWithScale)
					BALU_ENGINE_PROPERTY_SETGET(Transform)
					BALU_ENGINE_PROPERTY_SETGET(Scale)
					BALU_ENGINE_PROPERTY_SETGET(Pos)
					BALU_ENGINE_PROPERTY_SETGET(Rotation)
					BALU_ENGINE_PROPERTY_SETGET(PhysBodyType)
					BALU_ENGINE_PROPERTY_SETGET(ImagePath)

#undef BALU_ENGINE_PROPERTY_SETGET

				template<int property_type, class T>
				void Set(const T& new_value)
				{
					assert(property_type == (int)type);
					auto& curr_value = *(PropertyToTypeMap<property_type>::Result*)value;
					//TODO if (curr_value != new_value)
					{
						std::string old_value;
						if (watcher != nullptr)
						{
							old_value = SerializeValue();
						}
						curr_value = new_value;
						if (watcher != nullptr)
						{
							watcher->PropertyChanged(name, old_value, SerializeValue());
						}
					}
				}
				std::string SerializeValue()const;
				void DeserializeValue(const std::string& value);
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& parent_node, const int version);
			};

			class TProperties : public virtual IProperties
			{
			private:
				std::map<std::string, std::unique_ptr<TProperty>> properties;
				IPropertyChangeWatcher* watcher;
			public:
				TProperties(IPropertyChangeWatcher* watcher = nullptr);
				void AddProperty(const std::string& name, PropertyType type, void* value)
				{
					properties[name].reset(new TProperty(type, name, value, watcher));
				}
				std::vector<std::string> GetPropertyNames();
				bool HasProperty(const std::string& name, PropertyType& type)const;
				IProperty* GetProperty(const std::string& name)const;
				void SaveProperties(pugi::xml_node& parent_node, const int version)const;
				void LoadProperties(const pugi::xml_node& instance_node, const int version);				
				~TProperties();
			};
		}
	}
}
