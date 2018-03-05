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


b2PolygonShape* GetTransformedShape(WorldDef::TTransformWithScale class_transform, WorldDef::TTransformWithScale local, b2PolygonShape& b2shape)
{
	b2PolygonShape* transformed_shape = new b2PolygonShape();
	*(b2Shape*)transformed_shape = b2shape;
	b2Vec2 vertices[b2_maxPolygonVertices];
	for (int i = 0; i < b2shape.m_count; i++)
	{
		auto vertex = *(BaluLib::TVec2*)&b2shape.m_vertices[i];
		auto global_vertex = class_transform.ToGlobal(local.ToGlobal(vertex));
		vertices[i] = *(b2Vec2*)& global_vertex;
	}
	transformed_shape->Set(&vertices[0], b2shape.m_count);
	return transformed_shape;
}

class TShapeBuilder : public WorldDef::IPhysShapeVisitor
{
public:
	b2Shape * result;
	
	WorldDef::TTransformWithScale class_transform;

	void Visit(WorldDef::IPolygonShape* shape)
	{
		auto local = shape->GetLocal();
		b2PolygonShape b2shape;

		result = GetTransformedShape(class_transform, local, b2shape);
	}
	void Visit(WorldDef::ICircleShape* shape)
	{
		auto local = shape->GetLocal();
		b2CircleShape* transformed_shape = new b2CircleShape();
		auto global_p = class_transform.ToGlobal(local.ToGlobal(BaluLib::TVec2(0, 0)));
		transformed_shape->m_p = *(b2Vec2*)& global_p;
		transformed_shape->m_radius = shape->GetRadius()*fminf(local.scale[0], local.scale[1])*fminf(class_transform.scale[0], class_transform.scale[1]);
		result = transformed_shape;
	}
	void Visit(WorldDef::IBoxShape* shape)
	{
		auto local = shape->GetLocal();
		b2PolygonShape b2shape;
		b2shape.SetAsBox(shape->GetWidth() / 2, shape->GetHeight() / 2);
		result = GetTransformedShape(class_transform, local, b2shape);
	}
};


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
	b2FixtureDef fixture_def;
	TShapeBuilder builder;
	builder.class_transform = class_transform;

	source->Accept(&builder);

	fixture_def.shape = builder.result;
	fixture_def.isSensor = source->GetIsSensor();
	if (fixture_def.shape->m_type == b2BodyType::b2_dynamicBody)
		fixture_def.density = 1.0;
	fixture_def.userData = GetUserData();
	fixture = body->CreateFixture(&fixture_def);
	delete fixture_def.shape;
}