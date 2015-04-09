#pragma once

#include "PhysShape.h"

#include "EngineInterfaces\IPhysShapeInstance.h"

class TBaluInstance;
class TBaluSpriteInstance;
class TSensorInstance;

class TBaluPhysShapeInstance: public EngineInterface::IBaluPhysShapeInstance
{
protected:
	TBaluPhysShape* source;
	//TBaluTransform global;
	b2Fixture* fixture;
	b2Body* body;
	TBaluInstance* parent;
	TBaluSpriteInstance* sprite_instance;
public:
	TBaluPhysShapeInstance(TBaluPhysShape* source, TBaluInstance* parent_instance, TBaluSpriteInstance* sprite_instance);
	void BuildFixture(b2Body* body, TVec2 class_scale, TBaluTransform class_transform, TVec2 sprite_scale, TBaluTransform sprite_transform);

	//TODO попытаться сделать TBaluInstance
	IBaluInstance* GetParent();
	IBaluSpriteInstance* GetSpriteInstance();
};

//
//class TBaluPolygonShapeInstance : public TBaluPhysShapeInstance
//{
//private:
//	TBaluPolygonShape* source;
//public:
//	TBaluPolygonShapeInstance(TBaluPolygonShape* source);
//	void BuildFixture(b2Body &body);
//};
//
//class TBaluCircleShapeInstance : public TBaluPhysShapeInstance
//{
//private:
//	TBaluCircleShape* source;
//public:
//	TBaluCircleShapeInstance(TBaluCircleShape* source);
//	void BuildFixture(b2Body &body);
//};
//
//class TBaluBoxShapeInstance : public TBaluPhysShapeInstance
//{
//private:
//	TBaluBoxShape* source;
//public:
//	TBaluBoxShapeInstance(TBaluBoxShape* source);
//	void BuildFixture(b2Body &body);
//};