#include "IClass.h"

#include <World/IWorld.h>

#include "ClassEditor\classEditor.h"

TBaluClass::TBaluClass(std::string name, TBaluWorld* world)
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

void TBaluClass::AddOnCollide(IBaluSprite* sprite, IBaluClass* obstancle_class, TScript callback)
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

IBaluClassSpriteInstance* TBaluClass::AddSprite(IBaluSprite* sprite)
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

IAbstractEditor* TBaluClass::CreateEditor(TDrawingHelperContext drawing_context, IBaluWorldInstance* world_instance)
{
	auto result = new TClassEditor(drawing_context, world, this, world_instance);
	return result;
}