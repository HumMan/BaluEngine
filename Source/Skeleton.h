#pragma once

#include <list>
#include <vector>
#include "../../BaluLib/Source/Math/vec.h"
#include "../../BaluLib/Source/Math/matrix.h"

#include "Sprite.h"

#include "EngineInterfaces\IClass.h"

class TSkeleton;

class TBone : public EngineInterface::IBone
{
private:
	TBone* parent;
	std::vector<TBone*> children;
	
	TBaluTransform local;
public:
	TBone()
	{
	}
	TBone(TBone* parent);
	
	void SetTransform(TBaluTransform);
	TBaluTransform GetTransform();

	void AddChild(TBone* bone);
	int GetChildrenCount();
	TBone* GetChild(int index);

	void Save(pugi::xml_node& parent_node, const int version, TSkeleton* skeleton);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TSkeleton* skeleton);
};

class TSkin: public EngineInterface::ISkin
{
public:
	class TBaluSpriteInstance
	{
	private:
		TBaluSprite* sprite;
		TBaluTransform transform;
	public:
		TBaluSpriteInstance()
		{
			sprite = nullptr;
		}
		TBaluSpriteInstance(TBaluSprite* sprite);
		void SetTransform(TBaluTransform global);
		TBaluTransform GetTransform();
		TBaluSprite* GetSprite();

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
private:
	std::vector<std::vector<TBaluSpriteInstance>> sprites_of_bones;
public:
	TSkin()
	{
	}
	TSkin(int bones_count);
	void SetBoneSprite(int bone_index, TBaluSprite* sprite, TBaluTransform global);
	void SetBoneSprite(int bone_index, EngineInterface::IBaluSprite* sprite, TBaluTransform global);
	int GetBonesCount();
	std::vector<TBaluSpriteInstance>& GetSpritesOfBone(int bone_index);

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};

class TSkeleton: public EngineInterface::ISkeleton
{
private:
	int root;
	std::vector<std::unique_ptr<TBone>> bones;
	std::vector<std::unique_ptr<TSkin>> skins;
public:
	TSkeleton()
	{
		root = -1;
	}
	//TSkeleton(TSkeleton&& right);
	TSkin* CreateSkin();
	void DestroySkin(TSkin* skin);
	void DestroySkin(EngineInterface::ISkin* skin);
	int GetSkinsCount();
	TSkin* GetSkin(int index);
	TBone* CreateBone(TBone* parent);
	EngineInterface::IBone* CreateBone(EngineInterface::IBone* parent);
	void DestroyBone(TBone* bone);
	void DestroyBone(EngineInterface::IBone* bone);
	int GetBoneIndex(TBone* bone);
	int GetBoneIndex(EngineInterface::IBone* bone);
	TBone* GetBone(int index)
	{
		return bones[index].get();
	}
	TBone* GetRoot();
	std::vector<TBone*> GetAllBones();

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};