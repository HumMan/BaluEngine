#include "ClassInstance.h"


TSensorInstance::TSensorInstance(TSensor* source, TBaluInstance* parent)
{
	this->parent = parent;
	this->source = source;
	shape = std::make_unique<TBaluPhysShapeInstance>(source->phys_shape.get(), parent, this);
}
void TSensorInstance::BuildFixture(b2Body* body, TVec2 sprite_scale, TBaluTransform sprite_transform)
{
	shape->BuildFixture(body,sprite_scale, sprite_transform);
}

TBaluClass* TBaluInstance::GetClass()
{
	return instance_class;
}

bool TBaluInstance::PointCollide(TVec2 scene_space_point)
{
	TVec2 p = instance_transform.ToLocal(scene_space_point);
	return instance_class->PointCollide(p);
}

TBaluInstance::TBaluInstance(TBaluClass* source, b2World* phys_world, TBaluTransform transform, TVec2 scale, TResources* resources) 
	:skeleton(source->GetSkeleton(), this, resources), skeleton_animation(&skeleton, source->GetSkeletonAnimation())
{
	instance_transform = transform;
	instance_scale = scale;
	this->instance_class = source;
	this->phys_world = phys_world;

	for (int i = 0; i < source->GetSpritesCount(); i++)
	{
		sprites.push_back(std::make_unique<TBaluSpriteInstance>(source->GetSprite(i)->sprite, source->GetSprite(i)->local, this, resources));
	}

	phys_body = std::make_unique<TBaluClassPhysBodyIntance>(phys_world, source->GetPhysBody(), this);
}

void TBaluInstance::SetTransform(TBaluTransform transform)
{
	this->instance_transform = transform;
	if (phys_body->IsEnable())
	{
		phys_body->SetTransform(transform);
	}
}

TBaluTransform TBaluInstance::GetTransform()
{
	return instance_transform;
}
TVec2 TBaluInstance::GetScale()
{
	return this->instance_scale;
}
void TBaluInstance::SetScale(TVec2 scale)
{
	this->instance_scale = scale;
	if (phys_body->IsEnable())
	{
		
	}
}
TProperties* TBaluInstance::GetProperties()
{
	return &properties;
}

TBaluClassPhysBodyIntance* TBaluInstance::GetPhysBody()
{
	return phys_body.get();
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

TSkeletonAnimationInstance* TBaluInstance::GetSkeletonAnimation()
{
	return &skeleton_animation;
}

void TBaluInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		if (sprites[i]->GetPolygon()->IsEnable())
		{
			//if (sprites[i]->GetAABB().CollideWith(frustum))
			results.push_back(sprites[i]->GetPolygon());
		}
	}
	skeleton.QueryAABB(frustum, results);
}

void TBaluInstance::UpdateTranform()
{
	if (phys_body->IsEnable())
	{
		instance_transform = phys_body->GetTransform();
		for (int i = 0; i < sprites.size(); i++)
		{
			sprites[i]->UpdateTranform(instance_transform);
		}
		skeleton.UpdateTranform(instance_transform);
	}
}

bool TBaluClassPhysBodyIntance::IsEnable()
{
	return is_enable;
}

TBaluClassPhysBodyIntance::TBaluClassPhysBodyIntance(b2World* phys_world, TBaluClassPhysBody* source, TBaluInstance* parent)
{
	is_enable = source->IsEnable();
	if (source->IsEnable())
	{
		this->source = source;
		this->phys_world = phys_world;

		auto body_def = source->GetBodyDef();
		auto instance_transform = parent->GetTransform();
		
		body_def.position = *(b2Vec2*)&instance_transform.position;
		body_def.angle = instance_transform.angle.GetAngle();
		body_def.linearDamping = 0.1;
		//body_def.fixedRotation = false;
		//if (body_def.type == b2BodyType::b2_dynamicBody)
		//	body_def.angularVelocity = 10;

		phys_body = phys_world->CreateBody(&body_def);

		for (int i = 0; i < source->GetSensorsCount(); i++)
		{
			auto sensor_source = source->GetSensor(i);
			sensors.push_back(std::make_unique<TSensorInstance>(sensor_source, parent));
			//sensors.back()->BuildFixture(phys_body, parent->GetScale());
			sensors.back()->BuildFixture(phys_body, TVec2(1,1), TBaluTransform(TVec2(0,0),TRot(0)));
		}

		for (int i = 0; i < parent->GetSpritesCount(); i++)
		{
			auto sensor_source = parent->GetSprite(i);
			//TODO parent->GetScale()
			sensor_source->GetPhysShape()->BuildFixture(phys_body, sensor_source->GetScale(), sensor_source->GetTransform());
		}
	}
}

void TBaluClassPhysBodyIntance::SetFixedRotation(bool fixed)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	phys_body->SetFixedRotation(fixed);
}

TVec2 TBaluClassPhysBodyIntance::GetLinearVelocity()
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	return *(TVec2*)&(phys_body->GetLinearVelocity());
}

void TBaluClassPhysBodyIntance::SetLinearVelocity(TVec2 velocity)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	phys_body->SetLinearVelocity(*(b2Vec2*)&velocity);
}

float TBaluClassPhysBodyIntance::GetAngularVelocity()
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	return phys_body->GetAngularVelocity();
}

void TBaluClassPhysBodyIntance::SetAngularVelocity(float velocity)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Недоступно для данного типа тела");
	phys_body->SetAngularVelocity(velocity);
}

TBaluTransform TBaluClassPhysBodyIntance::GetTransform()
{
	return *(TBaluTransform*)&phys_body->GetTransform();
}

void TBaluClassPhysBodyIntance::SetTransform(TBaluTransform transform)
{
	phys_body->SetTransform(*(b2Vec2*)&transform.position, transform.angle.GetAngle());
}

void TBaluInstance::DoKeyDown(TKey key)
{
	auto it = instance_class->on_key_down_callbacks.find(key);
	if (it != instance_class->on_key_down_callbacks.end())
	{
		for (int i = 0; i < it->second.size();i++)
			it->second[i].Execute(this);
	}
}

void TBaluInstance::DoKeyUp(TKey key)
{
	auto it = instance_class->on_key_up_callbacks.find(key);
	if (it != instance_class->on_key_up_callbacks.end())
	{
		for (int i = 0; i < it->second.size(); i++)
			it->second[i].Execute(this);
	}
}

void TBaluInstance::DoBeforePhysicsStep()
{
	for (const BeforePhysicsCallback& i : instance_class->before_physics_callbacks)
	{
		i(this);
	}
}
//void TBaluInstance::DoSensorCollide(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape)
//{
//	for (const SensorCollideCallback& i : sensor->source->on_sensor_collide_callbacks)
//	{
//		i(this, sensor, obstancle, obstacle_shape);
//	}	
//}

void TBaluInstance::DoBeginContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape)
{
	for (const SensorCollideCallback& i : sensor->source->on_begin_contact)
	{
		i(this, sensor, obstancle, obstacle_shape);
	}	
}

void TBaluInstance::DoEndContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape)
{
	for (const SensorCollideCallback& i : sensor->source->on_end_contact)
	{
		i(this, sensor, obstancle, obstacle_shape);
	}
}