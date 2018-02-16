#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TSkeleton;

			class TBone : public IBone
			{
			private:
				TBone * parent;
				std::vector<TBone*> children;

				TTransform local;
			public:
				TBone()
				{
				}
				TBone(TBone* parent);

				void SetTransform(TTransform);
				TTransform GetTransform();

				void AddChild(TBone* bone);
				int GetChildrenCount();
				TBone* GetChild(int index);

				void Save(pugi::xml_node& parent_node, const int version, const TSkeleton* skeleton)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world, TSkeleton* skeleton);
			};

			class TSkin : public ISkin, public ISerializable
			{
			private:
				std::vector<std::vector<TTransformedSprite>> sprites_of_bones;
			public:
				TSkin()
				{
				}
				TSkin(int bones_count);
				void SetBoneSprite(int bone_index, TBaluSprite* sprite, TTransform global);
				void SetBoneSprite(int bone_index, ISprite* sprite, TTransform global);
				int GetBonesCount();
				std::vector<TTransformedSprite>& GetSpritesOfBone(int bone_index);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			class TSkeleton : public ISkeleton, public TChangeListenerArray, public ISerializable
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

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
		}
	}
}