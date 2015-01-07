#pragma once

#include "Sprite.h"

#include "Skeleton.h"
#include "SkeletonAnimation.h"

#include <map>

typedef void(*TMouseMoveCallback)(void* calle, TVec2 old_pos, TVec2 new_pos);

enum TPhysBodyType
{
	Static,
	Dynamic,
	Kinematic
};

class TBaluInstance;
class TBaluPhysShapeInstance;
class TSensorInstance;

typedef void (*KeyDownCallback)(TBaluInstance* object);
typedef void (*BeforePhysicsCallback)(TBaluInstance* object);
typedef void (*SensorCollideCallback)(TBaluInstance* source, TSensorInstance* sensor, TBaluInstance* obstacle, TBaluPhysShapeInstance* obstacle_shape);

class TSensor
{
public:
	std::unique_ptr<TBaluPhysShape> shape;
	//std::vector<SensorCollideCallback> on_sensor_collide_callbacks;
	std::vector<SensorCollideCallback> on_begin_contact, on_end_contact;
	TSensor(TBaluPhysShape* shape)
	{
		this->shape.reset(shape);
	}
};

class TBaluClassPhysBody
{
private:
	b2BodyDef body_def;
	bool enable;
	std::vector<std::unique_ptr<TSensor>> sensors;
public:
	TBaluClassPhysBody();
	int GetSensorsCount();
	TSensor* GetSensor(int index);
	void SetFixedRotation(bool fixed);
	void SetPhysBodyType(TPhysBodyType type);
	void Enable(bool enable);
	bool IsEnable();
	b2BodyDef GetBodyDef();
	TSensor* CreateSensor(TBaluPhysShape* shape);
};

enum TKey:int
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
		if (properties.find(name) == properties.end())
		{
			SetBool(name, false);
		}
		if (properties[name].type != TProperty::Type::Bool)
			throw std::invalid_argument("������������ ��� ��������");
		return properties[name].bool_val;
	}
};



class TBaluClass: public TProperties
{
public:
	class TBaluSpriteInstance
	{
	public:
		TBaluSprite* sprite;
		std::string tag;
		TBaluTransform local;
		TBaluSpriteInstance(TBaluSprite* sprite)
		{
			this->sprite = sprite;
		}
	};

	

private:
	std::string class_name;
	std::vector<std::unique_ptr<TBaluSpriteInstance>> sprites;
	TBaluClassPhysBody phys_body;
	TSkeleton skeleton;
	TSkeletonAnimation skeleton_animation;
public:
	std::map<TKey, std::vector<KeyDownCallback>> one_key_down_callbacks;
	std::vector<BeforePhysicsCallback> before_physics_callbacks;

	std::string GetName();
	void SetName(std::string name);

	TBaluClass();
	TBaluClass(TBaluClass&& right);
	virtual ~TBaluClass();

	void OnMouseMove(TMouseMoveCallback);
	TBaluSpriteInstance* AddSprite(TBaluSprite* sprite);
	void RemoveSprite(TBaluSprite* sprite);
	int GetSpritesCount();
	TBaluSpriteInstance* GetSprite(int index);

	
	TBaluClassPhysBody& GetPhysBody();

	TSkeletonAnimation& GetSkeletonAnimation();
	TSkeleton& GetSkeleton();

	void CreateBone();
	void AttachSpriteToBone();
	void CreateAnimationLine();
	void SetBoneTransform();

	void CreateKeyFrame();
	void SetAnimationTime();

	void OnKeyDown(TKey key, KeyDownCallback callback);
	void OnBeforePhysicsStep(BeforePhysicsCallback callback);
	//void OnSensorCollide(TSensor* sensor, SensorCollideCallback callback);
	void OnBeginContact(TSensor* sensor, SensorCollideCallback callback);
	void OnEndContact(TSensor* sensor, SensorCollideCallback callback);
};