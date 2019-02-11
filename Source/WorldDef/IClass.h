#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{

		enum TPhysBodyType
		{
			Static,
			Kinematic,
			Dynamic,
		};

		class IClassPhysBody: public ISerializable
		{
		public:
			BALU_ENGINE_VPROPERTY(Enabled, bool)
			BALU_ENGINE_VPROPERTY(PhysBodyType, TPhysBodyType)
			BALU_ENGINE_VPROPERTY(FixedRotation,bool)

		};

		class IClass : public virtual IWorldObject
		{
		public:
			static std::string GetDefaultName()
			{
				return "class";
			}
			virtual BaluLib::TAABB2 GetAABB() = 0;
			virtual ITransformedSprite* CreateSpriteInstance(ISprite* sprite) = 0;
			virtual void DestroySpriteInstance(ITransformedSprite* sprite)=0;
			virtual int GetSpritesCount() = 0;
			virtual ITransformedSprite* GetSprite(int index) = 0;
			virtual ISkeletonAnimation* GetSkeletonAnimation() = 0;
			virtual IClassPhysBody* GetPhysBody() = 0;
			virtual ISkeleton* GetSkeleton() = 0;
		};

		class ITransformedClass: public virtual ISceneObject
		{
		public:
			virtual ~ITransformedClass() {}
			virtual void SetTransform(TTransform transform) = 0;
			virtual void SetScale(BaluLib::TVec2 scale) = 0;
			virtual TTransform GetTransform() = 0;
			virtual BaluLib::TVec2 GetScale() = 0;
			virtual TTransformWithScale GetTransformWithScale() = 0;
			virtual IClass* GetClass() = 0;
		};
	}
}