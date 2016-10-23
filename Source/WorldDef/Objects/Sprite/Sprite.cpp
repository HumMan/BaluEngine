#include "ISprite.h"

#include "../Class/IClass.h"

using namespace EngineInterface;

TBaluSprite::TBaluSprite(const char* name, IBaluWorld* world)
	:TBaluWorldObject(world, name)
{
	this->sprite_name = name;
	phys_shape.reset(new TBaluBoxShape(0.1, 0.1));
}

IProperties* TBaluSprite::GetProperties()
{
	return &properties;
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
	phys_shape = std::unique_ptr<TBaluPolygonShape>(new TBaluPolygonShape());
}

TBaluSpritePolygon* TBaluSprite::GetPolygon()
{
	return &sprite_polygon;
}

//IAbstractEditor* TBaluSprite::CreateEditor(TDrawingHelperContext drawing_context, IBaluWorldInstance* world_instance)
//{
//	auto result = new TSpriteEditor(drawing_context, world, this, world_instance);
//	return result;
//}

