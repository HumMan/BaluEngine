#include "PhysShapeInstance.h"


TBaluPhysShapeInstance::TBaluPhysShapeInstance(TBaluPhysShape* source)
{
	this->source = source;
}
void TBaluPhysShapeInstance::BuildFixture(b2Body* body)
{
	b2FixtureDef fixture_def;
	fixture_def.shape = source->GetShape();
	fixture = body->CreateFixture(&fixture_def);
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
