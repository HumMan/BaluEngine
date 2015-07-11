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

	std::map<TKey, std::vector<TScript>> on_key_down_callbacks;
	std::map<TKey, std::vector<TScript>> on_key_up_callbacks;
	std::vector<TScript> before_physics_callbacks;

	std::vector<TSpriteWithClassCollide> on_collide_callbacks;

	void Initialize();

	TBaluWorld* world;
public:

	void AddOnCollide(IBaluSprite* sprite, IBaluClass* obstancle_class, TScript callback);
	std::vector<TSpriteWithClassCollide>& GetOnCollide();
	TScript* GetOnCollide(IBaluSprite* sprite, TBaluClass* obstancle_class);
	void RemoveOnCollide(int index);

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

	void OnKeyDown(TKey key, TScript callback);
	void OnKeyUp(TKey key, TScript callback);
	void OnBeforePhysicsStep(TScript callback);

	std::map<TKey, std::vector<TScript>>& GetOnKeyDown();
	std::map<TKey, std::vector<TScript>>& GetOnKeyUp();
	std::vector<TScript>& GetOnBeforePhysicsStep();

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};