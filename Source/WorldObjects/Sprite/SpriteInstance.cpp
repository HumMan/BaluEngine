#include "ISpriteInstance.h"

using namespace EngineInterface;

IBaluPhysShapeInstance* TBaluSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TBaluSpritePolygonInstance* TBaluSpriteInstance::GetPolygon()
{
	return &polygon;
}

TBaluSpriteInstance::TBaluSpriteInstance(TBaluSprite* source, TResources* resources, 
	TSceneObjectInstance* scene_object, TBaluTransformedSpriteInstance* parent)
	:polygon(source->GetPolygon(), resources)
{
	this->source = source;
	phys_shape = std::make_unique<TBaluPhysShapeInstance>(source->GetPhysShape(), TPhysShapeUserData(scene_object, parent));
}

TOBB2 TBaluSpriteInstance::GetOBB()
{
	return source->GetPolygon()->GetBoundingBox();
}

void TBaluSpriteInstance::UpdateTransform(TBaluTransformWithScale global)
{
	polygon.UpdateTransform(global);
}

TBaluSprite* TBaluSpriteInstance::GetSource()
{
	return source;
}

IBaluPhysShapeInstance* TBaluTransformedSpriteInstance::GetPhysShape()
{
	return sprite_instance.GetPhysShape();
}

TBaluSpritePolygonInstance* TBaluTransformedSpriteInstance::GetPolygon()
{
	return sprite_instance.GetPolygon();
}

TBaluTransformedSpriteInstance::TBaluTransformedSpriteInstance(TBaluTransformedSprite* source, TResources* resources, TSceneObjectInstance* scene_object)
	:sprite_instance(source->GetSprite(), resources, scene_object, this)
{
	tag = nullptr;
	this->source = source;
	this->transform = source->GetTransformWithScale();
}

TOBB2 TBaluTransformedSpriteInstance::GetOBB()
{
	return this->transform.ToGlobal(this->source->GetSprite()->GetPolygon()->GetBoundingBox());
}

void TBaluTransformedSpriteInstance::UpdateTransform(TBaluTransformWithScale global)
{
	sprite_instance.UpdateTransform(global.ToGlobal(transform));
	//polygon.UpdateTransform(global, TBaluTransformWithScale(), TBaluTransformWithScale());
}

TBaluTransformedSprite* TBaluTransformedSpriteInstance::GetSource()
{
	return source;
}