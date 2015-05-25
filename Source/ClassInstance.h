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

class TBaluInstance: public EngineInterface::IBaluInstance//, TLayerObjectInstance
{
private:
	int uid;
	TBaluClass* instance_class;
	TBaluTransformWithScale instance_transform;

	b2World* phys_world;

	std::vector<std::unique_ptr<TBaluSpriteInstance>> sprites;
	std::unique_ptr<TBaluClassPhysBodyIntance> phys_body;
	TSkeletonInstance skeleton;
	TSkeletonAnimationInstance skeleton_animation;

	TProperties properties;

	TResources* resources;

public:
	TBaluClass* GetClass();
	bool PointCollide(TVec2 scene_space_point);

	TOBB2 GetOBB();

	TBaluInstance(TBaluClass* source, b2World* phys_world, TBaluTransform transform, TVec2 scale, TResources* resources);
	void SetTransform(TBaluTransform transform);
	TBaluTransform GetTransform();
	TVec2 GetScale();
	void SetScale(TVec2 scale);
	TProperties* GetProperties();

	TBaluClassPhysBodyIntance* GetPhysBody();

	int GetSpritesCount();
	TBaluSpriteInstance* GetSprite(int index);
	TBaluSpriteInstance* AddSprite(IBaluSprite* source, TBaluTransformWithScale local_transform);

	TAABB2 GetAABB();

	TSkeletonAnimationInstance* GetSkeletonAnimation();

	bool PointCollide(TVec2 class_space_point, EngineInterface::IBaluSpriteInstance* &result);

	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);

	void UpdateTranform();

	void DoKeyDown(TKey key);
	void DoKeyUp(TKey key);

	void DoBeforePhysicsStep();
	//void DoSensorCollide(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
	void DoBeginContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
	void DoEndContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
};
