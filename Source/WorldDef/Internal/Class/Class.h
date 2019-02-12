#pragma once

#include "../../Interface.h"

#include "../Common/Common.h"

#include "../Sprite/Sprite.h"
#include "Skeleton.h"
#include "SkeletonAnimation.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			class TClassPhysBody : public TProperties, public IClassPhysBody
			{
			protected:
				void InitAllProperties()
				{					
					InitProperty_FixedRotation();
					InitProperty_PhysBodyType();
					InitProperty_Enabled();
				}
			public:

				BALU_ENGINE_REGISTER_PROPERTY(Enabled, PropertyType::Bool, false)				
				BALU_ENGINE_REGISTER_PROPERTY(PhysBodyType, PropertyType::PhysBodyType, TPhysBodyType::Static)
				BALU_ENGINE_REGISTER_PROPERTY(FixedRotation, PropertyType::Bool, false)
				

				TClassPhysBody();
				
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			class TClass : public IClass, public TWorldObject
			{
			private:
				std::vector<std::unique_ptr<TTransformedSprite>> sprites;
				TClassPhysBody phys_body;
				std::unique_ptr<TSkeleton> skeleton;
				std::unique_ptr<TSkeletonAnimation> skeleton_animation;

				void Initialize();

			public:
				static TWorldObjectType GetWorldObjectType()
				{
					return TWorldObjectType::Class;
				}
				TClass(std::string name, IWorld* world);

				bool PointCollide(BaluLib::TVec2 class_space_point);
				BaluLib::TAABB2 GetAABB();

				virtual ~TClass();
				TTransformedSprite* CreateSpriteInstance(TSprite* sprite);
				ITransformedSprite* CreateSpriteInstance(ISprite* sprite);
				void DestroySpriteInstance(ITransformedSprite* sprite);
				int GetSpritesCount();
				TTransformedSprite* GetSprite(int index);

				TClassPhysBody* GetPhysBody();

				TSkeletonAnimation* GetSkeletonAnimation();
				TSkeleton* GetSkeleton();

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};


			class TTransformedClassPropertyChangeCommand
			{
			public:
				std::string scene_name;
				int scene_object_id;
				std::string property_name;
				std::string property_value;
			};

			class TTransformedClass :public TProperties, public ITransformedClass, public ISceneObject, public TChangeListenerArray
			{
				TClass* balu_class;
				IScene* parent;

			protected:
				void InitAllProperties()
				{
					InitProperty_TransformTest();
				}
			public:

				BALU_ENGINE_REGISTER_PROPERTY(TransformTest, PropertyType::TransformWithScale, TTransformWithScale())

				static const char* FactoryName()
				{
					return "ClassInstance";
				}
				const char* GetFactoryName()
				{
					return FactoryName();
				}
				IScene* GetScene()
				{
					return parent;
				}
				TTransformedClass(IScene* parent)
				{
					InitAllProperties();

					this->SetTransformTest(TTransformWithScale());
					this->balu_class = nullptr;
					this->parent = parent;
				}
				TTransformedClass(TClass* balu_class, IScene* parent)
				{
					this->balu_class = balu_class;
					this->parent = parent;
				}
				void SetTransform(TTransform transform)
				{

					this->TransformTestValue.transform = transform;
					OnChanged();
				}
				void SetScale(BaluLib::TVec2 scale)
				{
					this->TransformTestValue.scale = scale;
					OnChanged();
				}
				TTransform GetTransform()
				{
					return TransformTestValue.transform;
				}
				BaluLib::TVec2 GetScale()
				{
					return TransformTestValue.scale;
				}
				TTransformWithScale GetTransformWithScale()
				{
					return TransformTestValue;
				}
				TClass* GetClass()
				{
					return balu_class;
				}
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
				static ISceneObject* Clone(IScene* scene)
				{
					return new TTransformedClass(scene);
				}
			};

			REGISTER_FACTORY_CLASS(SceneObjectFactory, TTransformedClass)
		}
	}
}