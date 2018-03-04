#pragma once

#include <WorldDef/Objects/Sprite/IPhysShape.h>

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

}