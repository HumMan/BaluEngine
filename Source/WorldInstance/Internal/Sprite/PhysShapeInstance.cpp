#include "PhysShapeInstance.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;

#include <Box2D.h>

TPhysShapeInstance::TPhysShapeInstance(WorldDef::IPhysShape* source, TPhysShapeUserData _user_data)
	:user_data(_user_data)
{
	this->fixture = nullptr;
	this->body = nullptr;
	this->source = source;
	//source->AddChangesListener(this);
}

TPhysShapeInstance::~TPhysShapeInstance()
{
	//source->RemoveChangesListener(this);
}

void TPhysShapeInstance::BuildFixture(b2Body* body, WorldDef::TTransformWithScale class_transform)
{
	if (this->body != nullptr)
		assert(this->body == body);
	else
		this->body = body;
	if (fixture != nullptr)
	{
		body->DestroyFixture(fixture);
	}
	//TODO
	//b2FixtureDef fixture_def;
	//fixture_def.shape = source->GetShape(class_transform);
	//fixture_def.isSensor = source->IsSensor();
	//if (fixture_def.shape->m_type == b2BodyType::b2_dynamicBody)
	//	fixture_def.density = 1.0;
	//fixture_def.userData = GetUserData();
	//fixture = body->CreateFixture(&fixture_def);
	//delete fixture_def.shape;
}