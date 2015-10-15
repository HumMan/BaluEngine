#include "IPhysShapeInstance.h"

#include "../Class/IClassInstance.h"

using namespace EngineInterface;

TBaluPhysShapeInstance::TBaluPhysShapeInstance(TBaluPhysShape* source, TBaluTransformedClassInstance* parent, TBaluTransformedSpriteInstance* sprite_instance)
{
	this->fixture = nullptr;
	this->body = nullptr;
	this->parent = parent;
	this->source = source;
	this->sprite_instance = sprite_instance;
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
	fixture_def.userData = this;
	fixture = body->CreateFixture(&fixture_def);
	delete fixture_def.shape;
}

IBaluTransformedClassInstance* TBaluPhysShapeInstance::GetParent()
{
	return parent;
}

IBaluTransformedSpriteInstance* TBaluPhysShapeInstance::GetSpriteInstance()
{
	return sprite_instance;
}