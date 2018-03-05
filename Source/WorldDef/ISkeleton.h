#pragma once


namespace BaluEngine
{
	namespace WorldDef
	{
		class IBone
		{
		public:
			virtual void SetTransform(TTransform) = 0;
			virtual int GetChildrenCount()=0;
			virtual IBone* GetChild(int index)=0;
			virtual TTransform GetTransform()=0;
		};

		class ISkin
		{
		public:
			virtual void SetBoneSprite(int bone_index, ISprite* sprite, TTransform global) = 0;
			virtual std::vector<ITransformedSprite*> IGetSpritesOfBone(int bone_index)=0;
			virtual int GetBonesCount() = 0;
		};

		class ISkeleton
		{
		public:
			virtual ISkin * CreateSkin()=0;
			virtual void DestroySkin(ISkin* skin)=0;
			virtual int GetSkinsCount()const =0;
			virtual ISkin* GetSkin(int index)const =0;
			virtual IBone* CreateBone(IBone* parent)=0;
			virtual void DestroyBone(IBone* bone)=0;
			virtual int GetBoneIndex(const IBone* const bone)const =0;
			virtual IBone* GetBone(int index)const =0;
			virtual IBone* GetRoot()const =0;
			virtual std::vector<IBone*> GetAllBones()const =0;
		};
	}
}