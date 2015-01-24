#pragma once

#include "Material.h"

#include <Box2D.h>

class TBaluPhysShape: public EngineInterface::IBaluPhysShape
{
protected:
	TBaluTransform phys_shape_transform;
public:
	virtual ~TBaluPhysShape(){}
	virtual b2Shape* GetShape()=0;
	//virtual TBaluPhysShape* GetPhysShape() = 0;
};

class TBaluPolygonShape : public TBaluPhysShape, public EngineInterface::IBaluPolygonShape
{
private:
	b2PolygonShape b2shape;
public:
	b2PolygonShape* GetShape();
	TBaluPhysShape* GetPhysShape();
};


class TBaluCircleShape : public TBaluPhysShape, public EngineInterface::IBaluCircleShape
{
private:
	b2CircleShape b2shape;
public:
	TBaluCircleShape(float radius);
	TBaluCircleShape(float radius, TVec2 pos);
	b2CircleShape* GetShape();
	TBaluPhysShape* GetPhysShape();
};

class TBaluBoxShape : public TBaluPhysShape, public EngineInterface::IBaluBoxShape
{
private:
	b2PolygonShape b2shape;
public:
	TBaluBoxShape(float width, float height);
	b2PolygonShape* GetShape();
	TBaluPhysShape* GetPhysShape();
};
