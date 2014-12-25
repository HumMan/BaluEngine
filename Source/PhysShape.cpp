#include "PhysShape.h"

b2PolygonShape* TBaluPolygonShape::GetShape()
{
	return &b2shape;
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

TBaluBoxShape::TBaluBoxShape(float width, float height)
{
	b2shape.SetAsBox(height/2, width/2);
}

b2PolygonShape* TBaluBoxShape::GetShape()
{
	return &b2shape;
}
