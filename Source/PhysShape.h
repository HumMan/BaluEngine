#pragma once

#include "Material.h"

#include <Box2D.h>

class TBaluPhysShape
{
protected:
	TBaluTransform phys_shape_transform;
public:
	virtual ~TBaluPhysShape(){}
	virtual b2Shape* GetShape()=0;
};

class TBaluPolygonShape : public TBaluPhysShape
{
private:
	b2PolygonShape b2shape;
public:
	b2PolygonShape* GetShape();
};


class TBaluCircleShape : public TBaluPhysShape
{
private:
	b2CircleShape b2shape;
public:
	TBaluCircleShape(float radius);
	TBaluCircleShape(float radius, TVec2 pos);
	b2CircleShape* GetShape();
};

class TBaluBoxShape : public TBaluPhysShape
{
private:
	b2PolygonShape b2shape;
public:
	TBaluBoxShape(float width, float height);
	b2PolygonShape* GetShape();
};
