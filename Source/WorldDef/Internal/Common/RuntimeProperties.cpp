#include "RuntimeProperties.h"


#include <assert.h>

#include <pugixml.hpp>

#include "SerializeCommon.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

using namespace pugi;

typedef std::vector < std::pair<const char*, PropertyClone>> properties_registry_type;
properties_registry_type *properties_registry;

TRuntimeProperties::~TRuntimeProperties()
{
}

TRuntimeProperties::TRuntimeProperties()
{
}

TRuntimeProperties::TRuntimeProperties(const TRuntimeProperties& copy_from)
{

}

void TRuntimeProperties::AddProperty(const char* name, TRuntimeProperty* prop)
{
	RuntimePropertyType type;
	assert(!HasProperty(std::string(name), type));
	properties[name].reset(prop);
}

bool TRuntimeProperties::HasProperty(const std::string& name, RuntimePropertyType& type)
{
	auto it = properties.find(name);
	if (it != properties.end())
	{
		type = it->second->GetType();
		return true;
	}
	else
		return false;
}

template<class T>
void SaveValue(pugi::xml_node& property_node, const T& value)
{
	property_node.append_attribute("value").set_value(value);
}

void SaveValue(pugi::xml_node& property_node, const std::string& value)
{
	property_node.append_attribute("value").set_value(value.c_str());
}

template<int Size>
void SaveValue(pugi::xml_node& property_node, const BaluLib::TVec<float, Size>& value)
{
	for(int i=0;i<Size;i++)
		property_node.append_child(std::to_string(i).c_str()).append_attribute("value").set_value(value[i]);
}

void SaveValue(pugi::xml_node& property_node, const TRot& value)
{
	SerializeCommon::SaveRotation(property_node, "rotation", value);
}

void SaveValue(pugi::xml_node& property_node, const TTransform& value)
{
	SerializeCommon::SaveTransform(property_node, "transform", value);
}

void SaveValue(pugi::xml_node& property_node, const TTransformWithScale& value)
{
	SerializeCommon::SaveTransformWithScale(property_node, "transformWithScale", value);
}

void LoadValue(const pugi::xml_node& property_node, bool& value)
{
	value = property_node.attribute("value").as_bool();
}

void LoadValue(const pugi::xml_node& property_node, int& value)
{
	value = property_node.attribute("value").as_int();
}

void LoadValue(const pugi::xml_node& property_node, float& value)
{
	value = property_node.attribute("value").as_float();
}

void LoadValue(const pugi::xml_node& property_node, std::string& value)
{
	value = property_node.attribute("value").as_string();
}

template<int Size>
void LoadValue(const pugi::xml_node& property_node, BaluLib::TVec<float, Size>& value)
{
	for (int i = 0; i<Size; i++)
		value[i] = property_node.child(std::to_string(i).c_str()).attribute("value").as_float();
}

void LoadValue(const pugi::xml_node& property_node, TRot& value)
{
	value = SerializeCommon::LoadRotation(property_node.child("rotation"));
}

void LoadValue(const pugi::xml_node& property_node,  TTransform& value)
{
	value = SerializeCommon::LoadTransform(property_node.child("transform"));
}

void LoadValue(const pugi::xml_node& property_node, TTransformWithScale& value)
{
	value = SerializeCommon::LoadTransformWithScale(property_node.child("transformWithScale"));
}

#define RUNTIME_PROPERTY_SETGET(TypeName, PropType, ValueType)\
class T##TypeName##Property : public TRuntimePropertyValue<ValueType>\
{\
public:\
	typedef ValueType ValueTypeAlias;\
	T##TypeName##Property() {}\
	T##TypeName##Property(const ValueType& value) : TRuntimePropertyValue<ValueType>(value)\
	{\
	}\
	static TRuntimeProperty* NewInstance()\
	{\
		return new T##TypeName##Property();\
	}\
	TRuntimeProperty* Clone()\
	{\
		return new T##TypeName##Property(GetValue());\
	}\
	const char* GetTypeString()const\
	{\
		return #TypeName;\
	}\
	RuntimePropertyType GetType()\
	{\
		return RuntimePropertyType::TypeName;\
	}\
	void Save(pugi::xml_node& property_node, const int version)const\
	{\
		SaveValue(property_node, value);\
	}\
	void Load(const pugi::xml_node& property_node, const int version)\
	{\
		LoadValue(property_node, value);\
	}\
};\
static bool T##TypeName##Property_registered = RuntimePropertiesFactory::Register(#TypeName, T##TypeName##Property::NewInstance);\
\
void TRuntimeProperties::Set##TypeName(const std::string& name, const ValueType& value)\
{\
	Set<PropType>(name, value);\
}\
ValueType TRuntimeProperties::Get##TypeName(const std::string& name)\
{\
	ValueType value;\
	Get(name, value);\
	return value;\
}

RUNTIME_PROPERTY_SETGET(Bool, TBoolProperty, bool)
RUNTIME_PROPERTY_SETGET(Int, TIntProperty, int)
RUNTIME_PROPERTY_SETGET(Float, TFloatProperty, float)
RUNTIME_PROPERTY_SETGET(String, TStringProperty, std::string)
RUNTIME_PROPERTY_SETGET(Vec2, TVec2Property, BaluLib::TVec2)
RUNTIME_PROPERTY_SETGET(Vec3, TVec3Property, BaluLib::TVec3)
RUNTIME_PROPERTY_SETGET(Vec4, TVec4Property, BaluLib::TVec4)
RUNTIME_PROPERTY_SETGET(TransformWithScale, TTransformWithScaleProperty, TTransformWithScale)
RUNTIME_PROPERTY_SETGET(Transform, TTransformProperty, TTransform)
RUNTIME_PROPERTY_SETGET(Rotation, TRotationProperty, TRot)

void TRuntimeProperties::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node props_node = parent_node.append_child("Properties");
	for (auto& v : properties)
	{
		auto prop_node = props_node.append_child("Property");
		v.second->Save(props_node, version);
		prop_node.append_attribute("name").set_value(v.first.c_str());
		prop_node.append_attribute("type").set_value(v.second->GetTypeString());
	}
}

void TRuntimeProperties::Load(const pugi::xml_node& instance_node, const int version, IWorld* world)
{
	xml_node props_node = instance_node.child("Properties");
	for (pugi::xml_node prop_node = props_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		auto new_prop = RuntimePropertiesFactory::Create(prop_node.attribute("type").as_string());
		new_prop->Load(prop_node, version);
		auto name = prop_node.attribute("name").as_string();
		properties[name].reset(new_prop);
	}
}

bool RuntimePropertiesFactory::Register(const char* name, PropertyClone clone)
{
	if (properties_registry == nullptr)
		properties_registry = new properties_registry_type();
	properties_registry->push_back(std::pair<const char*, PropertyClone>(name, clone));
	return true;
}

void RuntimePropertiesFactory::UnregisterAll()
{
	delete properties_registry;
}

TRuntimeProperty* RuntimePropertiesFactory::Create(const char* name)
{
	for (int i = 0; i < properties_registry->size(); i++)
		if (strcmp((*properties_registry)[i].first, name) == 0)
			return (*properties_registry)[i].second();
	throw std::invalid_argument("Тип не зарегистрирован");
}