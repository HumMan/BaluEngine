#pragma once

#include <list>
#include <vector>
#include "../BaluLib/Source/Math/vec.h"
#include "../BaluLib/Source/Math/matrix.h"

#include "Sprite.h"

class TBone
{
private:
	TBone* parent;
	std::vector<std::unique_ptr<TBone>> children;
	
	TVec2 position;
	float rotation;
public:
	TBone(TBone* parent);
	void SetPosition(TVec2 position);
	void SetRotation(float rotation);
	void AddChild(TBone* bone);
	int GetChildrenCount();
	TBone* GetChild(int index);
};

class TSkin
{
public:
	class TBaluSpriteInstance
	{
	private:
		TBaluSprite* sprite;
		TBaluTransform global;
	public:
		TBaluSpriteInstance(TBaluSprite* sprite);
		void SetTransform(TBaluTransform global);
		TBaluTransform GetTransform();
	};
private:
	std::vector<TBaluSpriteInstance> sprites;
public:
};

class TSkeleton
{
private:
	std::unique_ptr<TBone> root;
	std::vector<TBone*> bones;
	std::vector<std::unique_ptr<TSkin>> skins;
public:
	TSkin* CreateSkin();
	void DestroySkin(TSkin* skin);
	int GetSkinsCount();
	TSkin* GetSkin(int index);
	TBone* CreateBone(TBone* parent);
	void DestroyBone(TBone* bone);
	TSkin::TBaluSpriteInstance AttachSpriteToBone(TBone* bone, TBaluSprite* sprite, TSkin* skin);
};