#pragma once

#include "EngineInterfaces\IProperties.h"

#include <pugixml.hpp>

using namespace pugi;

class TProperty
{
public:
	virtual const char* GetTypeString() = 0;
	virtual EngineInterface::PropertyType GetType() = 0;
	void Save(pugi::xml_node& parent_node, const int version)
	{
		parent_node.append_attribute("type").set_value(GetTypeString());
	}
	virtual void Load(const pugi::xml_node& instance_node, const int version)
	{}
	virtual ~TProperty()
	{
	}
};

typedef TProperty*(*PropertyClone)();
class PropertiesFactory
{
public:
	static bool Register(const char* name, PropertyClone clone);
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
	void Load(const pugi::xml_node& instance_node, const int version)
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
	void Load(const pugi::xml_node& instance_node, const int version)
	{
		TProperty::Load(instance_node, version);
	}
};
static bool TStringProperty_registered = PropertiesFactory::Register("string", TStringProperty::Clone);
//
//class TSceneClassInstanceProperty : public TPropertyValue<EngineInterface::IBaluSceneClassInstance*>
//{
//public:
//	TSceneClassInstanceProperty()
//	{
//	}
//	TSceneClassInstanceProperty(EngineInterface::IBaluSceneClassInstance* value) : TPropertyValue<EngineInterface::IBaluSceneClassInstance*>(value)
//	{
//	}
//	static TProperty* Clone()
//	{
//		return new TSceneClassInstanceProperty();
//	}
//	const char* GetTypeString()
//	{
//		return "sceneClassInstance";
//	}
//	EngineInterface::PropertyType GetType()
//	{
//		return EngineInterface::PropertyType::SceneClassInstance;
//	}
//	void Save(pugi::xml_node& parent_node, const int version)
//	{
//		TProperty::Save(parent_node, version);
//		//parent_node.append_attribute("value").set_value(value);
//		//TODO get class instance id
//	}
//	void Load(const pugi::xml_node& instance_node, const int version)
//	{
//		TProperty::Load(instance_node, version, world);
//		//value = instance_node.attribute("value").as_string();
//		//TODO find by class instance id
//	}
//};
//static bool TSceneClassInstanceProperty_registered = PropertiesFactory::Register("sceneClassInstance", TSceneClassInstanceProperty::Clone);
//
//class TClassSpriteInstanceProperty : public TPropertyValue<EngineInterface::IBaluClassSpriteInstance*>
//{
//public:
//	TClassSpriteInstanceProperty()
//	{
//	}
//	TClassSpriteInstanceProperty(EngineInterface::IBaluClassSpriteInstance* value) : TPropertyValue<EngineInterface::IBaluClassSpriteInstance*>(value)
//	{
//	}
//	static TProperty* Clone()
//	{
//		return new TClassSpriteInstanceProperty();
//	}
//	const char* GetTypeString()
//	{
//		return "classSpriteInstance";
//	}
//	EngineInterface::PropertyType GetType()
//	{
//		return EngineInterface::PropertyType::SceneClassInstance;
//	}
//	void Save(pugi::xml_node& parent_node, const int version)
//	{
//		TProperty::Save(parent_node, version);
//		//parent_node.append_attribute("value").set_value(value);
//		//TODO get class instance id
//	}
//	void Load(const pugi::xml_node& instance_node, const int version)
//	{
//		TProperty::Load(instance_node, version, world);
//		//value = instance_node.attribute("value").as_string();
//		//TODO find by class instance id
//	}
//};
//static bool TClassSpriteInstanceProperty_registered = PropertiesFactory::Register("classSpriteInstance", TClassSpriteInstanceProperty::Clone);

class TProperties : public EngineInterface::IProperties
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
	TProperties()
	{
		is_wrapper = false;
	}
	TProperties(bool is_wrapper)
	{
		this->is_wrapper = is_wrapper;
	}
	void AddProperty(const char* name, TProperty* prop)
	{
		EngineInterface::PropertyType type;
		assert(!HasProperty(std::string(name), type));
		properties[name].reset(prop);
	}
	bool HasProperty(const std::string& name, EngineInterface::PropertyType& type)
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
	void SetBool(const std::string& name, bool value)
	{
		if (is_wrapper)
			dynamic_cast<TBoolProperty*>(properties[name].get())->SetValue(value);
		else
		properties[name].reset(new TBoolProperty(value));
	}
	bool GetBool(const std::string& name)
	{
		bool* value = nullptr;
		Get(name, value);
		return *value;
	}
	/*void SetSceneClassInstance(const std::string& name, EngineInterface::IBaluSceneClassInstance* value)
	{
		if (is_wrapper)
			dynamic_cast<TSceneClassInstanceProperty*>(properties[name].get())->SetValue(value);
		else 
			properties[name].reset(new TSceneClassInstanceProperty(value));
	}
	EngineInterface::IBaluSceneClassInstance* GetSceneClassInstance(const std::string& name)
	{
		EngineInterface::IBaluSceneClassInstance** value = nullptr;
		Get(name, value);
		return *value;
	}
	void SetClassSpriteInstance(const std::string& name, EngineInterface::IBaluClassSpriteInstance* value)
	{
		if (is_wrapper)
			dynamic_cast<TClassSpriteInstanceProperty*>(properties[name].get())->SetValue(value);
		else
			properties[name].reset(new TClassSpriteInstanceProperty(value));
	}
	EngineInterface::IBaluClassSpriteInstance* GetClassSpriteInstance(const std::string& name)
	{
		EngineInterface::IBaluClassSpriteInstance** value = nullptr;
		Get(name, value);
		return *value;
	}*/
	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version);
};

