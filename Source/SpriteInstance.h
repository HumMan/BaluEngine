#pragma once

#include "Sprite.h"

#include "Class.h"

#include "SpritePolyInstance.h"
#include "PhysShapeInstance.h"

class TBaluSpriteInstance
{
private:
	TBaluSprite* source;
	TBaluTransform local;
	TBaluTransform global;
	
	std::unique_ptr<TBaluPhysShapeInstance> phys_shape;
	TBaluSpritePolygonInstance polygon;

	//TBaluInstance* parent;

public:

	TBaluSpriteInstance(TBaluSprite* source, TBaluTransform local, TBaluInstance* parent, TResourses* resources);

	void SetTransform(TBaluTransform local);
	TBaluTransform GetTransform();
	TBaluSprite* GetSourceSprite();

	TAABB2 GetAABB();

	TBaluPhysShapeInstance* GetPhysShape();

	TBaluSpritePolygonInstance& GetPolygon();

	void PlayAnimation(std::string animation_name, bool loop);
	void PauseAnimation(bool pause);
	void StopAnimation();

	void UpdateTranform(TBaluTransform parent);
};