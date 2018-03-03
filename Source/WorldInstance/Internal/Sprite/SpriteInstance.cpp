#include "ISpriteInstance.h"

using namespace EngineInterface;

IBaluPhysShapeInstance* TSpriteInstance::GetPhysShape()
{
	return phys_shape.get();
}

TSpritePolygonInstance* TSpriteInstance::GetPolygon()
{
	return &polygon;
}

TSpriteInstance::TSpriteInstance(TSprite* source, TResources* resources, 
	TSceneObjectInstance* scene_object, TBaluTransformedSpriteInstance* parent)
	:polygon(source->GetPolygon(), resources)
{
	this->source = source;
	source->AddChangesListener(this);
	phys_shape = std::unique_ptr<TBaluPhysShapeInstance>(new TBaluPhysShapeInstance(source->GetPhysShape(), TPhysShapeUserData(scene_object, parent)));
}

TSpriteInstance::~TSpriteInstance()
{
	source->RemoveChangesListener(this);
}

TOBB2 TSpriteInstance::GetOBB()
{
	return source->GetPolygon()->GetBoundingBox();
}

void TSpriteInstance::UpdateTransform(TBaluTransformWithScale global)
{
	polygon.UpdateTransform(global);
}

TSprite* TSpriteInstance::GetSource()
{
	return source;
}

IBaluPhysShapeInstance* TBaluTransformedSpriteInstance::GetPhysShape()
{
	return sprite_instance.GetPhysShape();
}

TSpritePolygonInstance* TBaluTransformedSpriteInstance::GetPolygon()
{
	return sprite_instance.GetPolygon();
}

TBaluTransformedSpriteInstance::TBaluTransformedSpriteInstance(TBaluTransformedSprite* source, TResources* resources, TSceneObjectInstance* scene_object)
	:sprite_instance(source->GetSprite(), resources, scene_object, this)
{
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
