#pragma once

#include "IPhysShape.h"

namespace EngineInterface
{
	class IBaluTransformedSpriteInstance;
}

class b2Body;

namespace EngineInterface
{
	class IBaluPhysShapeInstance
	{
	public:
		//virtual IBaluTransformedClassInstance* GetParent() = 0;
		//virtual IBaluTransformedSpriteInstance* GetSpriteInstance() = 0;
		virtual void BuildFixture(b2Body* body, TBaluTransformWithScale class_transform)=0;
	};
	
#ifdef BALUENGINEDLL_EXPORTS
	class TBaluPhysShapeInstance : public IBaluPhysShapeInstance
	{
	protected:
		TBaluPhysShape* source;
		//TBaluTransform global;
		b2Fixture* fixture;
		b2Body* body;
		//TBaluTransformedClassInstance* parent;
		//TBaluTransformedSpriteInstance* sprite_instance;
	public:
		TBaluPhysShapeInstance(TBaluPhysShape* source);
		void BuildFixture(b2Body* body, TBaluTransformWithScale class_transform);

		//TODO попытаться сделать TBaluTransformedClassInstance
		//IBaluTransformedClassInstance* GetParent();
		//IBaluTransformedSpriteInstance* GetSpriteInstance();
	};
#endif
}