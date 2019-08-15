#pragma once

#include "../../Interface.h"

#include "SkeletonInstance.h"
#include "SkeletonAnimationInstance.h"

#include "../Scene/SceneInstance.h"

#include "../../../WorldDef/Internal/Common/RuntimeProperties.h"

class b2Body;
class b2World;

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{

			class TClassPhysBodyIntance : public IClassPhysBodyIntance
			{
			private:
				b2Body * phys_body;
				WorldDef::IClassPhysBody* source;
				b2World* phys_world;
				std::weak_ptr < ISpritesArray> sprites;

				WorldDef::TTransform local;

				bool is_enabled;

			public:
				TClassPhysBodyIntance(b2World* phys_world, WorldDef::IClassPhysBody* source, std::weak_ptr < ISpritesArray> sprites, WorldDef::TTransform parent_transform);

				void BuildAllFixtures();

				bool IsEnabled();
				void SetFixedRotation(bool fixed);

				BaluLib::TVec2 GetLinearVelocity();
				void SetLinearVelocity(BaluLib::TVec2 velocity);

				float GetAngularVelocity();
				void SetAngularVelocity(float velocity);

				WorldDef::TTransform GetTransform();
				void SetTransform(WorldDef::TTransform transform);
			};

			class TClassInstance :public IClassInstance
			{
			private:
				WorldDef::IClass * source;
				std::weak_ptr<ISceneObjectInstance> scene_object;
				//TResources* resources;

				std::vector<std::shared_ptr<ITransformedSpriteInstance>> sprites;
				std::shared_ptr<TClassPhysBodyIntance> phys_body;
				std::shared_ptr < TSkeletonInstance> skeleton;
				std::shared_ptr < TSkeletonAnimationInstance> skeleton_animation;

				//TProperties properties;
				//void BuildAllFixtures();
			public:
				TClassInstance();
				void Init(WorldDef::IClass* source, b2World* phys_world, WorldDef::TTransform parent_transform, 
					TResources* resources, std::weak_ptr < ISceneObjectInstance> scene_object, std::weak_ptr< TClassInstance> this_ptr);
				WorldDef::IClass* GetSource();
				int GetSpritesCount();
				int ContainsSprite(std::shared_ptr<ITransformedSpriteInstance> sprite);
				std::shared_ptr < ITransformedSpriteInstance> GetSprite(int index);
				std::shared_ptr < ISkeletonAnimationInstance> GetSkeletonAnimation();
				std::shared_ptr < IClassPhysBodyIntance> GetPhysBody();
				bool PointCollide(BaluLib::TVec2 class_space_point, std::shared_ptr < ITransformedSpriteInstance> &result);
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector< std::shared_ptr<ISpritePolygonInstance>>& results);

				void UpdateTransform(WorldDef::TTransformWithScale transform);
			};

			class TTransformedClassInstance : public ITransformedClassInstance, public TSceneObjectInstance//, public IChangeListener
			{
			private:
				int uid;
				std::shared_ptr < TClassInstance> instance_class;
				WorldDef::TTransformWithScale instance_transform;

				WorldDef::ITransformedClass* source;
			public:

				void SourceChanged();
				void BeforeDeleteSource();

				static const char* FactoryName()
				{
					return "ClassInstance";
				}
				const char* GetFactoryName()
				{
					return FactoryName();
				}
				std::shared_ptr < IClassInstance> GetClass();
				WorldDef::ISceneObject* GetSource()
				{
					return source;
				}
				TTransformedClassInstance(std::shared_ptr < IScene> scene);
				void Init(WorldDef::ITransformedClass* source, std::shared_ptr< TTransformedClassInstance> this_ptr);
				~TTransformedClassInstance();
				void SetTransform(WorldDef::TTransform transform);
				WorldDef::TTransform GetTransform();
				BaluLib::TVec2 GetScale();
				void SetScale(BaluLib::TVec2 scale);

				std::shared_ptr < IClassPhysBodyIntance> GetPhysBody();

				std::shared_ptr < ITransformedSpriteInstance> GetSprite(int index);

				std::shared_ptr < ISkeletonAnimationInstance> GetSkeletonAnimation();

				bool PointCollide(BaluLib::TVec2 class_space_point, std::shared_ptr < ITransformedSpriteInstance> &result);
				bool PointCollide(BaluLib::TVec2 scene_space_point);
				BaluLib::TOBB2 GetOBB();
				BaluLib::TAABB2 GetAABB();
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector< std::shared_ptr<ISpritePolygonInstance>>& results);

				void UpdateTransform();
				static std::shared_ptr<ISceneObjectInstance> Clone(WorldDef::ISceneObject* source, std::shared_ptr<IScene> scene);
			};

			REGISTER_FACTORY_CLASS(SceneObjectInstanceFactory, TTransformedClassInstance)
		}
	}
}