
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
	class IBaluSpriteInstance
	{
	public:
		//virtual void SetTransform(TBaluTransform local)=0;
		//virtual TBaluTransform GetTransform() = 0;
		virtual IBaluSprite* GetSourceSprite() = 0;
		virtual IBaluPhysShapeInstance* GetPhysShape() = 0;
		virtual TVec2 GetScale() = 0;
		virtual IBaluSpritePolygonInstance* GetPolygon() = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES

	DECL_SCRIPT_TYPE(IBaluSpriteInstance, "ISpriteInstance");

#endif
}