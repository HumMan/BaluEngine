#pragma once

#include "Material.h"

#include <Box2D.h>

#include "IPhysShape.h"

using namespace EngineInterface;

class TBaluPhysShape: public EngineInterface::IBaluPhysShape
{
protected:
	TBaluTransformWithScale local;
	bool is_sensor;
public:
	TBaluPhysShape()
	{
		is_sensor = false;
	}
	virtual ~TBaluPhysShape(){}
	virtual b2Shape* GetShape(TBaluTransformWithScale class_transform) = 0;
	void SetTransform(TBaluTransform local)
	{
		this->local.transform = local;
	}
	void SetScale(TVec2 scale)
	{
		this->local.scale = scale;
	}
	void SetIsSensor(bool value)
	{
		is_sensor = value;
	}
	bool IsSensor()
	{
		return is_sensor;
	}
	//virtual TBaluPhysShape* GetPhysShape() = 0;
	virtual void Save(pugi::xml_node& parent_node, const int version)=0;
	virtual void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)=0;
};

typedef TBaluPhysShape*(*PhysShapeClone)();
class PhysShapeFactory
{
public:
	static bool Register(const char* name, PhysShapeClone clone);
	static TBaluPhysShape* Create(const char* name);
};


class TBaluPolygonShape : public TBaluPhysShape, public EngineInterface::IBaluPolygonShape
{
protected:
	b2PolygonShape b2shape;
public:
	TBaluPolygonShape()
	{
	}
	static TBaluPhysShape* Clone()
	{
		return new TBaluPolygonShape();
	}
	b2PolygonShape* GetShape(TBaluTransformWithScale class_transform);
	TBaluPhysShape* GetPhysShape();
	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};
static bool TBaluPolygonShape_registered = PhysShapeFactory::Register("PolygonShape", TBaluPolygonShape::Clone);

class TBaluCircleShape : public TBaluPhysShape, public EngineInterface::IBaluCircleShape
{
private:
	b2CircleShape b2shape;
public:
	TBaluCircleShape()
	{
	}
	static TBaluPhysShape* Clone()
	{
		return new TBaluCircleShape();
	}
	TBaluCircleShape(float radius);
	TBaluCircleShape(float radius, TVec2 pos);
	b2CircleShape* GetShape(TBaluTransformWithScale class_transform);
	TBaluPhysShape* GetPhysShape();
	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};
static bool TBaluCircleShape_registered = PhysShapeFactory::Register("CircleShape", TBaluCircleShape::Clone);

class TBaluBoxShape : public TBaluPolygonShape, public EngineInterface::IBaluBoxShape
{
	float width, height;
public:
	TBaluBoxShape()
	{
	}
	static TBaluPhysShape* Clone()
	{
		return new TBaluBoxShape();
	}
	TBaluBoxShape(float width, float height);
	b2PolygonShape* GetShape(TBaluTransformWithScale class_transform);
	TBaluPhysShape* GetPhysShape();
	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};
static bool TBaluBoxShape_registered = PhysShapeFactory::Register("BoxShape", TBaluBoxShape::Clone);