#pragma once

#include "PhysShape.h"

#include "EngineInterfaces\IPhysShapeInstance.h"

class TBaluInstance;
class TBaluClassSpriteInstance;
class TSensorInstance;

class TBaluPhysShapeInstance: public EngineInterface::IBaluPhysShapeInstance
{
protected:
	TBaluPhysShape* source;
	//TBaluTransform global;
	b2Fixture* fixture;
	b2Body* body;
	TBaluInstance* parent;
	TBaluClassSpriteInstance* sprite_instance;
public:
	TBaluPhysShapeInstance(TBaluPhysShape* source, TBaluInstance* parent_instance, TBaluClassSpriteInstance* sprite_instance);
	void BuildFixture(b2Body* body, TBaluTransformWithScale class_transform, TBaluTransformWithScale sprite_transform);

	//TODO попытаться сделать TBaluInstance
	IBaluInstance* GetParent();
	IBaluClassSpriteInstance* GetSpriteInstance();
};
