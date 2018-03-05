#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{

		class TPhysShapeUserData
		{
			ISceneObjectInstance* scene_object;
			ITransformedSpriteInstance* sprite;
		public:
			ISceneObjectInstance * GetSceneObject()
			{
				return scene_object;
			}
			ITransformedSpriteInstance* GetSprite()
			{
				return sprite;
			}
			TPhysShapeUserData(ISceneObjectInstance* scene_object, ITransformedSpriteInstance* sprite)
			{
				this->scene_object = scene_object;
				this->sprite = sprite;
			}
		};

		class IPhysShapeInstance
		{
		public:
			virtual TPhysShapeUserData* GetUserData() = 0;
		};
	}
}