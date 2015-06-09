#include "Sprite.h"

#include "Class.h"

#include "World.h"

TBaluSprite::TBaluSprite()
{
	layer = 0;
	world = nullptr;
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

TBaluSpritePolygon* TBaluSprite::GetPolygon()
{
	return &sprite_polygon;
}

std::vector<std::pair<IBaluClass*, CallbackWithData<CollideCallback>>>& TBaluSprite::GetOnCollide()
{
	return on_collide_callbacks;
}

CallbackWithData<CollideCallback>* TBaluSprite::GetOnCollide(TBaluClass* obstancle_class)
{
	for (auto& v : on_collide_callbacks)
		if (v.first == obstancle_class)
			return &v.second;
	return nullptr;
}

void TBaluSprite::AddOnCollide(EngineInterface::IBaluClass* obstancle_class, CallbackWithData<CollideCallback> callback)
{
	on_collide_callbacks.emplace_back(dynamic_cast<TBaluClass*>(obstancle_class), callback);
}

void TBaluSprite::RemoveOnCollide(int index)
{
	on_collide_callbacks.erase(on_collide_callbacks.begin() + index);
}

std::string TBaluSprite::GetName()
{
	return sprite_name;
}

void TBaluSprite::SetName(std::string name)
{
	assert(!world->ObjectNameExists(TWorldObjectType::Sprite, name.c_str()));
	sprite_name = name;
}