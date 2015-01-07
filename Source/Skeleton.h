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
	
	TBaluTransform local;
public:
	TBone(TBone* parent);
	
	void SetTransform(TBaluTransform);
	TBaluTransform GetTransform();

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
		TBaluTransform transform;
	public:
		TBaluSpriteInstance(TBaluSprite* sprite);
		void SetTransform(TBaluTransform global);
		TBaluTransform GetTransform();
		TBaluSprite* GetSprite();
	};
private:
	std::vector<std::vector<TBaluSpriteInstance>> sprites_of_bones;
public:
	TSkin(int bones_count);
	void SetBoneSprite(int bone_index, TBaluSprite* sprite, TBaluTransform global);
	int GetBonesCount();
	std::vector<TBaluSpriteInstance>& GetSpritesOfBone(int bone_index);
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
	int GetBoneIndex(TBone* bone);
	TBone* GetRoot();
	std::vector<TBone*> GetAllBones();
};