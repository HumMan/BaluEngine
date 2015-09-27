#include "Class.h"

#include <World/World.h>

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


std::vector<TSpriteWithClassCollide>& TBaluClass::GetOnCollide()
{
	return on_collide_callbacks;
}

TScript* TBaluClass::GetOnCollide(IBaluSprite* sprite, TBaluClass* obstancle_class)
{
	for (auto& v : on_collide_callbacks)
		if (v.with_class == obstancle_class && v.sprite == sprite)
			return &v.script;
	return nullptr;
}

void TBaluClass::AddOnCollide(IBaluSprite* sprite, EngineInterface::IBaluClass* obstancle_class, TScript callback)
{
	on_collide_callbacks.push_back(TSpriteWithClassCollide(sprite, obstancle_class, callback));
}

void TBaluClass::RemoveOnCollide(int index)
{
	on_collide_callbacks.erase(on_collide_callbacks.begin() + index);
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

std::string TBaluClass::GetName()
{
	return class_name;
}

void TBaluClass::SetName(std::string name)
{
	assert(!world->ObjectNameExists(TWorldObjectType::Class, name.c_str()));
	class_name = name;
}
void TBaluClass::Initialize()
{
	skeleton = std::make_unique<TSkeleton>();
	skeleton_animation = std::make_unique<TSkeletonAnimation>(skeleton.get());
}

TBaluClass::~TBaluClass()
{

}

//void TBaluClass::OnMouseMove(TMouseMoveCallback)
//{
//	
//}

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

TBaluClassSpriteInstance* TBaluClass::AddSprite(TBaluSprite* sprite)
{
	sprites.push_back(std::make_unique<TBaluClassSpriteInstance>(sprite));
	return sprites.back().get();
}

EngineInterface::IBaluClassSpriteInstance* TBaluClass::AddSprite(EngineInterface::IBaluSprite* sprite)
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

TBaluClassSpriteInstance* TBaluClass::GetSprite(int index)
{
	return sprites[index].get();
}

void TBaluClass::OnKeyDown(TKey key, TScript callback)
{
	on_key_down_callbacks[key].push_back(callback);
}

void TBaluClass::OnKeyUp(TKey key, TScript callback)
{
	on_key_up_callbacks[key].push_back(callback);
}


void TBaluClass::OnBeforePhysicsStep(TScript callback)
{
	before_physics_callbacks.push_back(callback);
}

std::map<TKey, std::vector<TScript>>& TBaluClass::GetOnKeyDown()
{
	return on_key_down_callbacks;
}

std::map<TKey, std::vector<TScript>>& TBaluClass::GetOnKeyUp()
{
	return on_key_up_callbacks;
}

std::vector<TScript>& TBaluClass::GetOnBeforePhysicsStep()
{
	return before_physics_callbacks;
}