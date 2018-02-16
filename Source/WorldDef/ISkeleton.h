#pragma once


namespace BaluEngine
{
	namespace WorldDef
	{
		class IBone
		{
		public:
			virtual void SetTransform(TTransform) = 0;
		};

		class ISkin
		{
		public:
			virtual void SetBoneSprite(int bone_index, ISprite* sprite, TTransform global) = 0;
		};

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
	}
}