#include "SpriteInstance.h"

TBaluPhysShapeInstance* TBaluSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TBaluSpritePolygonInstance* TBaluSpriteInstance::GetPolygon()
{
	return &polygon;
}

TBaluSpriteInstance::TBaluSpriteInstance(TBaluSprite* source, TBaluClass::TBaluSpriteInstance* sprite_source, TBaluTransformWithScale local, TBaluInstance* parent, TResources* resources) :polygon(source->GetPolygon(), resources)
{
	this->sprite_source = sprite_source;
	this->source = source;
	this->local = local;
	phys_shape = std::make_unique<TBaluPhysShapeInstance>(source->GetPhysShape(), parent, this);
}

TOBB2 TBaluSpriteInstance::GetOBB()
{
	//source->GetPolygon()->GetAABB(local);
	return TOBB2();
}

void TBaluSpriteInstance::UpdateTranform(TBaluTransformWithScale parent_transform, TBaluTransformWithScale class_transform)
{
	global = parent_transform.ToGlobal(local);

	polygon.UpdateTransform(global, class_transform, local);
}

TBaluSprite* TBaluSpriteInstance::GetSourceSprite()
{
	return source;
}