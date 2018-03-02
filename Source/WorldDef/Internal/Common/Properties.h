#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			template<int T>
			class PropertyToTypeMap {};

#define BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(prop, result)\
			template<>\
			class PropertyToTypeMap<(int)prop>\
			{\
			public:\
				typedef result Result;\
			};

			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Bool, bool)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Int, int)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Number, unsigned int)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Float, float)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::String, std::string)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Color, BaluLib::TVec3)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::ColorWithAlpha, BaluLib::TVec4)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::TransparentMode, TTransparentMode)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::AlphaTestFunc, TAlphaTestFunc)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::BlendFunc, TBlendFunc)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::BlendEquation, TBlendEquation)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::TexFilter, TTexFilter)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::TexClamp, TTexClamp)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Size, BaluLib::TVec2)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::TransformWithScale, TTransformWithScale)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Transform, TTransform)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Scale, BaluLib::TVec2)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Pos, BaluLib::TVec2)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::Rotation, TRot)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::PhysBodyType, TPhysBodyType)
			//BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::PhysShapeType, TTransparentMode)
			BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP(PropertyType::ImagePath, std::string)

#undef BALU_ENGINE_REGISTER_PROPERTY_TO_TYPE_MAP

#define BALU_ENGINE_REGISTER_PROPERTY(property_name, property_type, default_value)\
private:\
	PropertyToTypeMap<(int)property_type>::Result property_name##Value; \
	void InitProperty_##property_name()\
	{\
		property_name##Value = default_value;\
		AddProperty(#property_name, property_type, &property_name##Value);\
	}\
public:\
	void Set##property_name(PropertyToTypeMap<(int)property_type>::Result value){\
		PropertyType temp_property_type;\
		assert(HasProperty(#property_name, temp_property_type));\
		assert(property_type == temp_property_type);\
		GetProperty(#property_name)->Set(&value);}\
	PropertyToTypeMap<(int)property_type>::Result Get##property_name()const {\
		PropertyType temp_property_type;\
		assert(HasProperty(#property_name, temp_property_type));\
		assert(property_type == temp_property_type);\
		return property_name##Value;}


			class TProperty :public IProperty
			{
			private:
				PropertyType type;
				void* value;
			public:
				TProperty(PropertyType type, void* value)
				{
					this->type = type;
					this->value = value;
				}
				PropertyType GetType()const
				{
					return type;
				}
				void Set(const void const* new_value)
				{

				}
				void SetAsBool(bool value)
				{
					//TODO - listener update
					*(bool*)(this->value) = value;
				}
				bool GetAsBool()const
				{
					return *(bool*)value;
				}

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& parent_node, const int version, IWorld* world);
			};

			class TProperties : public virtual IProperties
			{
			private:
				std::map<std::string, std::unique_ptr<TProperty>> properties;
			public:
				TProperties();
				void AddProperty(const std::string& name, PropertyType type, void* value)
				{
					properties[name].reset(new TProperty(type, value));
				}

				bool HasProperty(const std::string& name, PropertyType& type)const;
				IProperty* GetProperty(const std::string& name)const;
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
				~TProperties();
			};
		}
	}
}
