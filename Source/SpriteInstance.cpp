#include "SpriteInstance.h"

TBaluPhysShapeInstance* TBaluSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TBaluSpritePolygonInstance& TBaluSpriteInstance::GetPolygon()
{
	return polygon;
}

TBaluSpriteInstance::TBaluSpriteInstance(TBaluClass::TBaluSpriteInstance* source)
{
	this->source = source;
	local = source->local;
	phys_shape = std::make_unique<TBaluPhysShapeInstance>(source->sprite->GetPhysShape());
}

TAABB2 TBaluSpriteInstance::GetAABB()
{
	//TAABB2 aabb(TVec2(0, 0), TVec2(width, width / aspect));

	//return TOBB<float, 2>(transform.position, transform.GetOrientation(), aabb).GetAABB();
	//TODO
	return TAABB2();
}
