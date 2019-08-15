#include "SpriteInstance.h"

#include "PhysShapeInstance.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;
using namespace BaluLib;

std::shared_ptr < IPhysShapeInstance> TSpriteInstance::GetPhysShape()
{
	return phys_shape;
}

std::shared_ptr < TSpritePolygonInstance> TSpriteInstance::GetPolygon()
{
	return polygon;
}

TSpriteInstance::TSpriteInstance(WorldDef::ISprite* source, TResources* resources, 
	std::weak_ptr < ISceneObjectInstance> scene_object, std::weak_ptr < ITransformedSpriteInstance> parent)
	:polygon(std::make_shared<TSpritePolygonInstance>(source->GetPolygon(), resources))
{
	this->source = source;
	//source->AddChangesListener(this);
	phys_shape = std::make_shared<TPhysShapeInstance>(source->GetPhysShape(), TPhysShapeUserData(scene_object, parent));
}

TSpriteInstance::~TSpriteInstance()
{
	//source->RemoveChangesListener(this);
}

TOBB2 TSpriteInstance::GetOBB()
{
	return source->GetPolygon()->GetBoundingBox();
}

void TSpriteInstance::UpdateTransform(WorldDef::TTransformWithScale global)
{
	polygon->UpdateTransform(global);
}

WorldDef::ISprite* TSpriteInstance::GetSource()
{
	return source;
}

std::shared_ptr < IPhysShapeInstance> TTransformedSpriteInstance::GetPhysShape()
{
	return sprite_instance->GetPhysShape();
}

std::shared_ptr < ISpritePolygonInstance> TTransformedSpriteInstance::GetPolygon()
{
	return sprite_instance->GetPolygon();
}

TTransformedSpriteInstance::TTransformedSpriteInstance()
{
	this->source = nullptr;
}

void TTransformedSpriteInstance::Init(WorldDef::ITransformedSprite* source, TResources* resources,
	std::weak_ptr < ISceneObjectInstance> scene_object, std::weak_ptr<ITransformedSpriteInstance> this_ptr)
{
	this->sprite_instance = std::make_shared<TSpriteInstance>(source->GetSprite(), resources, scene_object, this_ptr);
	this->source = source;
	this->transform = source->GetTransformWithScale();
}

TOBB2 TTransformedSpriteInstance::GetOBB()
{
	return this->transform.ToGlobal(this->source->GetSprite()->GetPolygon()->GetBoundingBox());
}

void TTransformedSpriteInstance::UpdateTransform(WorldDef::TTransformWithScale global)
{
	sprite_instance->UpdateTransform(global.ToGlobal(transform));
	//polygon.UpdateTransform(global, TBaluTransformWithScale(), TBaluTransformWithScale());
}

WorldDef::ITransformedSprite* TTransformedSpriteInstance::GetSource()
{
	return source;
}
