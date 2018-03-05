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
	throw std::invalid_argument("Тип не зарегистрирован");
}

void PhysShapeFactory::UnregisterAll()
{
	delete phys_shape_registry;
}

TPhysShape* TBaluPolygonShape::GetPhysShape()
{
	return this;
}

TBaluCircleShape::TBaluCircleShape(float radius, TVec2 pos)
{
	InitAllProperties();
	this->RadiusValue = radius;
	this->LocalValue.transform.position = pos;
}

TPhysShape* TBaluCircleShape::GetPhysShape()
{
	return this;
}

TBaluBoxShape::TBaluBoxShape(float width, float height)
{
	InitAllProperties();
	this->WidthValue = width;
	this->HeightValue = height;
}

TPhysShape* TBaluBoxShape::GetPhysShape()
{
	return this;
}


TBaluPolygonShape* TPhysShapeFactory::CreatePolygonShape()
{
	return new TBaluPolygonShape();
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
