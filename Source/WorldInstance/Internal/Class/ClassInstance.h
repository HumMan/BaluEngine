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
				ISpritesArray* sprites;

				WorldDef::TTransform local;

				bool is_enable;

			public:
				TClassPhysBodyIntance(b2World* phys_world, WorldDef::IClassPhysBody* source, ISpritesArray* sprites, WorldDef::TTransform parent_transform);

				void BuildAllFixtures();

				bool IsEnable();
				void SetFixedRotation(bool fixed);

				BaluLib::TVec2 GetLinearVelocity();
				void SetLinearVelocity(BaluLib::TVec2 velocity);

				float GetAngularVelocity();
				void SetAngularVelocity(float velocity);

				WorldDef::TTransform GetTransform();
				void SetTransform(WorldDef::TTransform transform);
			};



			//class IScriptsCache
			//{
			//public:
			//	virtual TClassCompiledScripts* GetClassCompiled(TClass* source) = 0;
			//};


			class TClassInstance :public IClassInstance
			{
			private:
				WorldDef::IClass * source;
				ISceneObjectInstance* scene_object;
				//TResources* resources;

				std::vector<std::unique_ptr<ITransformedSpriteInstance>> sprites;
				std::unique_ptr<TClassPhysBodyIntance> phys_body;
				TSkeletonInstance skeleton;
				TSkeletonAnimationInstance skeleton_animation;

				//TProperties properties;
				void BuildAllFixtures();
			public:
				TClassInstance(WorldDef::IClass* source, b2World* phys_world, WorldDef::TTransform parent_transform, TResources* resources, ISceneObjectInstance* scene_object);
				WorldDef::IClass* GetSource();
				int GetSpritesCount();
				ITransformedSpriteInstance* GetSprite(int index);
				TSkeletonAnimationInstance* GetSkeletonAnimation();
				TClassPhysBodyIntance* GetPhysBody();
				bool PointCollide(BaluLib::TVec2 class_space_point, ITransformedSpriteInstance* &result);
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results);

				void UpdateTransform(WorldDef::TTransformWithScale transform);
			};

			class TTransformedClassInstance : public ITransformedClassInstance, public TSceneObjectInstance//, public IChangeListener
			{
			private:
				int uid;
				TClassInstance instance_class;
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
				TClassInstance* GetClass();
				WorldDef::ISceneObject* GetSource()
				{
					return source;
				}
				TTransformedClassInstance(WorldDef::ITransformedClass* source, IScene* scene);
				~TTransformedClassInstance();
				void SetTransform(WorldDef::TTransform transform);
				WorldDef::TTransform GetTransform();
				BaluLib::TVec2 GetScale();
				void SetScale(BaluLib::TVec2 scale);

				TClassPhysBodyIntance* GetPhysBody();

				int GetSpritesCount();
				ITransformedSpriteInstance* GetSprite(int index);

				TSkeletonAnimationInstance* GetSkeletonAnimation();

				bool PointCollide(BaluLib::TVec2 class_space_point, ITransformedSpriteInstance* &result);
				bool PointCollide(BaluLib::TVec2 scene_space_point);
				BaluLib::TOBB2 GetOBB();
				BaluLib::TAABB2 GetAABB();
				void QueryAABB(BaluLib::TAABB2 frustum, std::vector<ISpritePolygonInstance*>& results);

				void UpdateTransform();
				static ISceneObjectInstance* Clone(WorldDef::ISceneObject* source, IScene* scene);
			};

			REGISTER_FACTORY_CLASS(SceneObjectInstanceFactory, TTransformedClassInstance)
		}
	}
}