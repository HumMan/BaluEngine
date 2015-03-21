#pragma once

#include "ISpritePolygon.h"

namespace EngineInterface
{
	class IBaluSpritePolygonInstance
	{
	public:
		//virtual void SetSpritePolygon(std::string name) = 0;
		virtual IBaluSpritePolygon* GetSpritePolygon() = 0;

		virtual void SetActiveAnimation(std::string) = 0;
		//virtual TBaluTransform GetGlobalTransform() = 0;
	};
}