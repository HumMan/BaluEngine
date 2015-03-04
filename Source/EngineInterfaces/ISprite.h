#pragma once

#include "IPhysShape.h"
#include "ISpritePolygon.h"

#include <string>

namespace EngineInterface
{
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
		virtual IBaluSpritePolygon* GetPolygone() = 0;
	};
}