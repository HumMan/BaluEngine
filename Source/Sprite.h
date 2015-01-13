#pragma once

#include "SpritePoly.h"
#include "PhysShape.h"

#include "interfaces.h"

class TBaluSprite :public EngineInterface::IBaluSprite
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
	TBaluPhysShape* GetPhysShape();
	void SetPhysShapeFromGeometry();

	TBaluSpritePolygon& GetPolygone();
};