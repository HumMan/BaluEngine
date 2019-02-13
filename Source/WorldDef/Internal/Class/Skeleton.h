#pragma once

#include "../../Interface.h"

#include "../Sprite/Sprite.h"

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
				IBone * parent;
				std::vector<IBone*> children;

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
				std::vector<std::vector<std::unique_ptr<TTransformedSprite>>> sprites_of_bones;
			public:
				TSkin()
				{
				}
				TSkin(int bones_count);
				void SetBoneSprite(int bone_index, TSprite* sprite, TTransform global);
				void SetBoneSprite(int bone_index, ISprite* sprite, TTransform global);
				int GetBonesCount();
				std::vector<TTransformedSprite*> GetSpritesOfBone(int bone_index);

				std::vector<ITransformedSprite*> IGetSpritesOfBone(int bone_index);

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			class TSkeleton : public ISkeleton, public ISerializable
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
				ISkin* CreateSkin();
				void DestroySkin(ISkin* skin);
				int GetSkinsCount()const;
				ISkin* GetSkin(int index)const;
				IBone* CreateBone(IBone* parent);
				void DestroyBone(IBone* bone);
				int GetBoneIndex(const IBone* bone)const;
				IBone* GetBone(int index)const;
				IBone* GetRoot()const;
				std::vector<IBone*> GetAllBones()const;

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
		}
	}
}