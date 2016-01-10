#pragma once

#include "IClass.h"
#include "../Sprite/ISpriteInstance.h"

#include "ISkeletonAnimationInstance.h"

namespace EngineInterface
{
	class TBaluTransformedClassInstance;
	class TBaluWorldInstance;
	class TBaluScriptInstance;
	class TBaluPhysShapeInstance;
	class TBaluClassCompiledScripts;
	class IBaluScriptsCache;
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

	class TBaluClassPhysBodyIntance : public IBaluClassPhysBodyIntance
	{
	private:
		b2Body* phys_body;
		TBaluClassPhysBody* source;
		b2World* phys_world;
		ISpritesArray* sprites;

		TBaluTransform local;

		bool is_enable;

	public:
		TBaluClassPhysBodyIntance(b2World* phys_world, TBaluClassPhysBody* source, ISpritesArray* sprites, TBaluTransform parent_transform);

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
		virtual TBaluClassCompiledScripts* GetClassCompiled(TBaluClass* source) = 0;
	};

#endif
	class TBaluClass;
	class IBaluClassInstance: public ISpritesArray
	{
	public:
		virtual TBaluClass* GetSource() = 0;
		virtual int GetSpritesCount() = 0;
		virtual IBaluTransformedSpriteInstance* GetSprite(int index) = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
		virtual bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result) = 0;
	};

	

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluClassInstance :public IBaluClassInstance
	{
	private:
		TBaluClass* source;
		TSceneObjectInstance* scene_object;
		TResources* resources;

		std::vector<std::unique_ptr<TBaluTransformedSpriteInstance>> sprites;
		std::unique_ptr<TBaluClassPhysBodyIntance> phys_body;
		TSkeletonInstance skeleton;
		TSkeletonAnimationInstance skeleton_animation;

		TProperties properties;
		void BuildAllFixtures();
	public:
		TBaluClassInstance(TBaluClass* source, b2World* phys_world, TBaluTransform parent_transform, TResources* resources, TSceneObjectInstance* scene_object);
		TBaluClass* GetSource();
		int GetSpritesCount();
		IBaluTransformedSpriteInstance* GetSprite(int index);
		TSkeletonAnimationInstance* GetSkeletonAnimation();
		TBaluClassPhysBodyIntance* GetPhysBody();
		bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result);
		void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);

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
		TBaluClassInstance instance_class;
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
		TBaluClassInstance* GetClass();
		TSceneObject* GetSource()
		{
			return source;
		}
		TBaluTransformedClassInstance(TBaluTransformedClass* source, TBaluSceneInstance* scene);
		~TBaluTransformedClassInstance();
		void SetTransform(TBaluTransform transform);
		TBaluTransform GetTransform();
		TVec2 GetScale();
		void SetScale(TVec2 scale);
		TProperties* GetProperties();

		TBaluClassPhysBodyIntance* GetPhysBody();

		int GetSpritesCount();
		IBaluTransformedSpriteInstance* GetSprite(int index);

		TSkeletonAnimationInstance* GetSkeletonAnimation();

		bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result);
		bool PointCollide(TVec2 scene_space_point);
		TOBB2 GetOBB();
		TAABB2 GetAABB();
		void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);

		void UpdateTransform();
		static TSceneObjectInstance* Clone(TSceneObject* source, TBaluSceneInstance* scene);
};

	REGISTER_FACTORY_CLASS(SceneObjectInstanceFactory, TBaluTransformedClassInstance);
#endif

}