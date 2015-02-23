#include "SpriteInstance.h"

TBaluPhysShapeInstance* TBaluSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TBaluSpritePolygonInstance* TBaluSpriteInstance::GetPolygon()
{
	return &polygon;
}

TBaluSpriteInstance::TBaluSpriteInstance(TBaluSprite* source, TBaluTransform local, TBaluInstance* parent, TResources* resources) :polygon(source->GetPolygone(), resources)
{
	//this->parent = parent;
	this->source = source;
	this->local = local;
	phys_shape = std::make_unique<TBaluPhysShapeInstance>(source->GetPhysShape(), parent);
}

TAABB2 TBaluSpriteInstance::GetAABB()
{
	//TAABB2 aabb(TVec2(0, 0), TVec2(width, width / aspect));

	//return TOBB<float, 2>(transform.position, transform.GetOrientation(), aabb).GetAABB();
	//TODO
	return TAABB2();
}

void TBaluSpriteInstance::UpdateTranform(TBaluTransform parent_transform)
{

	TMatrix2 global_orient(parent_transform.GetOrientation());
	//global_orient.Transpose();

	global = parent_transform.ToGlobal(local);

	polygon.UpdateTransform(global);
}

TBaluSprite* TBaluSpriteInstance::GetSourceSprite()
{
	return source;
}