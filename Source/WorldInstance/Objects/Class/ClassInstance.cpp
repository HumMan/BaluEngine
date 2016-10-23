#include "IClassInstance.h"

#include "../Sprite/ISpriteInstance.h"
#include "../Scene/ISceneInstance.h"

using namespace EngineInterface;

TBaluClassInstance* TBaluTransformedClassInstance::GetClass()
{
	return &instance_class;
}

bool TBaluTransformedClassInstance::PointCollide(TVec2 scene_space_point)
{
	TVec2 p = instance_transform.ToLocal(scene_space_point);
	IBaluTransformedSpriteInstance* sprite = nullptr;
	return instance_class.PointCollide(p, sprite);
}

TOBB2 TBaluTransformedClassInstance::GetOBB()
{
	auto aabb = instance_class.GetSource()->GetAABB();
	return instance_transform.ToGlobal(aabb);
}

TBaluClassInstance::TBaluClassInstance(TBaluClass* source, b2World* phys_world, TBaluTransform parent_transform, 
	TResources* resources, TSceneObjectInstance* scene_object)
	:skeleton(source->GetSkeleton(), resources, scene_object)
	, skeleton_animation(&skeleton, source->GetSkeletonAnimation())
{
	this->scene_object = scene_object;
	this->source = source;
	this->resources = resources;

	for (int i = 0; i < source->GetSpritesCount(); i++)
	{
		sprites.push_back(std::unique_ptr<TBaluTransformedSpriteInstance>(new TBaluTransformedSpriteInstance(source->GetSprite(i), resources, scene_object)));
	}

	phys_body = std::unique_ptr<TBaluClassPhysBodyIntance>(new TBaluClassPhysBodyIntance(phys_world, source->GetPhysBody(),this, parent_transform));
}

TSkeletonAnimationInstance* TBaluClassInstance::GetSkeletonAnimation()
{
	return &skeleton_animation;
}
TBaluClassPhysBodyIntance* TBaluClassInstance::GetPhysBody()
{
	return phys_body.get();
}

TBaluClass* TBaluClassInstance::GetSource()
{
	return source;
}
int TBaluClassInstance::GetSpritesCount()
{
	return sprites.size();
}
IBaluTransformedSpriteInstance* TBaluClassInstance::GetSprite(int index)
{
	return sprites[index].get();
}

void TBaluTransformedClassInstance::SourceChanged()
{
	instance_transform = source->GetTransformWithScale();
	if (instance_class.GetPhysBody()->IsEnable())
	{
		instance_class.GetPhysBody()->SetTransform(instance_transform.transform);
	}
}
void TBaluTransformedClassInstance::BeforeDeleteSource()
{

}

TBaluTransformedClassInstance::TBaluTransformedClassInstance(TBaluTransformedClass* source, TBaluSceneInstance* scene)
	:TSceneObjectInstance(scene)
	, instance_class(source->GetClass(), scene->GetPhysWorld(), source->GetTransformWithScale().transform, scene->GetResources(), this)
{
	this->source = source;
	instance_transform = source->GetTransformWithScale();
	source->AddChangesListener(this);
}

TBaluTransformedClassInstance::~TBaluTransformedClassInstance()
{
	source->RemoveChangesListener(this);
}

void TBaluTransformedClassInstance::SetTransform(TBaluTransform transform)
{
	this->instance_transform.transform = transform;
	if (instance_class.GetPhysBody()->IsEnable())
	{
		instance_class.GetPhysBody()->SetTransform(transform);
	}
}

TBaluTransform TBaluTransformedClassInstance::GetTransform()
{
	return instance_transform.transform;
}
TVec2 TBaluTransformedClassInstance::GetScale()
{
	return this->instance_transform.scale;
}
void TBaluTransformedClassInstance::SetScale(TVec2 scale)
{
	this->instance_transform.scale = scale;
	if (instance_class.GetPhysBody()->IsEnable())
	{
		instance_class.GetPhysBody()->BuildAllFixtures();
	}
}
TProperties* TBaluTransformedClassInstance::GetProperties()
{
	return &properties;
}

TBaluClassPhysBodyIntance* TBaluTransformedClassInstance::GetPhysBody()
{
	return instance_class.GetPhysBody();
}

int TBaluTransformedClassInstance::GetSpritesCount()
{
	return instance_class.GetSpritesCount();
}

TSceneObjectInstance* TBaluTransformedClassInstance::Clone(TSceneObject* source, TBaluSceneInstance* scene)
{
	return new TBaluTransformedClassInstance(dynamic_cast<TBaluTransformedClass*>(source), scene);
}

IBaluTransformedSpriteInstance* TBaluTransformedClassInstance::GetSprite(int index)
{
	return instance_class.GetSprite(index);
}

TAABB2 TBaluTransformedClassInstance::GetAABB()
{
	//TODO
	return TAABB2();
}

TSkeletonAnimationInstance* TBaluTransformedClassInstance::GetSkeletonAnimation()
{
	return instance_class.GetSkeletonAnimation();
}

bool TBaluTransformedClassInstance::PointCollide(TVec2 class_space_point, EngineInterface::IBaluTransformedSpriteInstance* &result)
{
	return instance_class.PointCollide(class_space_point, result);
}
bool TBaluClassInstance::PointCollide(TVec2 class_space_point, EngineInterface::IBaluTransformedSpriteInstance* &result)
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

void TBaluTransformedClassInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
{
	instance_class.QueryAABB(frustum, results);
}

void TBaluClassInstance::QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results)
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

void TBaluTransformedClassInstance::UpdateTransform()
{
	if (instance_class.GetPhysBody()->IsEnable())
	{
		instance_transform.transform = instance_class.GetPhysBody()->GetTransform();
	}
	instance_class.UpdateTransform(instance_transform);
}

void TBaluClassInstance::UpdateTransform(TBaluTransformWithScale transform)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->UpdateTransform(transform);
	}
	skeleton.UpdateTranform(transform);
}

bool TBaluClassPhysBodyIntance::IsEnable()
{
	return is_enable;
}

void TBaluClassPhysBodyIntance::BuildAllFixtures()
{
	for (int i = 0; i < sprites->GetSpritesCount(); i++)
	{
		auto sensor_source = sprites->GetSprite(i);

		auto phys_shape = dynamic_cast<TBaluPhysShapeInstance*>(sensor_source->GetPhysShape());
		phys_shape->BuildFixture(phys_body, TBaluTransformWithScale(sensor_source->GetTransform(), sensor_source->GetScale()));
	}
}

TBaluClassPhysBodyIntance::TBaluClassPhysBodyIntance(b2World* phys_world, TBaluClassPhysBody* source, ISpritesArray* sprites, TBaluTransform parent_transform)
{
	is_enable = source->IsEnable();
	if (source->IsEnable())
	{
		this->source = source;
		this->phys_world = phys_world;

		auto body_def = source->GetBodyDef();
		auto instance_transform = parent_transform;
		this->sprites = sprites;
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
