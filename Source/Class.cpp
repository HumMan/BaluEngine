#include "Class.h"


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

bool TBaluClass::PointCollide(TVec2 class_space_point)
{
	for (auto& s : sprites)
	{
		TVec2 p = s->local.ToLocal(class_space_point);
		bool is_in_sprite = s->GetSprite()->GetPolygon()->PointCollide(p);
		if (is_in_sprite)
			return true;
	}
	return false;
}

TAABB2 TBaluClass::GetAABB()
{
	if (sprites.size() > 0)
	{
		TAABB2 box(sprites[0]->GetSprite()->GetPolygon()->GetAABB(sprites[0]->local));
		for (int i = 1; i < sprites.size(); i++)
			box += sprites[i]->GetSprite()->GetPolygon()->GetAABB(sprites[i]->local);
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
	class_name = name;
}

TBaluClass::TBaluClass()
{
	skeleton = std::make_unique<TSkeleton>();
	skeleton_animation = std::make_unique<TSkeletonAnimation>(skeleton.get());
}
TBaluClass::TBaluClass(TBaluClass&& right)
	:layer_name(std::move(right.layer_name))
	, class_name(std::move(right.class_name))
	, sprites (std::move(right.sprites))
	, phys_body(std::move(right.phys_body))
	, skeleton(std::move(right.skeleton))
	, skeleton_animation ( std::move(right.skeleton_animation))
	, properties(std::move(right.properties))
{
}
TBaluClass::~TBaluClass()
{

}

void TBaluClass::OnMouseMove(TMouseMoveCallback)
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

TBaluClass::TBaluSpriteInstance* TBaluClass::AddSprite(TBaluSprite* sprite)
{
	sprites.push_back(std::make_unique<TBaluClass::TBaluSpriteInstance>(sprite));
	return sprites.back().get();
}

EngineInterface::IBaluClassSprite* TBaluClass::AddSprite(EngineInterface::IBaluSprite* sprite)
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

TBaluClass::TBaluSpriteInstance* TBaluClass::GetSprite(int index)
{
	return sprites[index].get();
}

void TBaluClass::CreateBone()
{

}
void TBaluClass::AttachSpriteToBone()
{

}
void TBaluClass::CreateAnimationLine()
{

}
void TBaluClass::SetBoneTransform()
{

}
void TBaluClass::CreateKeyFrame()
{

}
void TBaluClass::SetAnimationTime()
{

}

void TBaluClass::OnKeyDown(TKey key, CallbackWithData<KeyUpDownCallback> callback)
{
	on_key_down_callbacks[key].push_back(callback);
}

void TBaluClass::OnKeyUp(TKey key, CallbackWithData<KeyUpDownCallback> callback)
{
	on_key_up_callbacks[key].push_back(callback);
}


void TBaluClass::OnBeforePhysicsStep(CallbackWithData<BeforePhysicsCallback> callback)
{
	before_physics_callbacks.push_back(callback);
}

std::map<TKey, std::vector<CallbackWithData<KeyUpDownCallback>>>& TBaluClass::GetOnKeyDown()
{
	return on_key_down_callbacks;
}

std::map<TKey, std::vector<CallbackWithData<KeyUpDownCallback>>>& TBaluClass::GetOnKeyUp()
{
	return on_key_up_callbacks;
}

std::vector<CallbackWithData<BeforePhysicsCallback>>& TBaluClass::GetOnBeforePhysicsStep()
{
	return before_physics_callbacks;
}