#pragma once

#include "SpritePoly.h"
#include "PhysShape.h"

#include "EngineInterfaces\ISprite.h"
#include "EngineInterfaces\ISpriteInstance.h"

#include "Properties.h"



class TBaluClass;

//namespace pugi
//{
//	class xml_node;
//}

namespace EngineInterface
{
	class IBaluPhysShapeInstance;
	class IBaluInstance;
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

	std::vector<std::pair<IBaluClass*, CallbackWithData<CollideCallback>>> on_collide_callbacks;
public:
	TBaluSprite(const char* name, TBaluWorld* world)
	{
		this->world = world;
		this->sprite_name = name;
	}
	void AddOnCollide(IBaluClass* obstancle_class, CallbackWithData<CollideCallback> callback);
	std::vector<std::pair<IBaluClass*, CallbackWithData<CollideCallback>>>& GetOnCollide();
	CallbackWithData<CollideCallback>* TBaluSprite::GetOnCollide(TBaluClass* obstancle_class);
	void RemoveOnCollide(int index);

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