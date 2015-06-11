#include "ClassInstance.h"

#include "WorldInstance.h"

TBaluClassInstance* TBaluInstance::GetClass()
{
	return instance_class;
}

bool TBaluInstance::PointCollide(TVec2 scene_space_point)
{
	TVec2 p = instance_transform.ToLocal(scene_space_point);
	return instance_class->GetClass()->PointCollide(p);
}

TOBB2 TBaluInstance::GetOBB()
{
	auto aabb = GetClass()->GetClass()->GetAABB();
	//aabb.border[0] *= instance_scale;
	//aabb.border[1] *= instance_scale;
	return instance_transform.ToGlobal(aabb);
	//return TOBB2(instance_transform.position, instance_transform.GetOrientation(), aabb);
}

TBaluInstance::TBaluInstance(TBaluClassInstance* source, b2World* phys_world, TBaluTransform transform, TVec2 scale, TResources* resources)
	:skeleton(source->GetClass()->GetSkeleton(), this, resources), skeleton_animation(&skeleton, source->GetClass()->GetSkeletonAnimation())
{
	this->resources = resources;
	skeleton_animation.Init();
	instance_transform = TBaluTransformWithScale(transform, scale);
	this->instance_class = source;
	this->phys_world = phys_world;

	for (int i = 0; i < source->GetClass()->GetSpritesCount(); i++)
	{
		sprites.push_back(std::make_unique<TBaluClassInstanceSpriteInstance>(source->GetClass()->GetSprite(i), this, resources));
	}

	phys_body = std::make_unique<TBaluClassPhysBodyIntance>(phys_world, source->GetClass()->GetPhysBody(), this);
}

void TBaluInstance::SetTransform(TBaluTransform transform)
{
	this->instance_transform.transform = transform;
	if (phys_body->IsEnable())
	{
		phys_body->SetTransform(transform);
	}
}

TBaluTransform TBaluInstance::GetTransform()
{
	return instance_transform.transform;
}
TVec2 TBaluInstance::GetScale()
{
	return this->instance_transform.scale;
}
void TBaluInstance::SetScale(TVec2 scale)
{
	this->instance_transform.scale = scale;
	if (phys_body->IsEnable())
	{
		phys_body->BuildAllFixtures();
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
TBaluClassInstanceSpriteInstance* TBaluInstance::GetSprite(int index)
{
	return sprites[index].get();
}

TBaluClassInstanceSpriteInstance* TBaluInstance::AddSprite(IBaluClassSpriteInstance* _source)
{
	TBaluClassSpriteInstance* source = dynamic_cast<TBaluClassSpriteInstance*>(_source);
	sprites.push_back(std::make_unique<TBaluClassInstanceSpriteInstance>(source, this, resources));
	return sprites.back().get();
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

bool TBaluInstance::PointCollide(TVec2 class_space_point, EngineInterface::IBaluClassInstanceSpriteInstance* &result)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		bool collide = sprites[i]->GetSource()->PointCollide(class_space_point);
		if (collide)
		{
			result = sprites[i].get();
			return true;
		}
	}
	return false;
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
		instance_transform.transform = phys_body->GetTransform();
	}
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->UpdateTranform(TBaluTransformWithScale(), instance_transform);
	}
	skeleton.UpdateTranform(instance_transform);
}

bool TBaluClassPhysBodyIntance::IsEnable()
{
	return is_enable;
}

void TBaluClassPhysBodyIntance::BuildAllFixtures()
{
	for (int i = 0; i < parent->GetSpritesCount(); i++)
	{
		auto sensor_source = parent->GetSprite(i);
		//TODO parent->GetScale()
		sensor_source->GetPhysShape()->BuildFixture(phys_body, TBaluTransformWithScale(parent->GetTransform(), parent->GetScale()), TBaluTransformWithScale( sensor_source->GetTransform(), sensor_source->GetScale()));
	}
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
		this->parent = parent;
		body_def.position = *(b2Vec2*)&instance_transform.position;
		body_def.angle = instance_transform.angle.GetAngle();
		body_def.linearDamping = 0.1;
		//body_def.angularDamping = 0.1;
		//body_def.fixedRotation = false;
		//if (body_def.type == b2BodyType::b2_dynamicBody)
		//	body_def.angularVelocity = 10;

		phys_body = phys_world->CreateBody(&body_def);

		BuildAllFixtures();
	}
}

void TBaluClassPhysBodyIntance::SetFixedRotation(bool fixed)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("���������� ��� ������� ���� ����");
	phys_body->SetFixedRotation(fixed);
}

TVec2 TBaluClassPhysBodyIntance::GetLinearVelocity()
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("���������� ��� ������� ���� ����");
	return *(TVec2*)&(phys_body->GetLinearVelocity());
}

void TBaluClassPhysBodyIntance::SetLinearVelocity(TVec2 velocity)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("���������� ��� ������� ���� ����");
	phys_body->SetLinearVelocity(*(b2Vec2*)&velocity);
}

float TBaluClassPhysBodyIntance::GetAngularVelocity()
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("���������� ��� ������� ���� ����");
	return phys_body->GetAngularVelocity();
}

void TBaluClassPhysBodyIntance::SetAngularVelocity(float velocity)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("���������� ��� ������� ���� ����");
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

void TBaluClassInstance::DoKeyDown(TKey key, TBaluInstance* instance)
{
	auto it = on_key_down_callbacks.find(key);
	if (it != on_key_down_callbacks.end())
	{
		for (int i = 0; i < it->second.size(); i++)
		{
			it->second[i].Execute(instance);
		}
	}
}

void TBaluClassInstance::DoKeyUp(TKey key, TBaluInstance* instance)
{
	auto it = on_key_up_callbacks.find(key);
	if (it != on_key_up_callbacks.end())
	{
		for (int i = 0; i < it->second.size(); i++)
			it->second[i].Execute(instance);
	}
}

void TBaluClassInstance::DoBeforePhysicsStep(TBaluInstance* instance)
{
	for (auto& i : before_physics_callbacks)
	{
		i.Execute(instance);
	}
}