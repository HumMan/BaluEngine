#include "PhysShapeInstance.h"


TBaluPhysShapeInstance::TBaluPhysShapeInstance(TBaluPhysShape* source, TBaluInstance* parent, TSensorInstance* sensor)
{
	this->parent = parent;
	this->source = source;
	this->sensor = sensor;
	this->is_sensor = sensor!=nullptr;
}

void TBaluPhysShapeInstance::BuildFixture(b2Body* body, TVec2 sprite_scale, TBaluTransform sprite_transform)
{
	this->body = body;

	b2FixtureDef fixture_def;
	fixture_def.shape = source->GetShape(sprite_scale, sprite_transform);
	fixture_def.isSensor = is_sensor;
	if (fixture_def.shape->m_type == b2BodyType::b2_dynamicBody)
		fixture_def.density = 1.0;
	fixture_def.userData = this;
	fixture = body->CreateFixture(&fixture_def);
}

TBaluInstance* TBaluPhysShapeInstance::GetParent()
{
	return parent;
}

TSensorInstance* TBaluPhysShapeInstance::GetParentSensor()
{
	assert(is_sensor);
	return sensor;
}

//
//TBaluCircleShapeInstance::TBaluCircleShapeInstance(TBaluCircleShape* source)
//{
//	this->source = source;
//}
//void TBaluCircleShapeInstance::BuildFixture(b2Body &body)
//{
//	b2FixtureDef fixture_def;
//	auto shape = source->GetShape();
//	fixture_def.shape = &shape;
//	fixture = body.CreateFixture(&fixture_def);
//}
//
//TBaluBoxShapeInstance::TBaluBoxShapeInstance(TBaluBoxShape* source)
//{
//	this->source = source;
//}
//
//void TBaluBoxShapeInstance::BuildFixture(b2Body &body)
//{
//	b2FixtureDef fixture_def;
//	auto shape = source->GetShape();
//	fixture_def.shape = &shape;
//	fixture = body.CreateFixture(&fixture_def);
//}
