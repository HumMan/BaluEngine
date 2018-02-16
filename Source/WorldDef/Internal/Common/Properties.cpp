#include "IProperties.h"

#include <assert.h>

#include <pugixml.hpp>

using namespace EngineInterface;

class TBoolProperty : public TPropertyValue<bool>
{

public:
	TBoolProperty()
	{
	}
	TBoolProperty(const bool& value) : TPropertyValue<bool>(value)
	{
	}
	static TProperty* Clone()
	{
		return new TBoolProperty();
	}
	const char* GetTypeString()
	{
		return "bool";
	}
	EngineInterface::PropertyType GetType()
	{
		return EngineInterface::PropertyType::Bool;
	}
	void Save(pugi::xml_node& parent_node, const int version)
	{
		TProperty::Save(parent_node, version);
		parent_node.append_attribute("value").set_value(value);
	}
	void Load(const pugi::xml_node& instance_node, const int version, TWorld* world)
	{
		value = instance_node.attribute("value").as_bool();
	}
};
static bool TBoolProperty_registered = PropertiesFactory::Register("bool", TBoolProperty::Clone);

class TStringProperty : public TPropertyValue<std::string>
{

public:
	TStringProperty()
	{
	}
	TStringProperty(const std::string& value) : TPropertyValue<std::string>(value)
	{
	}
	static TProperty* Clone()
	{
		return new TStringProperty();
	}
	const char* GetTypeString()
	{
		return "string";
	}
	EngineInterface::PropertyType GetType()
	{
		return EngineInterface::PropertyType::String;
	}
	void Save(pugi::xml_node& parent_node, const int version)
	{
		TProperty::Save(parent_node, version);
		parent_node.append_attribute("value").set_value(value.c_str());
	}
	void Load(const pugi::xml_node& instance_node, const int version, TWorld* world)
	{
		TProperty::Load(instance_node, version, world);
	}
};
static bool TStringProperty_registered = PropertiesFactory::Register("string", TStringProperty::Clone);


void TProperty::Save(pugi::xml_node& parent_node, const int version)
{
	parent_node.append_attribute("type").set_value(GetTypeString());
}
void TProperty::Load(const pugi::xml_node& instance_node, const int version, TWorld* world)
{}
TProperty::~TProperty()
{
}

TProperties::TProperties()
{
	is_wrapper = false;
}
TProperties::TProperties(bool is_wrapper)
{
	this->is_wrapper = is_wrapper;
}
void TProperties::AddProperty(const char* name, TProperty* prop)
{
	EngineInterface::PropertyType type;
	assert(!HasProperty(std::string(name), type));
	properties[name].reset(prop);
}
bool TProperties::HasProperty(const std::string& name, EngineInterface::PropertyType& type)
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
void TProperties::SetBool(const std::string& name, bool value)
{
	if (is_wrapper)
		dynamic_cast<TBoolProperty*>(properties[name].get())->SetValue(value);
	else
		properties[name].reset(new TBoolProperty(value));
}
bool TProperties::GetBool(const std::string& name)
{
	bool* value = nullptr;
	Get(name, value);
	return *value;
}
