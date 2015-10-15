#include "ISpriteInstance.h"

using namespace EngineInterface;

IBaluPhysShapeInstance* TBaluTransformedSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TBaluSpritePolygonInstance* TBaluTransformedSpriteInstance::GetPolygon()
{
	return &polygon;
}

TBaluTransformedSpriteInstance::TBaluTransformedSpriteInstance(TBaluTransformedSprite* source, TResources* resources)
	:polygon(source->GetSprite()->GetPolygon(), resources)
{
	tag = nullptr;
	this->source = source;
	this->local = source->GetTransformWithScale();
	phys_shape = std::make_unique<TBaluPhysShapeInstance>(source->GetSprite()->GetPhysShape());
}

TOBB2 TBaluTransformedSpriteInstance::GetOBB()
{
	return this->local.ToGlobal(this->source->GetSprite()->GetPolygon()->GetBoundingBox());
}

void TBaluTransformedSpriteInstance::UpdateTranform(TBaluTransformWithScale global)
{
	polygon.UpdateTransform(global.ToGlobal(local));
	//polygon.UpdateTransform(global, TBaluTransformWithScale(), TBaluTransformWithScale());
}

TBaluTransformedSprite* TBaluTransformedSpriteInstance::GetSource()
{
	return source;
}