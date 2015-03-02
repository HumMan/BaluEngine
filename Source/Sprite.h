#pragma once

#include "SpritePoly.h"
#include "PhysShape.h"

#include "EngineInterfaces.h"

namespace pugi
{
	class xml_node;
}

class TBaluSprite :public EngineInterface::IBaluSprite, public EngineInterface::IBaluWorldObject
{
private:
	std::string sprite_name;
	
	TBaluSpritePolygon sprite_polygon;
	std::unique_ptr<TBaluPhysShape> phys_shape;
	
	int layer;

public:
	EngineInterface::IProperties* GetProperties()
	{
		return nullptr;
	}
	TBaluSprite();
	//TBaluSprite(const TBaluSprite& sp);

	std::string GetName();
	void SetName(std::string name);

	void SetPhysShape(TBaluPhysShape* shape);
	void SetPhysShape(EngineInterface::IBaluPhysShape* shape);

	TBaluPhysShape* GetPhysShape();
	void SetPhysShapeFromGeometry();

	TBaluSpritePolygon* GetPolygone();

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};