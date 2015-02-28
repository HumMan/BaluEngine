#pragma once

#include "IClass.h"

#include "ISpriteInstance.h"

namespace EngineInterface
{
	class ISensorInstance
	{

	};

	class IBaluClassPhysBodyIntance
	{
	public:
		virtual TVec2 GetLinearVelocity() = 0;
		virtual void SetLinearVelocity(TVec2 velocity) = 0;
	};

	class ISkeletonAnimationInstance
	{
	public:
		virtual void Update(float step) = 0;
		virtual void PlayAnimation(std::string name, float alpha) = 0;
		virtual void StopAnimation(std::string name) = 0;
	};

	class IBaluInstance
	{
	public:
		virtual TOBB2 GetOBB()=0;
		virtual IBaluClass* GetClass()=0;
		virtual TBaluTransform GetTransform()=0;
		virtual void SetTransform(TBaluTransform) = 0;
		virtual TVec2 GetScale() = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual int GetSpritesCount() = 0;
		virtual IBaluSpriteInstance* GetSprite(int index) = 0;
		virtual IProperties* GetProperties() = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
	};
}