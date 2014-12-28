#include "Sprite.h"

TBaluSprite::TBaluSprite()
{
	layer = 0;
}

void TBaluSprite::SetPhysShape(TBaluPhysShape* shape)
{
	phys_shape.reset(shape);
}

TBaluPhysShape* TBaluSprite::GetPhysShape()
{
	return phys_shape.get();
}

void TBaluSprite::SetPhysShapeFromGeometry()
{
	phys_shape = std::make_unique<TBaluPolygonShape>();
}

TBaluSpritePolygon& TBaluSprite::GetPolygone()
{
	return sprite_polygon;
}

std::string TBaluSprite::GetName()
{
	return sprite_name;
}

void TBaluSprite::SetName(std::string name)
{
	sprite_name = name;
}