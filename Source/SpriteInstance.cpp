#include "SpriteInstance.h"

TBaluPhysShapeInstance* TBaluSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TBaluSpritePolygonInstance* TBaluSpriteInstance::GetPolygon()
{
	return &polygon;
}

TBaluSpriteInstance::TBaluSpriteInstance(TBaluSprite* source, TBaluTransformWithScale local, TBaluInstance* parent, TResources* resources) :polygon(source->GetPolygon(), resources)
{
	this->source = source;
	this->local = local;
	phys_shape = std::make_unique<TBaluPhysShapeInstance>(source->GetPhysShape(), parent, this);
}

TAABB2 TBaluSpriteInstance::GetAABB()
{
	//TAABB2 aabb(TVec2(0, 0), TVec2(width, width / aspect));

	//return TOBB<float, 2>(transform.position, transform.GetOrientation(), aabb).GetAABB();
	//TODO
	return TAABB2();
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