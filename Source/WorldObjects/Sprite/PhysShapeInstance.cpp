#include "IPhysShapeInstance.h"

using namespace EngineInterface;

TBaluPhysShapeInstance::TBaluPhysShapeInstance(TBaluPhysShape* source, TPhysShapeUserData _user_data)
	:user_data(_user_data)
{
	this->fixture = nullptr;
	this->body = nullptr;
	this->source = source;
}

void TBaluPhysShapeInstance::BuildFixture(b2Body* body, TBaluTransformWithScale class_transform)
{
	if (this->body != nullptr)
		assert(this->body == body);
	else
		this->body = body;
	if (fixture != nullptr)
	{
		body->DestroyFixture(fixture);
	}
	b2FixtureDef fixture_def;
	fixture_def.shape = source->GetShape(class_transform);
	fixture_def.isSensor = source->IsSensor();
	if (fixture_def.shape->m_type == b2BodyType::b2_dynamicBody)
		fixture_def.density = 1.0;
	fixture_def.userData = GetUserData();
	fixture = body->CreateFixture(&fixture_def);
	delete fixture_def.shape;
}