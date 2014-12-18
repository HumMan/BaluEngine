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
	TBaluSprite(){}

	void SetPhysShape(TBaluPhysShape* shape);

	void SetPhysShapeFromGeometry();

	void CreateAnimationLine();
	void CreateFramesAsGrid();
	void CreateFrame(TVec2 tex_coord_pos, TVec2 tex_coord_size);
};