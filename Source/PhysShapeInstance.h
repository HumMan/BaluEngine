#pragma once

#include "PhysShape.h"

#include "EngineInterfaces\IPhysShapeInstance.h"

class TBaluInstance;
class TSensorInstance;

class TBaluPhysShapeInstance: public EngineInterface::IBaluPhysShapeInstance
{
protected:
	TBaluPhysShape* source;
	TBaluTransform global;
	b2Fixture* fixture;
	b2Body* body;
	TBaluInstance* parent;

	bool is_sensor;
	TSensorInstance* sensor;
public:
	bool IsSensor()
	{
		return is_sensor;
	}
	TBaluPhysShapeInstance(TBaluPhysShape* source, TBaluInstance* parent, TSensorInstance* sensor=nullptr);
	void BuildFixture(b2Body* body);
	TBaluInstance* GetParent();
	TSensorInstance* GetParentSensor();
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