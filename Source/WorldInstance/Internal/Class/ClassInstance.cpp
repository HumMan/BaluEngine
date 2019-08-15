#include "ClassInstance.h"

#include "../Sprite/SpriteInstance.h"

#include "../Sprite/PhysShapeInstance.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;
using namespace BaluLib;

#include <Box2D.h>

std::shared_ptr < IClassInstance> TTransformedClassInstance::GetClass()
{
	return instance_class;
}

bool TTransformedClassInstance::PointCollide(TVec2 scene_space_point)
{
	TVec2 p = instance_transform.ToLocal(scene_space_point);
	std::shared_ptr<ITransformedSpriteInstance> sprite;
	return instance_class->PointCollide(p, sprite);
}

TOBB2 TTransformedClassInstance::GetOBB()
{
	auto aabb = instance_class->GetSource()->GetAABB();
	return instance_transform.ToGlobal(aabb);
}

TClassInstance::TClassInstance()
{
	this->source = nullptr;
}

void TClassInstance::Init(WorldDef::IClass* source, b2World* phys_world,
	WorldDef::TTransform parent_transform,
	TResources* resources, std::weak_ptr<ISceneObjectInstance> scene_object, std::weak_ptr< TClassInstance> this_ptr)
{
	skeleton = std::make_shared< TSkeletonInstance>(source->GetSkeleton(), resources, scene_object);
	skeleton_animation = std::make_shared< TSkeletonAnimationInstance>(skeleton, source->GetSkeletonAnimation());

	this->scene_object = scene_object;
	this->source = source;
	//this->resources = resources;

	for (int i = 0; i < source->GetSpritesCount(); i++)
	{
		auto new_sprite = std::make_shared<TTransformedSpriteInstance>();
		new_sprite->Init(source->GetSprite(i), resources, scene_object, new_sprite);
		sprites.push_back(new_sprite);
	}

	phys_body = std::make_shared<TClassPhysBodyIntance>(phys_world, source->GetPhysBody(), this_ptr, parent_transform);
}

std::shared_ptr <ISkeletonAnimationInstance> TClassInstance::GetSkeletonAnimation()
{
	return skeleton_animation;
}
std::shared_ptr < IClassPhysBodyIntance> TClassInstance::GetPhysBody()
{
	return phys_body;
}

WorldDef::IClass* TClassInstance::GetSource()
{
	return source;
}
int TClassInstance::GetSpritesCount()
{
	return sprites.size();
}
int BaluEngine::WorldInstance::Internal::TClassInstance::ContainsSprite(std::shared_ptr < ITransformedSpriteInstance> sprite)
{
	for(int i=0;i<sprites.size();i++)
		if (sprites[i].get() == sprite.get())
			return i;
	return -1;
}
std::shared_ptr < ITransformedSpriteInstance> TClassInstance::GetSprite(int index)
{
	return sprites[index];
}

void TTransformedClassInstance::SourceChanged()
{
	instance_transform = source->GetTransformWithScale();
	auto phys_body = dynamic_cast<TClassPhysBodyIntance*>(instance_class->GetPhysBody().get());
	if (phys_body->IsEnabled())
	{
		phys_body->SetTransform(instance_transform.transform);
	}
}
void TTransformedClassInstance::BeforeDeleteSource()
{

}

TTransformedClassInstance::TTransformedClassInstance(std::shared_ptr < IScene> scene)
:TSceneObjectInstance(scene)
{
	this->source = nullptr;
}

void TTransformedClassInstance::Init(WorldDef::ITransformedClass* source,  std::shared_ptr< TTransformedClassInstance> this_ptr)
{
	 instance_class = std::make_shared<TClassInstance>();
	 instance_class->Init(source->GetClass(),
		 dynamic_cast<TScene*>(this->GetScene().get())->GetPhysWorld(),
		 source->GetTransformWithScale().transform,
		 dynamic_cast<TScene*>(this->GetScene().get())->GetResources(), this_ptr, instance_class);
	this->source = source;
	instance_transform = source->GetTransformWithScale();
	//source->AddChangesListener(this);
}

TTransformedClassInstance::~TTransformedClassInstance()
{
	//source->RemoveChangesListener(this);
}

void TTransformedClassInstance::SetTransform(WorldDef::TTransform transform)
{
	this->instance_transform.transform = transform;
	auto phys_body = dynamic_cast<TClassPhysBodyIntance*>(instance_class->GetPhysBody().get());
	if (phys_body->IsEnabled())
	{
		phys_body->SetTransform(transform);
	}
}

WorldDef::TTransform TTransformedClassInstance::GetTransform()
{
	return instance_transform.transform;
}
TVec2 TTransformedClassInstance::GetScale()
{
	return this->instance_transform.scale;
}
void TTransformedClassInstance::SetScale(TVec2 scale)
{
	this->instance_transform.scale = scale;
	auto phys_body = dynamic_cast<TClassPhysBodyIntance*>(instance_class->GetPhysBody().get());
	if (phys_body->IsEnabled())
	{
		phys_body->BuildAllFixtures();
	}
}
//TProperties* TTransformedClassInstance::GetProperties()
//{
//	return &properties;
//}

std::shared_ptr<IClassPhysBodyIntance> TTransformedClassInstance::GetPhysBody()
{
	return instance_class->GetPhysBody();
}

