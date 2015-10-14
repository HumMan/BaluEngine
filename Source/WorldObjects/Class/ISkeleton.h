#pragma once

#include <map>
#include <set>

#include <WorldObjects/Sprite/ISprite.h>

namespace EngineInterface
{
	class TSkeleton;
}

namespace EngineInterface
{

	class IBone
	{
	public:
		virtual void SetTransform(TBaluTransform) = 0;
	};

	class TBone : public IBone
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

	class ISkin
	{
	public:
		virtual void SetBoneSprite(int bone_index, IBaluSprite* sprite, TBaluTransform global) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TSkin : public ISkin
	{
	private:
		std::vector<std::vector<TBaluTransformedSprite>> sprites_of_bones;
	public:
		TSkin()
		{
		}
		TSkin(int bones_count);
		void SetBoneSprite(int bone_index, TBaluSprite* sprite, TBaluTransform global);
		void SetBoneSprite(int bone_index, IBaluSprite* sprite, TBaluTransform global);
		int GetBonesCount();
		std::vector<TBaluTransformedSprite>& GetSpritesOfBone(int bone_index);

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};

#endif

	class ISkeleton
	{
	public:
		virtual ISkin* CreateSkin() = 0;
		virtual void DestroySkin(ISkin* skin) = 0;
		virtual int GetSkinsCount() = 0;
		virtual ISkin* GetSkin(int index) = 0;
		virtual IBone* CreateBone(IBone* parent) = 0;
		virtual void DestroyBone(IBone* bone) = 0;
		virtual int GetBoneIndex(IBone* bone) = 0;
		virtual IBone* GetRoot() = 0;
		//virtual std::vector<IBone*> GetAllBones() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TSkeleton : public ISkeleton
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
		void DestroySkin(ISkin* skin);
		int GetSkinsCount();
		TSkin* GetSkin(int index);
		TBone* CreateBone(TBone* parent);
		IBone* CreateBone(IBone* parent);
		void DestroyBone(TBone* bone);
		void DestroyBone(IBone* bone);
		int GetBoneIndex(TBone* bone);
		int GetBoneIndex(IBone* bone);
		TBone* GetBone(int index)
		{
			return bones[index].get();
		}
		TBone* GetRoot();
		std::vector<TBone*> GetAllBones();

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
#endif

}