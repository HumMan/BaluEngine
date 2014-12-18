#include "Class.h"

void TBaluClass::ConstructPhysBody(b2Body& body)
{

}

std::string TBaluClass::GetName()
{
	return class_name;
}
TBaluClass::TBaluClass()
{
}
TBaluClass::TBaluClass(TBaluClass&& right)
{
	class_name = std::move(right.class_name);
	sprites = std::move(right.sprites);
}
TBaluClass::~TBaluClass()
{

}

void TBaluClass::OnMouseMove(TMouseMoveCallback)
{

}
TBaluClass::TBaluSpriteInstance* TBaluClass::AddSprite(TBaluSprite* sprite)
{
	return nullptr;
}
void TBaluClass::RemoveSprite(TBaluSprite* sprite)
{

}
void TBaluClass::SetPhysBodyType()
{

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