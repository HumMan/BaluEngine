#include "ISprite.h"

#include "../Class/IClass.h"

#include <World\IWorld.h>

#include "SpriteEditor\spriteEditor.h"

using namespace EngineInterface;

TBaluSprite::TBaluSprite(const char* name, TBaluWorld* world)
	:TBaluWorldObject(world, name)
{
	this->world = world;
	this->sprite_name = name;
}

IProperties* TBaluSprite::GetProperties()
{
	return &properties;
}

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

IAbstractEditor* TBaluSprite::CreateEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluSceneInstance* editor_scene_instance)
{
	auto result = new TSpriteEditor();
	result->Initialize(drawing_context, world, this, editor_scene_instance);
	return result;
}