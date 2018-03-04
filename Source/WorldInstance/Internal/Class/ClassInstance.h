#pragma once

#include <WorldDef/Objects/Class/IClass.h>
#include "../Sprite/ISpriteInstance.h"

#include "ISkeletonAnimationInstance.h"

namespace EngineInterface
{
	class TBaluTransformedClassInstance;
	class TBaluWorldInstance;
	class TBaluScriptInstance;
	class TBaluPhysShapeInstance;
	class TClassCompiledScripts;
	class TBaluTransformedClass;

	class ISpritesArray
	{
	public:
		virtual int GetSpritesCount() = 0;
		virtual IBaluTransformedSpriteInstance* GetSprite(int index) = 0;
	};

	class IBaluClassPhysBodyIntance
	{
	public:
		virtual TVec2 GetLinearVelocity() = 0;
		virtual void SetLinearVelocity(TVec2 velocity) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS

	class TClassPhysBodyIntance : public IBaluClassPhysBodyIntance
	{
	private:
		b2Body* phys_body;
		TClassPhysBody* source;
		b2World* phys_world;
		ISpritesArray* sprites;

		TBaluTransform local;

		bool is_enable;

	public:
		TClassPhysBodyIntance(b2World* phys_world, TClassPhysBody* source, ISpritesArray* sprites, TBaluTransform parent_transform);

		void BuildAllFixtures();

		bool IsEnable();
		b2BodyDef GetBodyDef();
		void SetFixedRotation(bool fixed);

		TVec2 GetLinearVelocity();
		void SetLinearVelocity(TVec2 velocity);

		float GetAngularVelocity();
		void SetAngularVelocity(float velocity);

		TBaluTransform GetTransform();
		void SetTransform(TBaluTransform transform);
};
#endif


#ifdef BALUENGINEDLL_EXPORTS

	class IScriptsCache
	{
	public:
		virtual TClassCompiledScripts* GetClassCompiled(TClass* source) = 0;
	};

#endif
	class TClass;
	class IBaluClassInstance: public ISpritesArray
	{
	public:
		virtual TClass* GetSource() = 0;
		virtual int GetSpritesCount() = 0;
		virtual IBaluTransformedSpriteInstance* GetSprite(int index) = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
		virtual bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result) = 0;
	};

	

#ifdef BALUENGINEDLL_EXPORTS
	class TClassInstance :public IBaluClassInstance
	{
	private:
		TClass* source;
		TSceneObjectInstance* scene_object;
		TResources* resources;

		std::vector<std::unique_ptr<TBaluTransformedSpriteInstance>> sprites;
		std::unique_ptr<TClassPhysBodyIntance> phys_body;
		TSkeletonInstance skeleton;
		TSkeletonAnimationInstance skeleton_animation;

		TProperties properties;
		void BuildAllFixtures();
	public:
		TClassInstance(TClass* source, b2World* phys_world, TBaluTransform parent_transform, TResources* resources, TSceneObjectInstance* scene_object);
		TClass* GetSource();
		int GetSpritesCount();
		IBaluTransformedSpriteInstance* GetSprite(int index);
		TSkeletonAnimationInstance* GetSkeletonAnimation();
		TClassPhysBodyIntance* GetPhysBody();
		bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result);
		void QueryAABB(TAABB2 frustum, std::vector<TSpritePolygonInstance*>& results);

		void UpdateTransform(TBaluTransformWithScale transform);
	};
#endif

	class IBaluTransformedClassInstance : public ISpritesArray
	{
	public:
		virtual void UpdateTransform() = 0;
		virtual TOBB2 GetOBB() = 0;
		virtual IBaluClassInstance* GetClass() = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual void SetTransform(TBaluTransform) = 0;
		virtual TVec2 GetScale() = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual int GetSpritesCount() = 0;
		virtual IBaluTransformedSpriteInstance* GetSprite(int index) = 0;
		virtual IProperties* GetProperties() = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
		virtual bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluTransformedClassInstance : public IBaluTransformedClassInstance, public TSceneObjectInstance, public IChangeListener
	{
	private:
		int uid;
		TClassInstance instance_class;
		TBaluTransformWithScale instance_transform;

		TProperties properties;

		TBaluTransformedClass* source;
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
		TSceneObject* GetSource()
		{
			return source;
		}
		TBaluTransformedClassInstance(TBaluTransformedClass* source, TSceneInstance* scene);
		~TBaluTransformedClassInstance();
		void SetTransform(TBaluTransform transform);
		TBaluTransform GetTransform();
		TVec2 GetScale();
		void SetScale(TVec2 scale);
		TProperties* GetProperties();

		TClassPhysBodyIntance* GetPhysBody();

		int GetSpritesCount();
		IBaluTransformedSpriteInstance* GetSprite(int index);

		TSkeletonAnimationInstance* GetSkeletonAnimation();

		bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result);
		bool PointCollide(TVec2 scene_space_point);
		TOBB2 GetOBB();
		TAABB2 GetAABB();
		void QueryAABB(TAABB2 frustum, std::vector<TSpritePolygonInstance*>& results);

		void UpdateTransform();
		static TSceneObjectInstance* Clone(TSceneObject* source, TSceneInstance* scene);
};

	REGISTER_FACTORY_CLASS(SceneObjectInstanceFactory, TBaluTransformedClassInstance);
#endif

}