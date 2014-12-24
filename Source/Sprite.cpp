#include "Sprite.h"

TBaluSprite::TBaluSprite()
{
	layer = 0;
}

void TBaluSprite::SetPhysShape(TBaluPhysShape* shape)
{
	phys_shape.reset(shape);
}
void TBaluSprite::SetPhysShapeFromGeometry()
{
	phys_shape = std::make_unique<TBaluPolygonShape>();
}

TBaluSpritePolygon& TBaluSprite::GetPolygone()
{
	return sprite_polygon;
}

void TBaluSprite::SetFramesGrid(int pixels_in_cell_x, int pixels_in_cell_y)
{

}
void TBaluSprite::CreateAnimationLine(std::string line_name, int start_cell, int end_cell)
{

}
void TBaluSprite::CreateFrame(TVec2 tex_coord_pos, TVec2 tex_coord_size)
{

}

std::string TBaluSprite::GetName()
{
	return sprite_name;
}

void TBaluSprite::SetName(std::string name)
{
	sprite_name = name;
}