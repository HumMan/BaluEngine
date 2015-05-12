#pragma once

#include "Sprite.h"

#include "Class.h"

#include "SpritePolyInstance.h"
#include "PhysShapeInstance.h"

#include "EngineInterfaces\ISpriteInstance.h"

class TBaluSpriteInstance: public EngineInterface::IBaluSpriteInstance
{
private:
	TBaluSprite* source;
	
	TBaluTransformWithScale global;
	TBaluTransformWithScale local;

	std::unique_ptr<TBaluPhysShapeInstance> phys_shape;
	TBaluSpritePolygonInstance polygon;

	//TBaluInstance* parent;

public:

	TBaluSpriteInstance(TBaluSprite* source, TBaluTransformWithScale local, TBaluInstance* parent, TResources* resources);

	void SetTransform(TBaluTransform local);
	TBaluTransform GetTransform()
	{
		return local.transform;
	}
	TVec2 GetScale()
	{
		return local.scale;
	}
	TBaluSprite* GetSourceSprite();

	TAABB2 GetAABB();

	TBaluPhysShapeInstance* GetPhysShape();

	TBaluSpritePolygonInstance* GetPolygon();

	void PlayAnimation(std::string animation_name, bool loop);
	void PauseAnimation(bool pause);
	void StopAnimation();

	void UpdateTranform(TBaluTransformWithScale parent, TBaluTransformWithScale class_transform);
};