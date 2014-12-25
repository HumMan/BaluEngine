#include "SpriteInstance.h"

TBaluPhysShapeInstance* TBaluSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TBaluSpritePolygonInstance& TBaluSpriteInstance::GetPolygon()
{
	return polygon;
}

TBaluSpriteInstance::TBaluSpriteInstance(TBaluClass::TBaluSpriteInstance* source, TBaluInstance* parent) :polygon(&source->sprite->GetPolygone())
{
	this->parent = parent;
	this->source = source;
	local = source->local;
	phys_shape = std::make_unique<TBaluPhysShapeInstance>(source->sprite->GetPhysShape(), parent);
	
}

TAABB2 TBaluSpriteInstance::GetAABB()
{
	//TAABB2 aabb(TVec2(0, 0), TVec2(width, width / aspect));

	//return TOBB<float, 2>(transform.position, transform.GetOrientation(), aabb).GetAABB();
	//TODO
	return TAABB2();
}

void TBaluSpriteInstance::UpdateTranform(TBaluTransform parent)
{
	global.position = parent.position + local.position;
	global.angle = b2Rot(parent.angle.GetAngle() + local.angle.GetAngle());

	polygon.UpdateTransform(global);
}