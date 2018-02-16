#include "ISprite.h"

#include "../Class/IClass.h"

using namespace EngineInterface;

TBaluSprite::TBaluSprite(const char* name, IWorld* world)
	:TWorldObject(world, name)
{
	this->sprite_name = name;
	phys_shape.reset(new TBaluBoxShape(0.1, 0.1));
}

IProperties* TBaluSprite::GetProperties()
{
	return &properties;
}

void TBaluSprite::SetPhysShape(TPhysShape* shape)
{
	phys_shape.reset(shape);
}

void TBaluSprite::SetPhysShape(EngineInterface::IPhysShape* shape)
{
	phys_shape.reset(dynamic_cast<TPhysShape*>(shape));
}

TPhysShape* TBaluSprite::GetPhysShape()
{
	return phys_shape.get();
}

void TBaluSprite::SetPhysShapeFromGeometry()
{
	phys_shape = std::unique_ptr<TBaluPolygonShape>(new TBaluPolygonShape());
}

TSpritePolygon* TBaluSprite::GetPolygon()
{
	return &sprite_polygon;
}