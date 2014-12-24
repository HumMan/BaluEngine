#pragma once

#include "PhysShape.h"

class TBaluPhysShapeInstance
{
protected:
	TBaluPhysShape* source;
	TBaluTransform global;
	b2Fixture* fixture;
	b2Body* body;
public:
	TBaluPhysShapeInstance(TBaluPhysShape* source);
	void BuildFixture(b2Body* body);
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