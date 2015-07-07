#pragma once

#include "Class.h"
#include "SpriteInstance.h"
#include "SkeletonInstance.h"
#include "SkeletonAnimationInstance.h"

#include "EngineInterfaces\IClassInstance.h"

class TBaluInstance;
class TBaluWorldInstance;

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

struct TSpriteWithClassCollideInstance
{
	IBaluSprite* sprite;
	IBaluClass* with_class;
	TScriptInstance script;
	TSpriteWithClassCollideInstance()
	{
		sprite = nullptr;
		with_class = nullptr;
	}
	TSpriteWithClassCollideInstance(IBaluSprite* sprite, IBaluClass* with_class, TScriptInstance script)
	{
		this->sprite = sprite;
		this->with_class = with_class;
		this->script = script;
	}
};

class TBaluClassInstance :public EngineInterface::IBaluClassInstance
{
private:
	TBaluWorldInstance* world_instance;
	TBaluClass* source;

	std::vector<std::pair<TKey, TScriptInstance>> on_key_down_callbacks;
	std::vector<std::pair<TKey, TScriptInstance>> on_key_up_callbacks;
	std::vector<TScriptInstance> before_physics_callbacks;
	std::vector<TSpriteWithClassCollideInstance> on_collide_callbacks;
public:
	TBaluClassInstance(TBaluWorldInstance* world_instance, TBaluClass* source);
	TBaluClass* GetClass()
	{
		return source;
	}
	void CompileScripts(std::vector<std::string>& errors_list);

	void DoKeyDown(TKey key, TBaluInstance* instance);
	void DoKeyUp(TKey key, TBaluInstance* instance);
	void DoBeforePhysicsStep(TBaluInstance* instance);
	void DoCollide(TBaluPhysShapeInstance* obj_a, TBaluInstance* obstancle);
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
