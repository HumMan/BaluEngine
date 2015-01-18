#pragma once

#include "Class.h"
#include "SpriteInstance.h"
#include "SkeletonInstance.h"
#include "SkeletonAnimationInstance.h"

#include "EngineInterfaces.h"

class TSensorInstance
{
public:
	TSensor* source;
	std::unique_ptr<TBaluPhysShapeInstance> shape;
	TBaluInstance* parent;



	TSensorInstance(TSensor* source, TBaluInstance* parent);
	void BuildFixture(b2Body* body);
};

class TBaluInstance;

class TBaluClassPhysBodyIntance : public EngineInterface::IBaluClassPhysBodyIntance
{
private:
	b2Body* phys_body;
	TBaluClassPhysBody* source;
	b2World* phys_world;
	std::vector<std::unique_ptr<TSensorInstance>> sensors;
	TBaluInstance* parent;

	TBaluTransform local;
public:
	TBaluClassPhysBodyIntance(b2World* phys_world, TBaluClassPhysBody* source, TBaluInstance* parent);
	
	bool IsEnable();
	b2BodyDef GetBodyDef();
	void SetFixedRotation(bool fixed);

	TVec2 GetLinearVelocity();
	void SetLinearVelocity(TVec2 velocity);
	
	float GetAngularVelocity();
	void SetAngularVelocity(float velocity);

	TBaluTransform GetTransform();
};

class TBaluInstance:  EngineInterface::IBaluInstance//, TLayerObjectInstance
{
private:
	int uid;
	TBaluClass* instance_class;
	TBaluTransform instance_transform;
	b2World* phys_world;

	std::vector<std::unique_ptr<TBaluSpriteInstance>> sprites;
	std::unique_ptr<TBaluClassPhysBodyIntance> phys_body;
	TSkeletonInstance skeleton;
	TSkeletonAnimationInstance skeleton_animation;

	TProperties properties;

public:
	
	TBaluInstance(TBaluClass* source, b2World* phys_world, TBaluTransform transform, TResourses* resources);
	void SetTransform(TBaluTransform transform);
	TBaluTransform GetTransform();

	TProperties* GetProperties();

	TBaluClassPhysBodyIntance* GetPhysBody();

	int GetSpritesCount();
	TBaluSpriteInstance* GetSprite(int index);

	TAABB2 GetAABB();

	TSkeletonAnimationInstance& GetSkeletonAnimation();

	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);

	void UpdateTranform();

	void DoKeyDown(TKey key);
	void DoBeforePhysicsStep();
	//void DoSensorCollide(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
	void DoBeginContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
	void DoEndContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
};
