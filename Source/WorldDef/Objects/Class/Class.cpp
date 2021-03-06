#include "IClass.h"

#include <Common/ICommon.h>

using namespace EngineInterface;

TBaluClass::TBaluClass(std::string name, IBaluWorld* world)
	:TBaluWorldObject(world, name)
{
	skeleton.reset(new TSkeleton());
	this->skeleton_animation.reset(new TSkeletonAnimation(skeleton.get()));
}

TBaluClassPhysBody::TBaluClassPhysBody()
{
	enable = false;
}

void TBaluClassPhysBody::SetFixedRotation(bool fixed)
{
	body_def.fixedRotation = fixed;
}
void TBaluClassPhysBody::SetPhysBodyType(TPhysBodyType type)
{
	switch (type)
	{
	case Static:
		body_def.type = b2BodyType::b2_staticBody;
		break;
	case Dynamic:
		body_def.type = b2BodyType::b2_dynamicBody;
		break;
	case Kinematic:
		body_def.type = b2BodyType::b2_kinematicBody;
		break;
	default:
		assert(false);
		break;
	}
}
void TBaluClassPhysBody::Enable(bool enable)
{
	this->enable = enable;
}

bool TBaluClassPhysBody::IsEnable()
{
	return this->enable;
}

b2BodyDef TBaluClassPhysBody::GetBodyDef()
{
	return body_def;
}

IProperties* TBaluClass::GetProperties()
{
	return &properties;
}


bool TBaluClass::PointCollide(TVec2 class_space_point)
{
	for (auto& s : sprites)
	{
		bool sprite_collide = s->PointCollide(class_space_point);
		if (sprite_collide)
			return true;
	}
	return false;
}

TAABB2 TBaluClass::GetAABB()
{
	if (sprites.size() > 0)
	{
		TAABB2 box(sprites[0]->GetSprite()->GetPolygon()->GetAABB(sprites[0]->GetTransformWithScale()));
		for (int i = 1; i < sprites.size(); i++)
			box += sprites[i]->GetSprite()->GetPolygon()->GetAABB(sprites[i]->GetTransformWithScale());
		return box;
	}
	else
		return TAABB2(TVec2(0), TVec2(0));
}

void TBaluClass::Initialize()
{
	skeleton = std::unique_ptr<TSkeleton>(new TSkeleton);
	skeleton_animation = std::unique_ptr<TSkeletonAnimation>(new TSkeletonAnimation(skeleton.get()));
}

TBaluClass::~TBaluClass()
{

}

TBaluClassPhysBody* TBaluClass::GetPhysBody()
{
	return &phys_body;
}

TSkeletonAnimation* TBaluClass::GetSkeletonAnimation()
{
	return skeleton_animation.get();
}

TSkeleton* TBaluClass::GetSkeleton()
{
	return skeleton.get();
}

TBaluTransformedSprite* TBaluClass::AddSprite(TBaluSprite* sprite)
{
	sprites.push_back(std::unique_ptr<TBaluTransformedSprite>(new TBaluTransformedSprite(sprite)));
	return sprites.back().get();
}

IBaluTransformedSprite* TBaluClass::AddSprite(IBaluSprite* sprite)
{
	return AddSprite(dynamic_cast<TBaluSprite*>(sprite));
}

void TBaluClass::RemoveSprite(TBaluSprite* sprite)
{

}

int TBaluClass::GetSpritesCount()
{
	return sprites.size();
}

TBaluTransformedSprite* TBaluClass::GetSprite(int index)
{
	return sprites[index].get();
}
