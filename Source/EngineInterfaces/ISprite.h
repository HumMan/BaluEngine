
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "ICallbacks.h"
#include "IPhysShape.h"
#include "ISpritePolygon.h"
#endif

namespace EngineInterface
{
	class IBaluPhysShapeInstance;
	class IBaluClass;
}

#include <string>
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluSprite
	{
	public:
		static std::string GetDefaultName()
		{
			return "sprite";
		}
		virtual std::string GetName() = 0;
		virtual void SetName(std::string name) = 0;
		virtual void SetPhysShape(IBaluPhysShape* shape) = 0;
		virtual IBaluPhysShape* GetPhysShape() = 0;
		virtual void SetPhysShapeFromGeometry() = 0;
		virtual IBaluSpritePolygon* GetPolygon() = 0;
		virtual void AddOnCollide(IBaluClass* obstancle_class, TScript script) = 0;
		virtual std::vector<std::pair<IBaluClass*, TScript>>& GetOnCollide() = 0;
		virtual void RemoveOnCollide(int index)=0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSprite, "ISprite");
	MUnpackA1(TYPE, SetPhysShape, WrapInterface<IBaluPhysShape>);
	MUnpackRA0(WrapPointer<IBaluPhysShape>, TYPE, GetPhysShape);
	MUnpackRA0(WrapPointer<IBaluSpritePolygon>, TYPE, GetPolygon);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassSpriteInstance
	{
	public:
		virtual IBaluSprite* GetSprite() = 0;
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual TVec2 GetScale() = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluClassSpriteInstance, "IClassSpriteInstance");
	MUnpackRA0(WrapPointer<IBaluSprite>, TYPE, GetSprite);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}