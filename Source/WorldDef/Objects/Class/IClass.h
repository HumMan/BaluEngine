#pragma once

#include <map>
#include <set>

#include <Common/IProperties.h>
#include "../Sprite/ISprite.h"
#include "../Sprite/IPhysShape.h"

#include "ISkeletonAnimation.h"

namespace EngineInterface
{
	class IBaluPhysShapeInstance;
	class IBaluClass;
}

namespace EngineInterface
{

	enum TPhysBodyType
	{
		Static,
		Dynamic,
		Kinematic
	};

	class IBaluClassPhysBody
	{
	public:
		virtual void SetFixedRotation(bool fixed) = 0;
		virtual void SetPhysBodyType(TPhysBodyType type) = 0;
		virtual void Enable(bool enable) = 0;
		virtual bool IsEnable() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluClassPhysBody : public IBaluClassPhysBody
	{
	private:
		b2BodyDef body_def;
		bool enable;
	public:
		TBaluClassPhysBody();
		int GetSensorsCount();
		void SetFixedRotation(bool fixed);
		void SetPhysBodyType(TPhysBodyType type);
		void Enable(bool enable);
		bool IsEnable();
		b2BodyDef GetBodyDef();
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
#endif

	class IBaluClass: public virtual IBaluWorldObject
	{
	public:
		static std::string GetDefaultName()
		{
			return "class";
		}
		virtual TAABB2 GetAABB()=0;
		virtual IBaluTransformedSprite* AddSprite(IBaluSprite* sprite) = 0;

		virtual int GetSpritesCount() = 0;
		virtual IBaluTransformedSprite* GetSprite(int index) = 0;
		virtual ISkeletonAnimation* GetSkeletonAnimation() = 0;
		virtual IBaluClassPhysBody* GetPhysBody()=0;
		virtual ISkeleton* GetSkeleton()=0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluClass : public IBaluClass, public TBaluWorldObject
	{
	private:

		int layer_id;

		std::vector<std::unique_ptr<TBaluTransformedSprite>> sprites;
		TBaluClassPhysBody phys_body;
		std::unique_ptr<TSkeleton> skeleton;
		std::unique_ptr<TSkeletonAnimation> skeleton_animation;
		TProperties properties;

		void Initialize();

	public:
		static TWorldObjectType GetWorldObjectType()
		{
			return TWorldObjectType::Class;
		}
		TBaluClass(std::string name, IBaluWorld* world);

		IProperties* GetProperties();
		bool PointCollide(TVec2 class_space_point);
		TAABB2 GetAABB();

		virtual ~TBaluClass();

		//void OnMouseMove(TMouseMoveCallback);

		TBaluTransformedSprite* AddSprite(TBaluSprite* sprite);
		IBaluTransformedSprite* AddSprite(IBaluSprite* sprite);
		void RemoveSprite(TBaluSprite* sprite);
		int GetSpritesCount();
		TBaluTransformedSprite* GetSprite(int index);

		TBaluClassPhysBody* GetPhysBody();

		TSkeletonAnimation* GetSkeletonAnimation();
		TSkeleton* GetSkeleton();

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);

		//IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IBaluWorldInstance* world_instance);
	};
#endif

	class IBaluTransformedClass
	{
	public:
		virtual ~IBaluTransformedClass(){}
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual TVec2 GetScale() = 0;
		virtual IBaluClass* GetClass() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluTransformedClass : public IBaluTransformedClass, public TSceneObject, public TChangeListenerArray
	{
		TBaluClass* balu_class;
		TBaluTransformWithScale transform;
	public:
		static const char* FactoryName()
		{
			return "ClassInstance";
		}
		const char* GetFactoryName()
		{
			return FactoryName();
		}
		TBaluTransformedClass()
		{
			this->balu_class = nullptr;
		}
		TBaluTransformedClass(TBaluClass* balu_class)
		{
			this->balu_class = balu_class;
		}
		void SetTransform(TBaluTransform transform)
		{
			this->transform.transform = transform;
			OnChanged();
		}
		void SetScale(TVec2 scale)
		{
			this->transform.scale = scale;
			OnChanged();
		}
		TBaluTransform GetTransform()
		{
			return transform.transform;
		}
		TVec2 GetScale()
		{
			return transform.scale;
		}
		TBaluTransformWithScale GetTransformWithScale()
		{
			return transform;
		}
		TBaluClass* GetClass()
		{
			return balu_class;
		}
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
		static TSceneObject* Clone()
		{
			return new TBaluTransformedClass();
		}
	};
	REGISTER_FACTORY_CLASS(SceneObjectFactory, TBaluTransformedClass)
#endif

}