#include "PhysShape.h"

b2PolygonShape* TBaluPolygonShape::GetShape()
{
	return &b2shape;
}

TBaluPhysShape* TBaluPolygonShape::GetPhysShape()
{
	return this;
}

TBaluCircleShape::TBaluCircleShape(float radius)
{
	b2shape.m_radius = radius;
}

TBaluCircleShape::TBaluCircleShape(float radius, TVec2 pos)
{
	b2shape.m_radius = radius;
	b2shape.m_p = *(b2Vec2*)&pos;
}

b2CircleShape* TBaluCircleShape::GetShape()
{
	return &b2shape;
}

TBaluPhysShape* TBaluCircleShape::GetPhysShape()
{
	return this;
}

TBaluBoxShape::TBaluBoxShape(float width, float height)
{
	b2shape.SetAsBox(width / 2, height / 2);
}

b2PolygonShape* TBaluBoxShape::GetShape()
{
	return &b2shape;
}

TBaluPhysShape* TBaluBoxShape::GetPhysShape()
{
	return this;
}