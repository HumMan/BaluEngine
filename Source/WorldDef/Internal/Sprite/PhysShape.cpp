#include "PhysShape.h"

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace BaluLib;


typedef  std::vector < std::pair<const char*, PhysShapeClone>> phys_shape_registry_type;
phys_shape_registry_type *phys_shape_registry;

bool PhysShapeFactory::Register(const char* name, PhysShapeClone clone)
{
	if (phys_shape_registry == nullptr)
		phys_shape_registry = new phys_shape_registry_type();
	phys_shape_registry->push_back(std::pair<const char*, PhysShapeClone>(name, clone));
	return true;
}

TPhysShape* PhysShapeFactory::Create(const char* name)
{
	for (int i = 0; i < phys_shape_registry->size(); i++)
		if (strcmp((*phys_shape_registry)[i].first, name) == 0)
			return (*phys_shape_registry)[i].second();
	throw std::invalid_argument("��� �� ���������������");
}

void PhysShapeFactory::UnregisterAll()
{
	delete phys_shape_registry;
}

//b2PolygonShape* GetTransformedShape(TTransformWithScale class_transform, TTransformWithScale local, b2PolygonShape& b2shape)
//{
//	b2PolygonShape* transformed_shape = new b2PolygonShape();
//	*(b2Shape*)transformed_shape = b2shape;
//	b2Vec2 vertices[b2_maxPolygonVertices];
//	for (int i = 0; i < b2shape.m_count; i++)
//	{
//		auto vertex = *(TVec2*)&b2shape.m_vertices[i];
//		auto global_vertex = class_transform.ToGlobal(local.ToGlobal(vertex));
//		vertices[i] = *(b2Vec2*)& global_vertex;
//	}
//	transformed_shape->Set(&vertices[0], b2shape.m_count);
//	return transformed_shape;
//}

//b2PolygonShape* TBaluPolygonShape::GetShape(TTransformWithScale class_transform)
//{
//	return GetTransformedShape(class_transform, local, b2shape);
//}

TPhysShape* TBaluPolygonShape::GetPhysShape()
{
	return this;
}

TBaluCircleShape::TBaluCircleShape(float radius)
{
	//b2shape.m_radius = radius;
}

TBaluCircleShape::TBaluCircleShape(float radius, TVec2 pos)
{
	//b2shape.m_radius = radius;
	//local.transform.position = pos;
}

//b2CircleShape* TBaluCircleShape::GetShape(TTransformWithScale class_transform)
//{
//	b2CircleShape* transformed_shape = new b2CircleShape();
//	*(b2Shape*)transformed_shape = b2shape;
//	auto global_p = class_transform.ToGlobal(local.ToGlobal(TVec2(0,0)));
//	transformed_shape->m_p = *(b2Vec2*)& global_p;
//	transformed_shape->m_radius = b2shape.m_radius*fminf(local.scale[0], local.scale[1])*fminf(class_transform.scale[0], class_transform.scale[1]);
//	return transformed_shape;
//}

TPhysShape* TBaluCircleShape::GetPhysShape()
{
	return this;
}

TBaluBoxShape::TBaluBoxShape(float width, float height)
{
	this->width = width;
	this->height = height;
	//b2shape.SetAsBox(width / 2, height / 2);
}

//b2PolygonShape* TBaluBoxShape::GetShape(TTransformWithScale class_transform)
//{
//	return GetTransformedShape(class_transform, local, b2shape);
//}

TPhysShape* TBaluBoxShape::GetPhysShape()
{
	return this;
}


TBaluPolygonShape* TPhysShapeFactory::CreatePolygonShape()
{
	return new TBaluPolygonShape();
}

TBaluCircleShape* TPhysShapeFactory::CreateCircleShape(float radius)
{
	return new TBaluCircleShape(radius);
}

TBaluCircleShape* TPhysShapeFactory::CreateCircleShape(float radius, TVec2 pos)
{
	return new TBaluCircleShape(radius, pos);
}

TBaluBoxShape* TPhysShapeFactory::CreateBoxShape(float width, float height)
{
	return new TBaluBoxShape(width, height);
}

static TPhysShapeFactory TPhysShapeFactory_local;

IPhysShapeFactory*  BaluEngine::WorldDef::GetPhysShapeFactory()
{
	return &TPhysShapeFactory_local;
}

TPhysShape::TPhysShape()
{
	InitAllProperties();
}
