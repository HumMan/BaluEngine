#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{


		class ISpritesArray
		{
		public:
			virtual int GetSpritesCount() = 0;
			virtual ITransformedSpriteInstance* GetSprite(int index) = 0;
		};

		class IClassPhysBodyIntance
		{
		public:
			virtual BaluLib::TVec2 GetLinearVelocity() = 0;
			virtual void SetLinearVelocity(BaluLib::TVec2 velocity) = 0;
		};


		class IClassInstance : public ISpritesArray
		{
		public:
			virtual WorldDef::IClass* GetSource() = 0;
			virtual int GetSpritesCount() = 0;
			virtual ITransformedSpriteInstance* GetSprite(int index) = 0;
			virtual IClassPhysBodyIntance* GetPhysBody() = 0;
			virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
			virtual bool PointCollide(BaluLib::TVec2 class_space_point, ITransformedSpriteInstance* &result) = 0;
		};

		class ITransformedClassInstance : public ISpritesArray
		{
		public:
			virtual void UpdateTransform() = 0;
			virtual BaluLib::TOBB2 GetOBB() = 0;
			virtual IClassInstance* GetClass() = 0;
			virtual WorldDef::TTransform GetTransform() = 0;
			virtual void SetTransform(WorldDef::TTransform) = 0;
			virtual BaluLib::TVec2 GetScale() = 0;
			virtual void SetScale(BaluLib::TVec2 scale) = 0;
			virtual int GetSpritesCount() = 0;
			virtual ITransformedSpriteInstance* GetSprite(int index) = 0;
			//virtual IProperties* GetProperties() = 0;
			virtual IClassPhysBodyIntance* GetPhysBody() = 0;
			virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
			virtual bool PointCollide(BaluLib::TVec2 class_space_point, ITransformedSpriteInstance* &result) = 0;
		};
	}
}