#pragma once

#include "SpritePoly.h"
#include "PhysShape.h"

#include "EngineInterfaces\ISprite.h"
#include "EngineInterfaces\ISpriteInstance.h"

#include <pugixml.hpp>

using namespace pugi;

class TBaluClass;

//namespace pugi
//{
//	class xml_node;
//}

namespace EngineInterface
{
	class IBaluPhysShapeInstance;
	class IBaluInstance;
	class IBaluClass;
	class IBaluClassSpriteInstance;
}

class TProperty
{
public:
	virtual const char* GetTypeString() = 0;
	virtual EngineInterface::PropertyType GetType() = 0;
	void Save(pugi::xml_node& parent_node, const int version)
	{
		parent_node.append_attribute("type").set_value(GetTypeString());
	}
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
	{

	}
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
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
	{
		TProperty::Load(instance_node, version, world);
	}	
};
static bool TBoolProperty_registered = PropertiesFactory::Register("bool", TBoolProperty::Clone);

class TSceneClassInstanceProperty : public TPropertyValue<EngineInterface::IBaluSceneClassInstance*>
{
public:
	TSceneClassInstanceProperty()
	{
	}
	TSceneClassInstanceProperty(EngineInterface::IBaluSceneClassInstance* value) : TPropertyValue<EngineInterface::IBaluSceneClassInstance*>(value)
	{
	}
	static TProperty* Clone()
	{
		return new TSceneClassInstanceProperty();
	}
	const char* GetTypeString()
	{
		return "sceneClassInstance";
	}
	EngineInterface::PropertyType GetType()
	{
		return EngineInterface::PropertyType::SceneClassInstance;
	}
	void Save(pugi::xml_node& parent_node, const int version)
	{
		TProperty::Save(parent_node, version);
		//parent_node.append_attribute("value").set_value(value);
		//TODO get class instance id
	}
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
	{
		TProperty::Load(instance_node, version, world);
		//value = instance_node.attribute("value").as_string();
		//TODO find by class instance id
	}
};
static bool TSceneClassInstanceProperty_registered = PropertiesFactory::Register("sceneClassInstance", TSceneClassInstanceProperty::Clone);

class TClassSpriteInstanceProperty : public TPropertyValue<EngineInterface::IBaluClassSpriteInstance*>
{
public:
	TClassSpriteInstanceProperty()
	{
	}
	TClassSpriteInstanceProperty(EngineInterface::IBaluClassSpriteInstance* value) : TPropertyValue<EngineInterface::IBaluClassSpriteInstance*>(value)
	{
	}
	static TProperty* Clone()
	{
		return new TClassSpriteInstanceProperty();
	}
	const char* GetTypeString()
	{
		return "classSpriteInstance";
	}
	EngineInterface::PropertyType GetType()
	{
		return EngineInterface::PropertyType::SceneClassInstance;
	}
	void Save(pugi::xml_node& parent_node, const int version)
	{
		TProperty::Save(parent_node, version);
		//parent_node.append_attribute("value").set_value(value);
		//TODO get class instance id
	}
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
	{
		TProperty::Load(instance_node, version, world);
		//value = instance_node.attribute("value").as_string();
		//TODO find by class instance id
	}
};
static bool TClassSpriteInstanceProperty_registered = PropertiesFactory::Register("classSpriteInstance", TClassSpriteInstanceProperty::Clone);

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
		if (ptr==nullptr)
			throw std::invalid_argument("Неправильный тип свойства");
		value = ptr->GetValue();
	}
public:
	TProperties()
	{
	}
	//TProperties(TProperties&& right)
	//	:properties(std::move(right.properties))
	//{
	//}
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
		static char name1[] = "bool";
		properties[name].reset(new TBoolProperty(value));
	}
	bool GetBool(const std::string& name)
	{
		bool* value = nullptr;
		Get(name, value);
		return *value;
	}
	void SetSceneClassInstance(const std::string& name, EngineInterface::IBaluSceneClassInstance* value)
	{
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
		properties[name].reset(new TClassSpriteInstanceProperty(value));
	}
	EngineInterface::IBaluClassSpriteInstance* GetClassSpriteInstance(const std::string& name)
	{
		EngineInterface::IBaluClassSpriteInstance** value = nullptr;
		Get(name, value);
		return *value;
	}
	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};



class TBaluSprite :public EngineInterface::IBaluSprite, public EngineInterface::IBaluWorldObject
{
private:
	std::string sprite_name;
	
	TBaluSpritePolygon sprite_polygon;
	std::unique_ptr<TBaluPhysShape> phys_shape;
	
	int layer;
	TProperties properties;

	std::vector<std::pair<IBaluClass*, CallbackWithData<CollideCallback>>> on_collide_callbacks;
public:
	TBaluSprite(const char* name)
	{
		this->sprite_name = name;
	}
	void AddOnCollide(IBaluClass* obstancle_class, CallbackWithData<CollideCallback> callback);
	std::vector<std::pair<IBaluClass*, CallbackWithData<CollideCallback>>>& GetOnCollide();
	CallbackWithData<CollideCallback>* TBaluSprite::GetOnCollide(TBaluClass* obstancle_class);
	void RemoveOnCollide(int index);

	EngineInterface::IProperties* GetProperties()
	{
		return &properties;
	}
	TBaluSprite();

	std::string GetName();
	void SetName(std::string name);

	void SetPhysShape(TBaluPhysShape* shape);
	void SetPhysShape(EngineInterface::IBaluPhysShape* shape);

	TBaluPhysShape* GetPhysShape();
	void SetPhysShapeFromGeometry();

	TBaluSpritePolygon* GetPolygon();

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};


class TBaluClassSpriteInstance : public EngineInterface::IBaluClassSpriteInstance
{
	TBaluSprite* sprite;
	TBaluTransformWithScale local;
public:
	//std::string tag;

	TBaluSprite* GetSprite()
	{
		return sprite;
	}
	TBaluClassSpriteInstance()
	{
		sprite = nullptr;
	}
	TBaluClassSpriteInstance(TBaluSprite* sprite)
	{
		this->sprite = sprite;
	}
	void SetTransform(TBaluTransform transform)
	{
		this->local.transform = transform;
	}
	void SetScale(TVec2 scale)
	{
		this->local.scale = scale;
	}
	TBaluTransformWithScale GetTransformWithScale()
	{
		return local;
	}
	TBaluTransform GetTransform()
	{
		return local.transform;
	}
	TVec2 GetScale()
	{
		return local.scale;
	}
	bool PointCollide(TVec2 class_space_point)
	{
		TVec2 p = local.ToLocal(class_space_point);
		bool is_in_sprite = GetSprite()->GetPolygon()->PointCollide(p);
		return (is_in_sprite);
	}
	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};