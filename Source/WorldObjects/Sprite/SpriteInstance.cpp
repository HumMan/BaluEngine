#include "ISpriteInstance.h"

using namespace EngineInterface;

IBaluPhysShapeInstance* TBaluClassInstanceSpriteInstance::GetPhysShape()
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
	return this->local.ToGlobal(this->source->GetSprite()->GetPolygon()->GetBoundingBox());
}

void TBaluClassInstanceSpriteInstance::UpdateTranform(TBaluTransformWithScale global)
{
	polygon.UpdateTransform(global.ToGlobal(local));
	//polygon.UpdateTransform(global, TBaluTransformWithScale(), TBaluTransformWithScale());
}

TBaluClassSpriteInstance* TBaluClassInstanceSpriteInstance::GetSource()
{
	return source;
}