
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IClass.h"
#include "../Sprite/ISpriteInstance.h"
#endif

#endif

namespace EngineInterface
{
#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassPhysBodyIntance
	{
	public:
		virtual TVec2 GetLinearVelocity() = 0;
		virtual void SetLinearVelocity(TVec2 velocity) = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluClassPhysBodyIntance, "IClassPhysBodyInstance");
	MUnpackRA0(WrapValue<TVec2>, TYPE, GetLinearVelocity);
	MUnpackA1(TYPE, SetLinearVelocity, WrapValue<TVec2>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ISkeletonAnimationInstance
	{
	public:
		virtual void Update(float step) = 0;
		virtual void PlayAnimation(std::string name, float alpha) = 0;
		virtual void StopAnimation(std::string name) = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, ISkeletonAnimationInstance, "ISkeletonAnimationInstance");
	MUnpackA2(TYPE, PlayAnimation, TStringWrapper<std::string>, WrapValue<float>);
	MUnpackA1(TYPE, StopAnimation, TStringWrapper<std::string>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassInstance
	{
	public:
		virtual IBaluClass* GetClass() = 0;
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

	class IBaluInstance
	{
	public:
		virtual void UpdateTransform() = 0;
		virtual TOBB2 GetOBB() = 0;
		virtual IBaluClassInstance* GetClass() = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual void SetTransform(TBaluTransform) = 0;
		virtual TVec2 GetScale() = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual int GetSpritesCount() = 0;
		virtual IBaluClassInstanceSpriteInstance* GetSprite(int index) = 0;
		virtual IBaluClassInstanceSpriteInstance* AddSprite(IBaluClassSpriteInstance* source) = 0;
		virtual IProperties* GetProperties() = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
		virtual bool PointCollide(TVec2 class_space_point, EngineInterface::IBaluClassInstanceSpriteInstance* &result) = 0;
		virtual void SetTag(void* tag) = 0;
		virtual void* GetTag() = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluInstance, "IInstance");
	MUnpackA1(TYPE, SetScale, WrapValue<TVec2>);
	MUnpackRA0(WrapPointer<IProperties>, TYPE, GetProperties);
	MUnpackRA0(WrapPointer<IBaluClassPhysBodyIntance>, TYPE, GetPhysBody);
	MUnpackRA1(WrapPointer<IBaluClassInstanceSpriteInstance>, TYPE, GetSprite, WrapValue<int>);
	MUnpackRA0(WrapPointer<ISkeletonAnimationInstance>, TYPE, GetSkeletonAnimation);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}