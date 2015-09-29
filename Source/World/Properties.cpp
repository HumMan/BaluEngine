#include "IProperties.h"

using namespace EngineInterface;

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
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
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
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
	{
		TProperty::Load(instance_node, version, world);
	}
};
static bool TStringProperty_registered = PropertiesFactory::Register("string", TStringProperty::Clone);

class TProperty
{
public:
	virtual const char* GetTypeString() = 0;
	virtual EngineInterface::PropertyType GetType() = 0;
	void Save(pugi::xml_node& parent_node, const int version)
	{
		parent_node.append_attribute("type").set_value(GetTypeString());
	}
	virtual void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
	{}
	virtual ~TProperty()
	{
	}
};