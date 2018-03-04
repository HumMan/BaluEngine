#pragma once

#include <WorldDef/Objects/Sprite/ISprite.h>
#include "IPhysShapeInstance.h"
#include "ISpritePolygonInstance.h"

namespace EngineInterface
{
	class TBaluTransformedSpriteInstance;

	class IBaluSpriteInstance
	{
	public:
	};


	class IBaluTransformedSpriteInstance
	{
	public:
		virtual IBaluTransformedSprite* GetSource()=0;
		virtual IBaluPhysShapeInstance* GetPhysShape() = 0;
		virtual TVec2 GetScale() = 0;
		virtual TOBB2 GetOBB() = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual void SetTransform(TBaluTransform local) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual IBaluSpritePolygonInstance* GetPolygon() = 0;
		virtual IProperties* GetProperties() = 0;
	};

}