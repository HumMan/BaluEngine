#pragma once

#include "IClass.h"
#include "../Sprite/ISpriteInstance.h"

#include "ISkeletonAnimationInstance.h"

namespace EngineInterface
{

	class IBaluClassPhysBodyIntance
	{
	public:
		virtual TVec2 GetLinearVelocity() = 0;
		virtual void SetLinearVelocity(TVec2 velocity) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluInstance;

	class TBaluClassPhysBodyIntance : public IBaluClassPhysBodyIntance
	{
	private:
		b2Body* phys_body;
		TBaluClassPhysBody* source;
		b2World* phys_world;
		TBaluInstance* parent;

		TBaluTransform local;

		bool is_enable;

	public:
		TBaluClassPhysBodyIntance(b2World* phys_world, TBaluClassPhysBody* source, TBaluInstance* parent);

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


	class IBaluClassInstance
	{
	public:
		virtual IBaluClass* GetClass() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	struct TSpriteWithClassCollideInstance
	{
		IBaluSprite* sprite;
		IBaluClass* with_class;
		TScriptInstance script;
		TSpriteWithClassCollideInstance()
		{
			sprite = nullptr;
			with_class = nullptr;
		}
		TSpriteWithClassCollideInstance(IBaluSprite* sprite, IBaluClass* with_class, TScriptInstance script)
		{
			this->sprite = sprite;
			this->with_class = with_class;
			this->script = script;
		}
	};

	class TBaluInstance;
	class TBaluWorldInstance;
	class TBaluScriptInstance;
	class TBaluPhysShapeInstance;

	class TBaluClassCompiledScripts :public IBaluClassInstance
	{
	private:
		TBaluWorldInstance* world_instance;
		TBaluClass* source;

		std::vector<std::pair<TKey, TScriptInstance>> on_key_down_callbacks;
		std::vector<std::pair<TKey, TScriptInstance>> on_key_up_callbacks;
		std::vector<TScriptInstance> before_physics_callbacks;
		std::vector<TSpriteWithClassCollideInstance> on_collide_callbacks;
	public:
		TBaluClassCompiledScripts(TBaluWorldInstance* world_instance, TBaluClass* source);
		TBaluClass* GetClass()
		{
			return source;
		}
		void CompileScripts();
		static void CheckScriptErrors(TBaluClass* source, TBaluScriptInstance* script_engine, std::vector<std::string>& errors_list);

		void DoKeyDown(TKey key, TBaluInstance* instance);
		void DoKeyUp(TKey key, TBaluInstance* instance);
		void DoBeforePhysicsStep(TBaluInstance* instance);
		void DoCollide(TBaluPhysShapeInstance* obj_a, TBaluInstance* obstancle);
		//void DoSensorCollide(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
		//void DoBeginContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
		//void DoEndContact(TSensorInstance* sensor, TBaluInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
	};
#endif

#ifdef BALUENGINEDLL_EXPORTS

	class IScriptsCache
	{
	public:
		virtual TBaluClassCompiledScripts* GetClassCompiled(TBaluClass* source) = 0;
	};

	class TBaluClassInstance
	{
		TBaluClass* source;
		TBaluClassCompiledScripts* scripts_cache;
	public:
		TBaluClassInstance(TBaluClass* source, IScriptsCache* cache);
	};

#endif

	class IBaluInstance
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
		virtual IBaluTransformedSpriteInstance* AddSprite(IBaluTransformedSprite* source) = 0;
		virtual IProperties* GetProperties() = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
		virtual bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result) = 0;
		virtual void SetTag(void* tag) = 0;
		virtual void* GetTag() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS

	class TBaluTransformedClass;

	class TBaluInstance : public IBaluInstance, public TSceneObjectInstance
	{
	private:
		int uid;
		TBaluClassCompiledScripts* instance_class;
		TBaluTransformWithScale instance_transform;

		std::vector<std::unique_ptr<TBaluTransformedSpriteInstance>> sprites;
		std::unique_ptr<TBaluClassPhysBodyIntance> phys_body;
		TSkeletonInstance skeleton;
		TSkeletonAnimationInstance skeleton_animation;

		TProperties properties;

		void* tag;
	public:
		static const char* FactoryName()
		{
			return "ClassInstance";
		}
		const char* GetFactoryName()
		{
			return FactoryName();
		}
		TBaluClassCompiledScripts* GetClass();
		void SetTag(void* tag)
		{
			this->tag = tag;
		}
		void* GetTag()
		{
			return tag;
		}
		TBaluInstance(TBaluTransformedClass* source, TBaluSceneInstance* scene);
		TBaluInstance(TBaluClass* source, TBaluTransform transform, TVec2 scale, TBaluSceneInstance* scene);
		void SetTransform(TBaluTransform transform);
		TBaluTransform GetTransform();
		TVec2 GetScale();
		void SetScale(TVec2 scale);
		TProperties* GetProperties();

		TBaluClassPhysBodyIntance* GetPhysBody();

		int GetSpritesCount();
		IBaluTransformedSpriteInstance* GetSprite(int index);
		IBaluTransformedSpriteInstance* AddSprite(IBaluTransformedSprite* source);

		TSkeletonAnimationInstance* GetSkeletonAnimation();

		bool PointCollide(TVec2 class_space_point, IBaluTransformedSpriteInstance* &result);
		bool PointCollide(TVec2 scene_space_point);
		TOBB2 GetOBB();
		TAABB2 GetAABB();
		void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);

		void UpdateTransform();
		static TSceneObjectInstance* Clone(TSceneObject* source, TBaluSceneInstance* scene);
};

	REGISTER_FACTORY_CLASS(SceneObjectInstanceFactory, TBaluInstance);
#endif

}