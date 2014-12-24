#pragma once

#include "SpritePoly.h"
#include "PhysShape.h"

class TBaluSprite
{
private:
	std::string sprite_name;
	
	TBaluSpritePolygon sprite_polygon;
	std::unique_ptr<TBaluPhysShape> phys_shape;
	
	int layer;

public:
	TBaluSprite();

	std::string GetName();
	void SetName(std::string name);

	void SetPhysShape(TBaluPhysShape* shape);
	void SetPhysShapeFromGeometry();

	TBaluSpritePolygon& GetPolygone();

	void SetFramesGrid(int pixels_in_cell_x, int pixels_in_cell_y);
	void CreateAnimationLine(std::string line_name, int start_cell, int end_cell);
	void CreateFrame(TVec2 tex_coord_pos, TVec2 tex_coord_size);
};