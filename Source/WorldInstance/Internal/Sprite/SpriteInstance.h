#pragma once

#include "../../Interface.h"

#include "SpritePolygonInstance.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{


			class TSpriteInstance//: public IChangeListener
			{
			private:
				WorldDef::ISprite * source;
				std::shared_ptr<IPhysShapeInstance> phys_shape;
				std::shared_ptr < TSpritePolygonInstance> polygon;

				//TProperties properties;
			public:
				WorldDef::ISprite * GetSource();
				TSpriteInstance(WorldDef::ISprite* source, TResources* resources, std::weak_ptr < ISceneObjectInstance> scene_object, std::weak_ptr < ITransformedSpriteInstance> parent);
				~TSpriteInstance();
				BaluLib::TOBB2 GetOBB();

				std::shared_ptr < IPhysShapeInstance> GetPhysShape();

				std::shared_ptr < TSpritePolygonInstance> GetPolygon();

				void PlayAnimation(std::string animation_name, bool loop);
				void PauseAnimation(bool pause);
				void StopAnimation();

				void UpdateTransform(WorldDef::TTransformWithScale global);
			};

			class TTransformedSpriteInstance : public ITransformedSpriteInstance//, public IChangeListener
			{
			private:
				WorldDef::ITransformedSprite * source;

				WorldDef::TTransformWithScale transform;

				std::shared_ptr < TSpriteInstance> sprite_instance;
			public:
				//IProperties * GetProperties()
				//{
				//	return sprite_instance.GetProperties();
				//}
				std::shared_ptr < TSpriteInstance> GetSprite();
				TTransformedSpriteInstance();
				void Init(WorldDef::ITransformedSprite* source, TResources* resources, std::weak_ptr < ISceneObjectInstance> scene_object, std::weak_ptr<ITransformedSpriteInstance> this_ptr);

				void SetTransform(WorldDef::TTransform local)
				{
					this->transform.transform = local;
				}
				WorldDef::TTransform GetTransform()
				{
					return transform.transform;
				}
				BaluLib::TVec2 GetScale()
				{
					return transform.scale;
				}
				void SetScale(BaluLib::TVec2 scale)
				{
					transform.scale = scale;
				}
				WorldDef::ITransformedSprite* GetSource();

				BaluLib::TOBB2 GetOBB();

				std::shared_ptr < IPhysShapeInstance> GetPhysShape();

				std::shared_ptr < ISpritePolygonInstance> GetPolygon();

				void PlayAnimation(std::string animation_name, bool loop);
				void PauseAnimation(bool pause);
				void StopAnimation();

				void UpdateTransform(WorldDef::TTransformWithScale global);
			};
		}
	}
}