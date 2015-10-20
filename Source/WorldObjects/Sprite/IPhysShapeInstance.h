#pragma once

#include "IPhysShape.h"

namespace EngineInterface
{
	class TBaluTransformedSpriteInstance;
	class TSceneObjectInstance;
	class IBaluTransformedClassInstance;
}

class b2Body;

namespace EngineInterface
{
	class TPhysShapeUserData
	{
		TSceneObjectInstance* scene_object;
		TBaluTransformedSpriteInstance* sprite;
	public:
		TSceneObjectInstance* GetSceneObject()
		{
			return scene_object;
		}
		TBaluTransformedSpriteInstance* GetSprite()
		{
			return sprite;
		}
		TPhysShapeUserData(TSceneObjectInstance* scene_object, TBaluTransformedSpriteInstance* sprite)
		{
			this->scene_object = scene_object;
			this->sprite = sprite;
		}
	};

	class IBaluPhysShapeInstance
	{
	public:
		virtual TPhysShapeUserData* GetUserData()=0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluPhysShapeInstance : public IBaluPhysShapeInstance, public IChangeListener
	{
	protected:
		TBaluPhysShape* source;
		b2Fixture* fixture;
		b2Body* body;
		TPhysShapeUserData user_data;
	public:
		TBaluPhysShapeInstance(TBaluPhysShape* source, TPhysShapeUserData user_data);
		~TBaluPhysShapeInstance();
		void BuildFixture(b2Body* body, TBaluTransformWithScale class_transform);
		TPhysShapeUserData* GetUserData()
		{
			return &user_data;
		}
	};
#endif
}