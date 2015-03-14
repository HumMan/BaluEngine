#pragma once

#include "Sprite.h"

#include "Skeleton.h"
#include "SkeletonAnimation.h"

#include <map>

#include "EngineInterfaces\IClass.h"
#include "EngineInterfaces\ISpriteInstance.h"

//TODO определиться в какой СК передавать координаты курсора мыши
typedef void(*TMouseMoveCallback)(void* calle, TVec2 old_pos, TVec2 new_pos);


class TSensor: public EngineInterface::ISensor
{
public:
	//std::unique_ptr<TBaluPhysShape> shape;
	std::unique_ptr<TBaluPhysShape> phys_shape;
	//std::vector<SensorCollideCallback> on_sensor_collide_callbacks;
	std::vector<SensorCollideCallback> on_begin_contact, on_end_contact;
	TSensor(TBaluPhysShape* shape)
	{
		//this->shape.reset(shape);
		this->phys_shape.reset(shape);
	}
};

class TBaluClassPhysBody: public EngineInterface::IBaluClassPhysBody
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
	EngineInterface::ISensor* CreateSensor(EngineInterface::IBaluPhysShape* shape);
};

class TBaluClass : public TProperties, public EngineInterface::IBaluClass, public EngineInterface::IBaluWorldObject
{
public:
	class TBaluSpriteInstance : public EngineInterface::IBaluClassSprite
	{
	public:
		TBaluSprite* sprite;
		std::string tag;
		TBaluTransform local;
		TVec2 scale;
		TBaluSpriteInstance()
		{
			sprite = nullptr;
		}
		TBaluSpriteInstance(TBaluSprite* sprite)
		{
			this->sprite = sprite;
			local = TBaluTransform(TVec2(0, 0), TRot(0));
			scale = TVec2(1, 1);
		}
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};

private:
	std::string layer_name;
	std::string class_name;
	std::vector<std::unique_ptr<TBaluSpriteInstance>> sprites;
	TBaluClassPhysBody phys_body;
	TSkeleton skeleton;
	TSkeletonAnimation skeleton_animation;
	TProperties properties;
public:
	EngineInterface::IProperties* GetProperties()
	{
		return &properties;
	}
	bool PointCollide(TVec2 class_space_point);
	TAABB2 GetAABB();

	std::map<TKey, std::vector<CallbackWithData<KeyUpDownCallback>>> on_key_down_callbacks;
	std::map<TKey, std::vector<CallbackWithData<KeyUpDownCallback>>> on_key_up_callbacks;

	std::vector<BeforePhysicsCallback> before_physics_callbacks;

	std::string GetName();
	void SetName(std::string name);

	TBaluClass();
	TBaluClass(TBaluClass&& right);
	virtual ~TBaluClass();

	void OnMouseMove(TMouseMoveCallback);

	TBaluSpriteInstance* AddSprite(TBaluSprite* sprite);
	EngineInterface::IBaluClassSprite* AddSprite(EngineInterface::IBaluSprite* sprite);
	void RemoveSprite(TBaluSprite* sprite);
	int GetSpritesCount();
	TBaluSpriteInstance* GetSprite(int index);
	
	TBaluClassPhysBody* GetPhysBody();

	TSkeletonAnimation* GetSkeletonAnimation();
	TSkeleton* GetSkeleton();

	void CreateBone();
	void AttachSpriteToBone();
	void CreateAnimationLine();
	void SetBoneTransform();

	void CreateKeyFrame();
	void SetAnimationTime();

	void OnKeyDown(TKey key, CallbackWithData<KeyUpDownCallback> callback);
	void OnKeyUp(TKey key, CallbackWithData<KeyUpDownCallback> callback);

	void OnBeforePhysicsStep(BeforePhysicsCallback callback);

	void OnBeginContact(TSensor* sensor, SensorCollideCallback callback);
	void OnBeginContact(EngineInterface::ISensor* sensor, SensorCollideCallback callback);

	void OnEndContact(TSensor* sensor, SensorCollideCallback callback);
	void OnEndContact(EngineInterface::ISensor* sensor, SensorCollideCallback callback);

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};