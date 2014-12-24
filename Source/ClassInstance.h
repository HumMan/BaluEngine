#pragma once

#include "Class.h"
#include "SpriteInstance.h"

class TSensorInstance
{
public:
	TSensor* source;
	std::unique_ptr<TBaluPhysShapeInstance> shape;
	TSensorInstance(TSensor* source)
	{
		this->source = source;
		shape = std::make_unique<TBaluPhysShapeInstance>(source->shape.get());
	}
};

class TBaluInstance;

class TBaluClassPhysBodyIntance
{
private:
	b2Body* phys_body;
	TBaluClassPhysBody* source;
	b2World* phys_world;
	std::vector<std::unique_ptr<TSensorInstance>> sensors;
	TBaluInstance* parent;
public:
	TBaluClassPhysBodyIntance(b2World* phys_world, TBaluClassPhysBody* source, TBaluInstance* parent);
	void SetFixedRotation(bool fixed);
	TVec2 GetLinearVelocity();
	void SetLinearVelocity(TVec2 velocity);
};

class TBaluInstance: public TProperties
{
private:
	int uid;
	TBaluClass* instance_class;
	TBaluTransform instance_transform;
	b2World* phys_world;

	

	std::vector<std::unique_ptr<TBaluSpriteInstance>> sprites;

	TBaluClassPhysBodyIntance phys_body;

	//TCustomMembersValues custom_values;

	//runtime
	//b2Body* phys_body
	//sprite_geometry_indices, vertices
	//

public:
	
	TBaluInstance(TBaluClass* source, b2World* phys_world);
	void SetTransform(TBaluTransform transform);

	TBaluClassPhysBodyIntance& GetPhysBody();

	int GetSpritesCount();
	TBaluSpriteInstance* GetSprite(int index);

	TAABB2 GetAABB();

	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);
};
