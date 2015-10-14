#pragma once

#include "IPhysShape.h"

namespace EngineInterface
{
	class IBaluPhysShapeInstance
	{
	public:
		//virtual IBaluInstance* GetParent() = 0;
		//virtual IBaluTransformedSprite* GetSpriteInstance() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluPhysShapeInstance : public IBaluPhysShapeInstance
	{
	protected:
		TBaluPhysShape* source;
		b2Fixture* fixture;
		b2Body* body;

	public:
		TBaluPhysShapeInstance(TBaluPhysShape* source);
		void BuildFixture(b2Body* body, TBaluTransformWithScale transform);
	};
#endif
}