std::shared_ptr<ISceneObjectInstance> TTransformedClassInstance::Clone(WorldDef::ISceneObject* source, std::shared_ptr < IScene> scene)
{
	auto result = std::make_shared<TTransformedClassInstance>(scene);
	result->Init(dynamic_cast<WorldDef::ITransformedClass*>(source), result);
	return result;
}

std::shared_ptr < ITransformedSpriteInstance> TTransformedClassInstance::GetSprite(int index)
{
	return instance_class->GetSprite(index);
}

TAABB2 TTransformedClassInstance::GetAABB()
{
	//TODO
	return TAABB2();
}

std::shared_ptr < ISkeletonAnimationInstance> TTransformedClassInstance::GetSkeletonAnimation()
{
	return instance_class->GetSkeletonAnimation();
}

bool TTransformedClassInstance::PointCollide(TVec2 class_space_point, std::shared_ptr < ITransformedSpriteInstance> &result)
{
	return instance_class->PointCollide(class_space_point, result);
}
bool TClassInstance::PointCollide(TVec2 class_space_point, std::shared_ptr < ITransformedSpriteInstance> &result)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		bool collide = sprites[i]->GetSource()->PointCollide(class_space_point);
		if (collide)
		{
			result = sprites[i];
			return true;
		}
	}
	return false;
}

void TTransformedClassInstance::QueryAABB(TAABB2 frustum, std::vector< std::shared_ptr<ISpritePolygonInstance>>& results)
{
	instance_class->QueryAABB(frustum, results);
}

void TClassInstance::QueryAABB(TAABB2 frustum, std::vector< std::shared_ptr<ISpritePolygonInstance>>& results)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		if (dynamic_cast<TTransformedSpriteInstance*>(sprites[i].get())->GetPolygon()->IsEnabled())
		{
			//if (sprites[i]->GetAABB().CollideWith(frustum))
			results.push_back(sprites[i]->GetPolygon());
		}
	}
	skeleton->QueryAABB(frustum, results);
}

void TTransformedClassInstance::UpdateTransform()
{
	if (instance_class->GetPhysBody()->IsEnabled())
	{
		instance_transform.transform = instance_class->GetPhysBody()->GetTransform();
	}
	instance_class->UpdateTransform(instance_transform);
}

void TClassInstance::UpdateTransform(WorldDef::TTransformWithScale transform)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		dynamic_cast<TTransformedSpriteInstance*>(sprites[i].get())->UpdateTransform(transform);
	}
	skeleton->UpdateTranform(transform);
}

bool TClassPhysBodyIntance::IsEnabled()
{
	return is_enabled;
}

void TClassPhysBodyIntance::BuildAllFixtures()
{
	for (int i = 0; i < sprites.lock()->GetSpritesCount(); i++)
	{
		auto sensor_source = sprites.lock()->GetSprite(i);

		auto phys_shape = dynamic_cast<TPhysShapeInstance*>(sensor_source->GetPhysShape().get());
		phys_shape->BuildFixture(phys_body, WorldDef::TTransformWithScale(sensor_source->GetTransform(), sensor_source->GetScale()));
	}
}

TClassPhysBodyIntance::TClassPhysBodyIntance(b2World* phys_world, WorldDef::IClassPhysBody* source, std::weak_ptr<ISpritesArray> sprites, WorldDef::TTransform parent_transform)
{
	is_enabled = source->GetEnabled();
	if (source->GetEnabled())
	{
		this->source = source;
		this->phys_world = phys_world;

		b2BodyDef body_def;

		body_def.type = (b2BodyType)source->GetPhysBodyType();
		body_def.fixedRotation = source->GetFixedRotation();

		auto instance_transform = parent_transform;
		this->sprites = sprites;
		body_def.position = *(b2Vec2*)&instance_transform.position;
		body_def.angle = instance_transform.angle.GetAngle();
		body_def.linearDamping = 0.1;
		//TODO остальные параметры в свойства
		//body_def.angularDamping = 0.1;
		//body_def.angularVelocity = 10;

		phys_body = phys_world->CreateBody(&body_def);

		BuildAllFixtures();
	}
}

void TClassPhysBodyIntance::SetFixedRotation(bool fixed)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Ќедоступно дл€ данного типа тела");
	phys_body->SetFixedRotation(fixed);
}

TVec2 TClassPhysBodyIntance::GetLinearVelocity()
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Ќедоступно дл€ данного типа тела");
	return *(TVec2*)&(phys_body->GetLinearVelocity());
}

void TClassPhysBodyIntance::SetLinearVelocity(TVec2 velocity)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Ќедоступно дл€ данного типа тела");
	phys_body->SetLinearVelocity(*(b2Vec2*)&velocity);
}

float TClassPhysBodyIntance::GetAngularVelocity()
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Ќедоступно дл€ данного типа тела");
	return phys_body->GetAngularVelocity();
}

void TClassPhysBodyIntance::SetAngularVelocity(float velocity)
{
	if (phys_body->GetType() == b2BodyType::b2_staticBody)
		throw std::invalid_argument("Ќедоступно дл€ данного типа тела");
	phys_body->SetAngularVelocity(velocity);
}

WorldDef::TTransform TClassPhysBodyIntance::GetTransform()
{
	return *(WorldDef::TTransform*)&phys_body->GetTransform();
}

void TClassPhysBodyIntance::SetTransform(WorldDef::TTransform transform)
{
	phys_body->SetTransform(*(b2Vec2*)&transform.position, transform.angle.GetAngle());
}
