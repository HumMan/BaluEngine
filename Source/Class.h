#pragma once

#include "Sprite.h"

#include "Skeleton.h"
#include "SkeletonAnimation.h"

#include <map>

#include "EngineInterfaces\IClass.h"

//TODO определиться в какой СК передавать координаты курсора мыши
typedef void(*TMouseMoveCallback)(void* calle, TVec2 old_pos, TVec2 new_pos);

class TBaluClassPhysBody: public EngineInterface::IBaluClassPhysBody
{
private:
	b2BodyDef body_def;
	bool enable;
public:
	TBaluClassPhysBody();
	//TBaluClassPhysBody(TBaluClassPhysBody&& right)
	//	:body_def(std::move(right.body_def))
	//	, enable(std::move(right.enable))
	//{

	//}
	int GetSensorsCount();
	void SetFixedRotation(bool fixed);
	void SetPhysBodyType(TPhysBodyType type);
	void Enable(bool enable);
	bool IsEnable();
	b2BodyDef GetBodyDef();

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};


class TBaluClass : public EngineInterface::IBaluClass, public EngineInterface::IBaluWorldObject
{
private:
	std::string class_name;

	int layer_id;
	
	std::vector<std::unique_ptr<TBaluClassSpriteInstance>> sprites;
	TBaluClassPhysBody phys_body;
	std::unique_ptr<TSkeleton> skeleton;
	std::unique_ptr<TSkeletonAnimation> skeleton_animation;
	TProperties properties;

	std::map<TKey, std::vector<TSpecialCallback<KeyUpDownCallback>>> on_key_down_callbacks;
	std::map<TKey, std::vector<TSpecialCallback<KeyUpDownCallback>>> on_key_up_callbacks;
	std::vector<TSpecialCallback<BeforePhysicsCallback>> before_physics_callbacks;

	void Initialize();

	TBaluWorld* world;
public:
	TBaluClass(const char* name, TBaluWorld* world)
	{
		Initialize();
		this->class_name = name;		
		this->world = world;
	}

	EngineInterface::IProperties* GetProperties()
	{
		return &properties;
	}
	bool PointCollide(TVec2 class_space_point);
	TAABB2 GetAABB();

	std::string GetName();
	void SetName(std::string name);

	virtual ~TBaluClass();

	void OnMouseMove(TMouseMoveCallback);

	TBaluClassSpriteInstance* AddSprite(TBaluSprite* sprite);
	EngineInterface::IBaluClassSpriteInstance* AddSprite(EngineInterface::IBaluSprite* sprite);
	void RemoveSprite(TBaluSprite* sprite);
	int GetSpritesCount();
	TBaluClassSpriteInstance* GetSprite(int index);
	
	TBaluClassPhysBody* GetPhysBody();

	TSkeletonAnimation* GetSkeletonAnimation();
	TSkeleton* GetSkeleton();

	void OnKeyDown(TKey key, TSpecialCallback<KeyUpDownCallback> callback);
	void OnKeyUp(TKey key, TSpecialCallback<KeyUpDownCallback> callback);
	void OnBeforePhysicsStep(TSpecialCallback<BeforePhysicsCallback> callback);

	std::map<TKey, std::vector<TSpecialCallback<KeyUpDownCallback>>>& GetOnKeyDown();
	std::map<TKey, std::vector<TSpecialCallback<KeyUpDownCallback>>>& GetOnKeyUp();
	std::vector<TSpecialCallback<BeforePhysicsCallback>>& GetOnBeforePhysicsStep();

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};