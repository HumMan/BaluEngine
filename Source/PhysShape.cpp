#include "PhysShape.h"


std::vector < std::pair<const char*, PhysShapeClone>> phys_shape_registry;

bool PhysShapeFactory::Register(const char* name, PhysShapeClone clone)
{
	phys_shape_registry.push_back(std::pair<const char*, PhysShapeClone>(name, clone));
	return true;
}

TBaluPhysShape* PhysShapeFactory::Create(const char* name)
{
	for (int i = 0; i < phys_shape_registry.size(); i++)
		if (strcmp(phys_shape_registry[i].first, name) == 0)
			return phys_shape_registry[i].second();
	throw std::invalid_argument("Тип не зарегистрирован");
}

b2PolygonShape* GetTransformedShape(TVec2 class_scale, TBaluTransform class_transform, TVec2 sprite_scale, TBaluTransform sprite_transform, TVec2 scale, TBaluTransform local, b2PolygonShape& b2shape)
{
	b2PolygonShape* transformed_shape = new b2PolygonShape();
	*(b2Shape*)transformed_shape = b2shape;
	b2Vec2 vertices[b2_maxPolygonVertices];
	for (int i = 0; i < b2shape.m_count; i++)
	{
		auto vertex = *(TVec2*)&b2shape.m_vertices[i];
		vertices[i] = *(b2Vec2*)& class_transform.Transform(sprite_transform.Transform(local.Transform(vertex, scale), sprite_scale), class_scale);
	}
	transformed_shape->Set(&vertices[0], b2shape.m_count);
	return transformed_shape;
}

b2PolygonShape* TBaluPolygonShape::GetShape(TVec2 class_scale, TBaluTransform class_transform, TVec2 sprite_scale, TBaluTransform sprite_transform)
{
	return GetTransformedShape(class_scale, class_transform, sprite_scale, sprite_transform, scale, local, b2shape);
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
	local.position = pos;
}

b2CircleShape* TBaluCircleShape::GetShape(TVec2 class_scale, TBaluTransform class_transform, TVec2 sprite_scale, TBaluTransform sprite_transform)
{
	b2CircleShape* transformed_shape = new b2CircleShape();
	*(b2Shape*)transformed_shape = b2shape;

	transformed_shape->m_p = *(b2Vec2*)& class_transform.Transform(sprite_transform.Transform(local.Transform(*(TVec2*)&b2shape.m_p, scale), sprite_scale), class_scale);
	transformed_shape->m_radius = b2shape.m_radius*fminf(scale[0], scale[1])*fminf(sprite_scale[0], sprite_scale[1])*fminf(class_scale[0], class_scale[1]);
	return transformed_shape;
}

TBaluPhysShape* TBaluCircleShape::GetPhysShape()
{
	return this;
}

TBaluBoxShape::TBaluBoxShape(float width, float height)
{
	this->width = width;
	this->height = height;
	b2shape.SetAsBox(width / 2, height / 2);
}

b2PolygonShape* TBaluBoxShape::GetShape(TVec2 class_scale, TBaluTransform class_transform, TVec2 sprite_scale, TBaluTransform sprite_transform)
{
	return GetTransformedShape(class_scale, class_transform, sprite_scale, sprite_transform, scale, local, b2shape);
}

TBaluPhysShape* TBaluBoxShape::GetPhysShape()
{
	return this;
}