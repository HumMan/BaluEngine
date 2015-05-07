#include "Sprite.h"

#include "Class.h"

TBaluSprite::TBaluSprite()
{
	layer = 0;
}

void TBaluSprite::SetPhysShape(TBaluPhysShape* shape)
{
	phys_shape.reset(shape);
}

void TBaluSprite::SetPhysShape(EngineInterface::IBaluPhysShape* shape)
{
	phys_shape.reset(dynamic_cast<TBaluPhysShape*>(shape));
}

TBaluPhysShape* TBaluSprite::GetPhysShape()
{
	return phys_shape.get();
}

void TBaluSprite::SetPhysShapeFromGeometry()
{
	phys_shape = std::make_unique<TBaluPolygonShape>();
}

TBaluSpritePolygon* TBaluSprite::GetPolygone()
{
	return &sprite_polygon;
}

void TBaluSprite::OnCollide(TBaluClass* obstancle_class, CallbackWithData<CollideCallback> callback)
{
	collide_callbacks.push_back(std::make_pair(obstancle_class, callback));
}

CallbackWithData<CollideCallback>* TBaluSprite::GetOnCollide(TBaluClass* obstancle_class)
{
	for (auto& v : collide_callbacks)
		if (v.first == obstancle_class)
			return &v.second;
	return nullptr;
}

void TBaluSprite::AddOnCollide(EngineInterface::IBaluClass* obstancle_class, CallbackWithData<CollideCallback> callback)
{
	OnCollide(dynamic_cast<TBaluClass*>(obstancle_class), callback);
}

CallbackWithData<CollideCallback>* TBaluSprite::GetOnCollide(EngineInterface::IBaluClass* obstancle_class)
{
	return GetOnCollide(dynamic_cast<TBaluClass*>(obstancle_class));
}

void TBaluSprite::RemoveOnCollide(int index)
{
	collide_callbacks.erase(collide_callbacks.begin() + index);
}

std::string TBaluSprite::GetName()
{
	return sprite_name;
}

void TBaluSprite::SetName(std::string name)
{
	sprite_name = name;
}