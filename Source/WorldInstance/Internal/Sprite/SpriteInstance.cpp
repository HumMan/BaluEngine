#include "SpriteInstance.h"

#include "PhysShapeInstance.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;
using namespace BaluLib;

IPhysShapeInstance* TSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TSpritePolygonInstance* TSpriteInstance::GetPolygon()
{
	return &polygon;
}

TSpriteInstance::TSpriteInstance(WorldDef::ISprite* source, TResources* resources, 
	ISceneObjectInstance* scene_object, ITransformedSpriteInstance* parent)
	:polygon(source->GetPolygon(), resources)
{
	this->source = source;
	//source->AddChangesListener(this);
	phys_shape = std::unique_ptr<IPhysShapeInstance>(new TPhysShapeInstance(source->GetPhysShape(), TPhysShapeUserData(scene_object, parent)));
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
	polygon.UpdateTransform(global);
}

WorldDef::ISprite* TSpriteInstance::GetSource()
{
	return source;
}

IPhysShapeInstance* TTransformedSpriteInstance::GetPhysShape()
{
	return sprite_instance.GetPhysShape();
}

TSpritePolygonInstance* TTransformedSpriteInstance::GetPolygon()
{
	return sprite_instance.GetPolygon();
}

TTransformedSpriteInstance::TTransformedSpriteInstance(WorldDef::ITransformedSprite* source, TResources* resources, ISceneObjectInstance* scene_object)
	:sprite_instance(source->GetSprite(), resources, scene_object, this)
{
	this->source = source;
	this->transform = source->GetTransformWithScale();
}

TOBB2 TTransformedSpriteInstance::GetOBB()
{
	return this->transform.ToGlobal(this->source->GetSprite()->GetPolygon()->GetBoundingBox());
}

void TTransformedSpriteInstance::UpdateTransform(WorldDef::TTransformWithScale global)
{
	sprite_instance.UpdateTransform(global.ToGlobal(transform));
	//polygon.UpdateTransform(global, TBaluTransformWithScale(), TBaluTransformWithScale());
}

WorldDef::ITransformedSprite* TTransformedSpriteInstance::GetSource()
{
	return source;
}
