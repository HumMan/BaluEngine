#include "Class.h"

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace BaluLib;

#include <algorithm>

TClass::TClass(std::string name, IWorld* world)
	:TWorldObject(world, name)
{
	skeleton.reset(new TSkeleton());
	this->skeleton_animation.reset(new TSkeletonAnimation(skeleton.get()));
}

TClassPhysBody::TClassPhysBody()
{
	InitAllProperties();
	EnabledValue = false;
}

bool TClass::PointCollide(TVec2 class_space_point)
{
	for (auto& s : sprites)
	{
		bool sprite_collide = s->PointCollide(class_space_point);
		if (sprite_collide)
			return true;
	}
	return false;
}

TAABB2 TClass::GetAABB()
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

void TClass::Initialize()
{
	skeleton = std::unique_ptr<TSkeleton>(new TSkeleton);
	skeleton_animation = std::unique_ptr<TSkeletonAnimation>(new TSkeletonAnimation(skeleton.get()));
}

TClass::~TClass()
{

}

TClassPhysBody* TClass::GetPhysBody()
{
	return &phys_body;
}

TSkeletonAnimation* TClass::GetSkeletonAnimation()
{
	return skeleton_animation.get();
}

TSkeleton* TClass::GetSkeleton()
{
	return skeleton.get();
}

TTransformedSprite* TClass::CreateSpriteInstance(TSprite* sprite)
{
	sprites.push_back(std::unique_ptr<TTransformedSprite>(new TTransformedSprite(sprite)));
	return sprites.back().get();
}

ITransformedSprite* TClass::CreateSpriteInstance(ISprite* sprite)
{
	return CreateSpriteInstance(dynamic_cast<TSprite*>(sprite));
}

void TClass::DestroySpriteInstance(ITransformedSprite* sprite)
{
	auto iter = std::find_if(sprites.begin(), sprites.end(),
		[&](std::unique_ptr<TTransformedSprite>& p) {return p.get() == sprite; });
	if (iter != sprites.end())
	{
		sprites.erase(iter);
	}
	else
	{
		throw std::invalid_argument("Объект не находится в данном классе");
	}
}

int TClass::GetSpritesCount()
{
	return sprites.size();
}

TTransformedSprite* TClass::GetSprite(int index)
{
	return sprites[index].get();
}