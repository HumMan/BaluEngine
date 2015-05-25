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

	TBaluClass::TBaluSpriteInstance* sprite_source;
	
	TBaluTransformWithScale global;
	TBaluTransformWithScale local;

	std::unique_ptr<TBaluPhysShapeInstance> phys_shape;
	TBaluSpritePolygonInstance polygon;

	//TBaluInstance* parent;
	TProperties properties;
public:
	EngineInterface::IProperties* GetProperties()
	{
		return &properties;
	}

	TBaluSpriteInstance(TBaluSprite* source, TBaluClass::TBaluSpriteInstance* sprite_source, TBaluTransformWithScale local, TBaluInstance* parent, TResources* resources);

	void SetTransform(TBaluTransform local)
	{
		this->local.transform = local;
	}
	TBaluTransform GetTransform()
	{
		return local.transform;
	}
	TVec2 GetScale()
	{
		return local.scale;
	}
	void SetScale(TVec2 scale)
	{
		local.scale = scale;
	}
	TBaluSprite* GetSourceSprite();
	TBaluClass::TBaluSpriteInstance* GetSourceSpriteInstance()
	{
		return sprite_source;
	}

	TOBB2 GetOBB();

	TBaluPhysShapeInstance* GetPhysShape();

	TBaluSpritePolygonInstance* GetPolygon();

	void PlayAnimation(std::string animation_name, bool loop);
	void PauseAnimation(bool pause);
	void StopAnimation();

	void UpdateTranform(TBaluTransformWithScale parent, TBaluTransformWithScale class_transform);
};