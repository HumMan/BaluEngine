#pragma once

#include "Sprite.h"

#include "Class.h"

#include "SpritePolyInstance.h"
#include "PhysShapeInstance.h"

class TBaluSpriteInstance
{
private:
	TBaluClass::TBaluSpriteInstance* source;
	TBaluTransform local;
	TBaluTransform global;
	
	TBaluSprite* sprite;
	
	std::unique_ptr<TBaluPhysShapeInstance> phys_shape;
	TBaluSpritePolygonInstance polygon;
public:
	TAABB2 GetAABB();

	TBaluPhysShapeInstance* GetPhysShape();

	TBaluSpritePolygonInstance& GetPolygon();

	void PlayAnimation(std::string animation_name, bool loop);
	void PauseAnimation(bool pause);
	void StopAnimation();
};