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
				std::unique_ptr<IPhysShapeInstance> phys_shape;
				TSpritePolygonInstance polygon;

				//TProperties properties;
			public:
				WorldDef::ISprite * GetSource();
				TSpriteInstance(WorldDef::ISprite* source, TResources* resources, ISceneObjectInstance* scene_object, ITransformedSpriteInstance* parent);
				~TSpriteInstance();
				BaluLib::TOBB2 GetOBB();

				IPhysShapeInstance* GetPhysShape();

				TSpritePolygonInstance* GetPolygon();

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

				TSpriteInstance sprite_instance;
			public:
				//IProperties * GetProperties()
				//{
				//	return sprite_instance.GetProperties();
				//}
				TSpriteInstance* GetSprite();
				TTransformedSpriteInstance(WorldDef::ITransformedSprite* source, TResources* resources, ISceneObjectInstance* scene_object);

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

				IPhysShapeInstance* GetPhysShape();

				TSpritePolygonInstance* GetPolygon();

				void PlayAnimation(std::string animation_name, bool loop);
				void PauseAnimation(bool pause);
				void StopAnimation();

				void UpdateTransform(WorldDef::TTransformWithScale global);
			};
		}
	}
}