#pragma once

#include "Sprite.h"

#include <map>

typedef void(*TMouseMoveCallback)(void* calle, TVec2 old_pos, TVec2 new_pos);

enum TPhysBodyType
{
	Static,
	Dynamic,
	Kinematic
};

class TBaluClassPhysBody
{
private:
public:
	void SetFixedRotation(bool fixed);
	void SetPhysBodyType(TPhysBodyType type);
	void Enable(bool enable);
};

enum TKey
{
	Left,
	Right,
	Up,
	Down
};

class TProperties
{
	struct TProperty
	{
		enum Type
		{
			Bool,
			Int,
			Float,
			String,
		};
		Type type;
		bool bool_val;
		int int_val;
		float float_val;
		std::string string_val;
		TProperty(){}
		TProperty(bool value)
		{
			type = Type::Bool;
			bool_val = value;
		}
	};
	std::map<std::string,TProperty> properties;
public:
	void SetBool(std::string name, bool value)
	{
		properties[name] = TProperty(value);
	}
	bool GetBool(std::string name)
	{
		if (properties[name].type != TProperty::Type::Bool)
			throw std::invalid_argument("Неправильный тип свойства");
		return properties[name].bool_val;
	}
};

class TBaluInstance;
class TBaluPhysShapeInstance;

class TBaluClass: public TProperties
{
public:
	class TBaluSpriteInstance
	{
	public:
		TBaluSprite* sprite;
		std::string tag;
		TBaluTransform local;
	};
	class TSensor
	{
	public:

	};

	typedef void (KeyDownCallback)(TBaluInstance* object);
	typedef void (BeforePhysicsCallback)(TBaluInstance* object);
	typedef void (SensorCollideCallback)(TBaluInstance* source, TSensor* sensor, TBaluInstance* obstacle, TBaluPhysShapeInstance* obstacle_shape);

private:
	std::string class_name;
	std::vector<std::unique_ptr<TBaluSpriteInstance>> sprites;

	void ConstructPhysBody(b2Body& body);
public:
	std::string GetName();
	TBaluClass();
	TBaluClass(TBaluClass&& right);
	virtual ~TBaluClass();

	void OnMouseMove(TMouseMoveCallback);
	TBaluSpriteInstance* AddSprite(TBaluSprite* sprite);
	void RemoveSprite(TBaluSprite* sprite);

	
	TBaluClassPhysBody& GetPhysBody();

	TSensor CreateSensor(TBaluPhysShape* shape);

	void CreateBone();
	void AttachSpriteToBone();
	void CreateAnimationLine();
	void SetBoneTransform();

	void CreateKeyFrame();
	void SetAnimationTime();

	void OnKeyDown(TKey key, KeyDownCallback callback);
	void OnBeforePhysicsStep(BeforePhysicsCallback callback);
	void OnSensorCollide(TSensor sensor, SensorCollideCallback callback);
};