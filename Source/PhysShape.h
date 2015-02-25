#pragma once

#include "Material.h"

#include <Box2D.h>

class TBaluPhysShape: public EngineInterface::IBaluPhysShape
{
protected:
	TBaluTransform local;
	TVec2 scale;
public:
	virtual ~TBaluPhysShape(){}
	virtual b2Shape* GetShape(TVec2 parent_scale, TBaluTransform sprite_transform) = 0;
	void SetTransform(TBaluTransform local)
	{
		this->local = local;
	}
	void SetScale(TVec2 scale)
	{
		this->scale = scale;
	}
	//virtual TBaluPhysShape* GetPhysShape() = 0;
};

class TBaluPolygonShape : public TBaluPhysShape, public EngineInterface::IBaluPolygonShape
{
private:
	b2PolygonShape b2shape;
public:
	b2PolygonShape* GetShape(TVec2 parent_scale, TBaluTransform sprite_transform);
	TBaluPhysShape* GetPhysShape();
};


class TBaluCircleShape : public TBaluPhysShape, public EngineInterface::IBaluCircleShape
{
private:
	b2CircleShape b2shape;
public:
	TBaluCircleShape(float radius);
	TBaluCircleShape(float radius, TVec2 pos);
	b2CircleShape* GetShape(TVec2 parent_scale, TBaluTransform sprite_transform);
	TBaluPhysShape* GetPhysShape();
};

class TBaluBoxShape : public TBaluPhysShape, public EngineInterface::IBaluBoxShape
{
private:
	b2PolygonShape b2shape;
public:
	TBaluBoxShape(float width, float height);
	b2PolygonShape* GetShape(TVec2 parent_scale, TBaluTransform sprite_transform);
	TBaluPhysShape* GetPhysShape();
};
