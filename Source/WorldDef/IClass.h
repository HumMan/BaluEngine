#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{

		enum TPhysBodyType
		{
			Static,
			Dynamic,
			Kinematic
		};

		class IClassPhysBody
		{
		public:
			virtual void SetFixedRotation(bool fixed) = 0;
			virtual void SetPhysBodyType(TPhysBodyType type) = 0;
			virtual void Enable(bool enable) = 0;
			virtual bool IsEnable() = 0;
		};

		class IClass : public virtual IWorldObject
		{
		public:
			static std::string GetDefaultName()
			{
				return "class";
			}
			virtual BaluLib::TAABB2 GetAABB() = 0;
			virtual ITransformedSprite* AddSprite(ISprite* sprite) = 0;

			virtual int GetSpritesCount() = 0;
			virtual ITransformedSprite* GetSprite(int index) = 0;
			virtual ISkeletonAnimation* GetSkeletonAnimation() = 0;
			virtual IClassPhysBody* GetPhysBody() = 0;
			virtual ISkeleton* GetSkeleton() = 0;
		};

		class ITransformedClass
		{
		public:
			virtual ~ITransformedClass() {}
			virtual void SetTransform(TTransform transform) = 0;
			virtual void SetScale(BaluLib::TVec2 scale) = 0;
			virtual TTransform GetTransform() = 0;
			virtual BaluLib::TVec2 GetScale() = 0;
			virtual IClass* GetClass() = 0;
		};
	}
}