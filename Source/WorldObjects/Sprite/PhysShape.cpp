#include "IPhysShape.h"

using namespace EngineInterface;

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

b2PolygonShape* GetTransformedShape(TBaluTransformWithScale class_transform, TBaluTransformWithScale local, b2PolygonShape& b2shape)
{
	b2PolygonShape* transformed_shape = new b2PolygonShape();
	*(b2Shape*)transformed_shape = b2shape;
	b2Vec2 vertices[b2_maxPolygonVertices];
	for (int i = 0; i < b2shape.m_count; i++)
	{
		auto vertex = *(TVec2*)&b2shape.m_vertices[i];
		vertices[i] = *(b2Vec2*)& class_transform.ToGlobal(local.ToGlobal(vertex));
	}
	transformed_shape->Set(&vertices[0], b2shape.m_count);
	return transformed_shape;
}

b2PolygonShape* TBaluPolygonShape::GetShape(TBaluTransformWithScale class_transform)
{
	return GetTransformedShape(class_transform, local, b2shape);
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
	local.transform.position = pos;
}

b2CircleShape* TBaluCircleShape::GetShape(TBaluTransformWithScale class_transform)
{
	b2CircleShape* transformed_shape = new b2CircleShape();
	*(b2Shape*)transformed_shape = b2shape;

	transformed_shape->m_p = *(b2Vec2*)& class_transform.ToGlobal(local.ToGlobal(TVec2(0,0)));
	transformed_shape->m_radius = b2shape.m_radius*fminf(local.scale[0], local.scale[1])*fminf(class_transform.scale[0], class_transform.scale[1]);
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

b2PolygonShape* TBaluBoxShape::GetShape(TBaluTransformWithScale class_transform)
{
	return GetTransformedShape(class_transform, local, b2shape);
}

TBaluPhysShape* TBaluBoxShape::GetPhysShape()
{
	return this;
}


TBaluPolygonShape* TBaluPhysShapeFactory::CreatePolygonShape()
{
	return new TBaluPolygonShape();
}

TBaluCircleShape* TBaluPhysShapeFactory::CreateCircleShape(float radius)
{
	return new TBaluCircleShape(radius);
}

TBaluCircleShape* TBaluPhysShapeFactory::CreateCircleShape(float radius, TVec2 pos)
{
	return new TBaluCircleShape(radius, pos);
}

TBaluBoxShape* TBaluPhysShapeFactory::CreateBoxShape(float width, float height)
{
	return new TBaluBoxShape(width, height);
}

EngineInterface::IBaluPhysShapeFactory* EngineInterface::GetPhysShapeFactory()
{
	return new TBaluPhysShapeFactory();
}