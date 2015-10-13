#pragma once

#include "../Class/IClassInstance.h"
#include "../Sprite/ISpriteInstance.h"

namespace EngineInterface
{
	class IBaluInstance;
	class TBaluInstance;
	class IBaluClassSpriteInstance;
}

namespace EngineInterface
{
	class IBaluPhysShapeInstance
	{
	public:
		virtual IBaluInstance* GetParent() = 0;
		virtual IBaluClassSpriteInstance* GetSpriteInstance() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluPhysShapeInstance : public IBaluPhysShapeInstance
	{
	protected:
		TBaluPhysShape* source;
		//TBaluTransform global;
		b2Fixture* fixture;
		b2Body* body;
		TBaluInstance* parent;
		TBaluClassSpriteInstance* sprite_instance;
	public:
		TBaluPhysShapeInstance(TBaluPhysShape* source, TBaluInstance* parent_instance, TBaluClassSpriteInstance* sprite_instance);
		void BuildFixture(b2Body* body, TBaluTransformWithScale class_transform);

		//TODO попытаться сделать TBaluInstance
		IBaluInstance* GetParent();
		IBaluClassSpriteInstance* GetSpriteInstance();
	};
#endif
}