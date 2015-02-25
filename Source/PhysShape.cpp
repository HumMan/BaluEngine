#include "PhysShape.h"

b2PolygonShape* TBaluPolygonShape::GetShape(TVec2 sprite_scale, TBaluTransform sprite_transform)
{
	b2PolygonShape* transformed_shape = new b2PolygonShape();
	b2Vec2 vertices[b2_maxPolygonVertices];
	for (int i = 0; i < b2shape.m_count; i++)
	{
		vertices[i] = *(b2Vec2*)&sprite_transform.ToGlobal(local.ToGlobal((*(TVec2*)&b2shape.m_vertices[i]).ComponentMul(scale)).ComponentMul(sprite_scale));
	}
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

b2CircleShape* TBaluCircleShape::GetShape(TVec2 sprite_scale, TBaluTransform sprite_transform)
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

b2PolygonShape* TBaluBoxShape::GetShape(TVec2 sprite_scale, TBaluTransform sprite_transform)
{
	return &b2shape;
}

TBaluPhysShape* TBaluBoxShape::GetPhysShape()
{
	return this;
}