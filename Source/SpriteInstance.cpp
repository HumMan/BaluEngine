#include "SpriteInstance.h"

TBaluPhysShapeInstance* TBaluClassInstanceSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TBaluSpritePolygonInstance* TBaluClassInstanceSpriteInstance::GetPolygon()
{
	return &polygon;
}

TBaluClassInstanceSpriteInstance::TBaluClassInstanceSpriteInstance(TBaluClassSpriteInstance* source,TBaluInstance* parent, TResources* resources) :polygon(source->GetSprite()->GetPolygon(), resources)
{
	tag = nullptr;
	this->source = source;
	this->local = source->GetTransformWithScale();
	phys_shape = std::make_unique<TBaluPhysShapeInstance>(source->GetSprite()->GetPhysShape(), parent, this->GetSource());
}

TOBB2 TBaluClassInstanceSpriteInstance::GetOBB()
{
	//source->GetPolygon()->GetAABB(local);
	return TOBB2();
}

void TBaluClassInstanceSpriteInstance::UpdateTranform(TBaluTransformWithScale parent_transform, TBaluTransformWithScale class_transform)
{
	global = parent_transform.ToGlobal(local);

	polygon.UpdateTransform(global, class_transform, local);
}

TBaluClassSpriteInstance* TBaluClassInstanceSpriteInstance::GetSource()
{
	return source;
}