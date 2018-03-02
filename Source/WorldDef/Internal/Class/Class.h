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

				//void OnMouseMove(TMouseMoveCallback);

				TTransformedSprite* AddSprite(TSprite* sprite);
				ITransformedSprite* AddSprite(ISprite* sprite);
				void RemoveSprite(TSprite* sprite);
				int GetSpritesCount();
				TTransformedSprite* GetSprite(int index);

				TClassPhysBody* GetPhysBody();

				TSkeletonAnimation* GetSkeletonAnimation();
				TSkeleton* GetSkeleton();

				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};

			class TTransformedClass : public ITransformedClass, public ISceneObject, public TChangeListenerArray
			{
				TClass* balu_class;
				TTransformWithScale transform;
			public:
				static const char* FactoryName()
				{
					return "ClassInstance";
				}
				const char* GetFactoryName()
				{
					return FactoryName();
				}
				TTransformedClass()
				{
					this->balu_class = nullptr;
				}
				TTransformedClass(TClass* balu_class)
				{
					this->balu_class = balu_class;
				}
				void SetTransform(TTransform transform)
				{
					this->transform.transform = transform;
					OnChanged();
				}
				void SetScale(BaluLib::TVec2 scale)
				{
					this->transform.scale = scale;
					OnChanged();
				}
				TTransform GetTransform()
				{
					return transform.transform;
				}
				BaluLib::TVec2 GetScale()
				{
					return transform.scale;
				}
				TTransformWithScale GetTransformWithScale()
				{
					return transform;
				}
				TClass* GetClass()
				{
					return balu_class;
				}
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
				static ISceneObject* Clone()
				{
					return new TTransformedClass();
				}
			};

			REGISTER_FACTORY_CLASS(SceneObjectFactory, TTransformedClass)
		}
	}
}