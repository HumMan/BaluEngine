
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "ISprite.h"
#include "IPhysShapeInstance.h"
#include "ISpritePolygonInstance.h"
#endif

#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassInstanceSpriteInstance
	{
	public:
		//virtual void SetTransform(TBaluTransform local)=0;
		//virtual TBaluTransform GetTransform() = 0;
		virtual IBaluClassSpriteInstance* GetSource()=0;
		virtual IBaluPhysShapeInstance* GetPhysShape() = 0;
		virtual TVec2 GetScale() = 0;
		virtual TOBB2 GetOBB() = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual void SetTransform(TBaluTransform local) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual IBaluSpritePolygonInstance* GetPolygon() = 0;
		virtual EngineInterface::IProperties* GetProperties() = 0;
		virtual void SetTag(void* tag)=0;
		virtual void* GetTag()=0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluClassInstanceSpriteInstance, "IClassInstanceSpriteInstance");
	MUnpackRA0(WrapPointer<IBaluClassSpriteInstance>,	TYPE, GetSource);
	MUnpackRA0(WrapPointer<IBaluPhysShapeInstance>,		TYPE, GetPhysShape);
	MUnpackRA0(WrapValue<TVec2>,						TYPE, GetScale);
	MUnpackRA0(WrapPointer<IBaluSpritePolygonInstance>,	TYPE, GetPolygon);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

}