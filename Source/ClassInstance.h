#pragma once

#include "Class.h"
#include "SpriteInstance.h"
#include "SkeletonInstance.h"
#include "SkeletonAnimationInstance.h"

#include "EngineInterfaces\IClassInstance.h"

class TBaluInstance;

class TBaluClassPhysBodyIntance : public EngineInterface::IBaluClassPhysBodyIntance
{
private:
	b2Body* phys_body;
	TBaluClassPhysBody* source;
	b2World* phys_world;
	TBaluInstance* parent;

	TBaluTransform local;

	bool is_enable;
	
public:
	TBaluClassPhysBodyIntance(b2World* phys_world, TBaluClassPhysBody* source, TBaluInstance* parent);

	void BuildAllFixtures();
	
	bool IsEnable();
	b2BodyDef GetBodyDef();
	void SetFixedRotation(bool fixed);

	TVec2 GetLinearVelocity();
	void SetLinearVelocity(TVec2 velocity);
	
	float GetAngularVelocity();
	void SetAngularVelocity(float velocity);

	TBaluTransform GetTransform();
	void SetTransform(TBaluTransform transform);
};

class TBaluClassInstance :public EngineInterface::IBaluClassInstance
{
private:
	TBaluClass* source;

	std::map<TKey, std::vector<TScript>> on_key_down_callbacks;
	std::map<TKey, std::vector<TScript>> on_key_up_callbacks;
	std::vector<TScript> before_physics_callbacks;
public:

	TBaluClass* GetClass()
	{
		return source;
	}
	void DoKeyDown(TKey key, TBaluInstance* instance);
	void DoKeyUp(TKey key, TBaluInstance* instance);

	void DoBeforePhysicsStep(TBaluInstance* instance);
	//void DoSensorCollide(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
	//void DoBeginContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
	//void DoEndContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
};

class TBaluInstance : public EngineInterface::IBaluInstance
{
private:
	int uid;
	TBaluClassInstance* instance_class;
	TBaluTransformWithScale instance_transform;

	b2World* phys_world;

	std::vector<std::unique_ptr<TBaluClassInstanceSpriteInstance>> sprites;
	std::unique_ptr<TBaluClassPhysBodyIntance> phys_body;
	TSkeletonInstance skeleton;
	TSkeletonAnimationInstance skeleton_animation;

	TProperties properties;

	TResources* resources;
	void* tag;
public:
	TBaluClassInstance* GetClass();
	void SetTag(void* tag)
	{
		this->tag = tag;
	}
	void* GetTag()
	{
		return tag;
	}

	TBaluInstance(TBaluClassInstance* source, b2World* phys_world, TBaluTransform transform, TVec2 scale, TResources* resources);
	void SetTransform(TBaluTransform transform);
	TBaluTransform GetTransform();
	TVec2 GetScale();
	void SetScale(TVec2 scale);
	TProperties* GetProperties();

	TBaluClassPhysBodyIntance* GetPhysBody();

	int GetSpritesCount();
	TBaluClassInstanceSpriteInstance* GetSprite(int index);
	TBaluClassInstanceSpriteInstance* AddSprite(IBaluClassSpriteInstance* source);

	TSkeletonAnimationInstance* GetSkeletonAnimation();

	bool PointCollide(TVec2 class_space_point, EngineInterface::IBaluClassInstanceSpriteInstance* &result);
	bool PointCollide(TVec2 scene_space_point);
	TOBB2 GetOBB();
	TAABB2 GetAABB();
	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);

	void UpdateTranform();


};
