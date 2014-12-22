#pragma once

#include "Class.h"
#include "SpriteInstance.h"

class TBaluClassPhysBodyIntance
{
private:
public:
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
	
	std::vector<std::unique_ptr<TBaluSpriteInstance>> sprites;

	//TCustomMembersValues custom_values;

	//runtime
	//b2Body* phys_body
	//sprite_geometry_indices, vertices
	//
public:
	TBaluInstance(TBaluClass* source);
	void SetTransform(TBaluTransform transform);

	TBaluClassPhysBodyIntance& GetPhysBody();

	TAABB2 GetAABB();

	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results);
};
