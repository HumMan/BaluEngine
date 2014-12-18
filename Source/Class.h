#pragma once

#include "Sprite.h"

typedef void(*TMouseMoveCallback)(void* calle, TVec2 old_pos, TVec2 new_pos);

class TBaluClass
{
public:
	class TBaluSpriteInstance
	{
	public:
		TBaluSprite* sprite;
		std::string tag;
		TBaluTransform local;
	};
private:
	std::string class_name;
	std::vector<std::unique_ptr<TBaluSpriteInstance>> sprites;

	void ConstructPhysBody(b2Body& body);
public:
	std::string GetName();
	TBaluClass();
	TBaluClass(TBaluClass&& right);
	virtual ~TBaluClass();
	
	void OnMouseMove(TMouseMoveCallback);
	TBaluSpriteInstance* AddSprite(TBaluSprite* sprite);
	void RemoveSprite(TBaluSprite* sprite);
	void SetPhysBodyType();//static dynamic

	void CreateBone();
	void AttachSpriteToBone();
	void CreateAnimationLine();
	void SetBoneTransform();
	void CreateKeyFrame();
	void SetAnimationTime();
};