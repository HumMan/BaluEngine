#pragma once

#include "Class.h"
#include "SpriteInstance.h"

class TBaluInstance
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
	void SetStringValue();
	void SetDoubleValue();
};
