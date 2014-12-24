#include "ClassInstance.h"


TBaluInstance::TBaluInstance(TBaluClass* source, b2World* phys_world) :phys_body(phys_world, &source->GetPhysBody(), this)
{
	this->instance_class = source;
	this->phys_world = phys_world;

	for (int i = 0; i < source->GetSpritesCount(); i++)
	{
		sprites.push_back(std::make_unique<TBaluSpriteInstance>(source->GetSprite(i)));
	}
}

void TBaluInstance::SetTransform(TBaluTransform transform)
{
	this->instance_transform = transform;
}

TBaluClassPhysBodyIntance& TBaluInstance::GetPhysBody()
{
	return phys_body;
}

int TBaluInstance::GetSpritesCount()
{
	return sprites.size();
}
TBaluSpriteInstance* TBaluInstance::GetSprite(int index)
{
	return sprites[index].get();
}

TAABB2 TBaluInstance::GetAABB()
{
	//TODO
	return TAABB2();
}

void TBaluInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		if (sprites[i]->GetAABB().CollideWith(frustum))
			results.push_back(&sprites[i]->GetPolygon());
	}
}

TBaluClassPhysBodyIntance::TBaluClassPhysBodyIntance(b2World* phys_world, TBaluClassPhysBody* source, TBaluInstance* parent)
{
	if (source->IsEnable())
	{
		this->source = source;
		this->phys_world = phys_world;

		auto body_def = source->GetBodyDef();
		phys_body = phys_world->CreateBody(&body_def);

		for (int i = 0; i < source->GetSensorsCount(); i++)
		{
			auto sensor_source = source->GetSensor(i);
			sensors.push_back(std::make_unique<TSensorInstance>(sensor_source));
		}

		for (int i = 0; i < parent->GetSpritesCount(); i++)
		{
			auto sensor_source = parent->GetSprite(i);
			sensor_source->GetPhysShape()->BuildFixture(phys_body);
		}
	}
}

void TBaluClassPhysBodyIntance::SetFixedRotation(bool fixed)
{
	phys_body->SetFixedRotation(fixed);
}

TVec2 TBaluClassPhysBodyIntance::GetLinearVelocity()
{
	return *(TVec2*)&(phys_body->GetLinearVelocity());
}

void TBaluClassPhysBodyIntance::SetLinearVelocity(TVec2 velocity)
{
	phys_body->SetLinearVelocity(*(b2Vec2*)&velocity);
}