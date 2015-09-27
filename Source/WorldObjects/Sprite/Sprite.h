#pragma once

#include "SpritePoly.h"
#include "PhysShape.h"

#include "ISprite.h"
#include "ISpriteInstance.h"

#include <World\Properties.h>



class TBaluClass;

//namespace pugi
//{
//	class xml_node;
//}

namespace EngineInterface
{
	class IBaluPhysShapeInstance;
	class IBaluClass;
	class IBaluClassSpriteInstance;
}

class TBaluSprite :public EngineInterface::IBaluSprite, public EngineInterface::IBaluWorldObject
{
private:
	TBaluWorld* world;
	std::string sprite_name;
	
	TBaluSpritePolygon sprite_polygon;
	std::unique_ptr<TBaluPhysShape> phys_shape;
	
	int layer;
	TProperties properties;

	
public:
	TBaluSprite(const char* name, TBaluWorld* world)
	{
		this->world = world;
		this->sprite_name = name;
	}

	EngineInterface::IProperties* GetProperties()
	{
		return &properties;
	}
	TBaluSprite();

	std::string GetName();
	void SetName(std::string name);

	void SetPhysShape(TBaluPhysShape* shape);
	void SetPhysShape(EngineInterface::IBaluPhysShape* shape);

	TBaluPhysShape* GetPhysShape();
	void SetPhysShapeFromGeometry();

	TBaluSpritePolygon* GetPolygon();

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);

	EngineInterface::IAbstractEditor* CreateEditor(EngineInterface::TDrawingHelperContext drawing_context, EngineInterface::IBaluSceneInstance* editor_scene_instance);
};


class TBaluClassSpriteInstance : public EngineInterface::IBaluClassSpriteInstance
{
	TBaluSprite* sprite;
	TBaluTransformWithScale local;
public:
	TBaluSprite* GetSprite()
	{
		return sprite;
	}
	TBaluClassSpriteInstance()
	{
		sprite = nullptr;
	}
	TBaluClassSpriteInstance(TBaluSprite* sprite)
	{
		this->sprite = sprite;
	}
	void SetTransform(TBaluTransform transform)
	{
		this->local.transform = transform;
	}
	void SetScale(TVec2 scale)
	{
		this->local.scale = scale;
	}
	TBaluTransformWithScale GetTransformWithScale()
	{
		return local;
	}
	TBaluTransform GetTransform()
	{
		return local.transform;
	}
	TVec2 GetScale()
	{
		return local.scale;
	}
	bool PointCollide(TVec2 class_space_point)
	{
		TVec2 p = local.ToLocal(class_space_point);
		bool is_in_sprite = GetSprite()->GetPolygon()->PointCollide(p);
		return (is_in_sprite);
	}
	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};