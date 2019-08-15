#pragma once

namespace BaluEngine
{
	namespace WorldInstance
	{

		class TPhysShapeUserData
		{
			std::weak_ptr < ISceneObjectInstance> scene_object;
			std::weak_ptr < ITransformedSpriteInstance> sprite;
		public:
			std::shared_ptr < ISceneObjectInstance> GetSceneObject()
			{
				return scene_object.lock();
			}
			std::shared_ptr < ITransformedSpriteInstance> GetSprite()
			{
				return sprite.lock();
			}
			TPhysShapeUserData(std::weak_ptr < ISceneObjectInstance> scene_object, std::weak_ptr < ITransformedSpriteInstance> sprite)
			{
				this->scene_object = scene_object;
				this->sprite = sprite;
			}
		};

		class IPhysShapeInstance
		{
		public:
			virtual TPhysShapeUserData* GetUserData() = 0;
			virtual ~IPhysShapeInstance() {};
		};
	}
}