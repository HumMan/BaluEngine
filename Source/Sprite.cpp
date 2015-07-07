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

std::string TBaluSprite::GetName()
{
	return sprite_name;
}

void TBaluSprite::SetName(std::string name)
{
	assert(!world->ObjectNameExists(TWorldObjectType::Sprite, name.c_str()));
	sprite_name = name;
}