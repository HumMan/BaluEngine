#pragma once

#include <WorldDef/Objects/Class/IClass.h>
#include "../Sprite/ISpriteInstance.h"

#include "ISkeletonAnimationInstance.h"

namespace EngineInterface
{
	class TBaluTransformedClassInstance;
	class TBaluWorldInstance;
	class TBaluScriptInstance;
	class TBaluPhysShapeInstance;
	class TClassCompiledScripts;
	class TBaluTransformedClass;

	class ISpritesArray
	{
	public:
		virtual int GetSpritesCount() = 0;
		virtual IBaluTransformedSpriteInstance* GetSprite(int index) = 0;
	};

	class IBaluClassPhysBodyIntance
	{
	public:
		virtual TVec2 GetLinearVelocity() = 0;
		virtual void SetLinearVelocity(TVec2 velocity) = 0;
	};

	class TClass;
	class IBaluClassInstance: public ISpritesArray
	{
	public:
		virtual TClass* GetSource() = 0;
		virtual int GetSpritesCount() = 0;
		virtual IBaluTransformedSpriteInstance* GetSprite(int index) = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
		virtual bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result) = 0;
	};

	


	class IBaluTransformedClassInstance : public ISpritesArray
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
		virtual IBaluTransformedSpriteInstance* GetSprite(int index) = 0;
		virtual IProperties* GetProperties() = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
		virtual bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result) = 0;
	};
}