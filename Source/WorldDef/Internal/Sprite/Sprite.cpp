#include "Sprite.h"

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

TSprite::TSprite(const char* name, IWorld* world)
	:TWorldObject(world, name)
{
	InitAllProperties();
	phys_shape.reset(new TBaluBoxShape(0.1, 0.1));
}

void TSprite::SetPhysShape(IPhysShape* shape)
{
	phys_shape.reset(dynamic_cast<TPhysShape*>(shape));
}

TPhysShape* TSprite::GetPhysShape()
{
	return phys_shape.get();
}

void TSprite::SetPhysShapeFromGeometry()
{
	phys_shape = std::unique_ptr<TBaluPolygonShape>(new TBaluPolygonShape());
}

TSpritePolygon* TSprite::GetPolygon()
{
	return &sprite_polygon;
}