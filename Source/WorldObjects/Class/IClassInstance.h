
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#if !defined(BALU_ENGINE_SCRIPT_CLASSES)  && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)
#include "IClass.h"
#include "../Sprite/ISpriteInstance.h"
#include "../Material/IMaterialInstance.h"
#endif

namespace EngineInterface
{
#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassPhysBodyIntance
	{
	public:
		virtual TVec2 GetLinearVelocity() = 0;
		virtual void SetLinearVelocity(TVec2 velocity) = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
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
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluClassPhysBodyIntance, "IClassPhysBodyInstance");
	MUnpackRA0(WrapValue<TVec2>, TYPE, GetLinearVelocity);
	MUnpackA1(TYPE, SetLinearVelocity, WrapValue<TVec2>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ISkeletonAnimationInstance
	{
	public:
		virtual void Update(float step) = 0;
		virtual void PlayAnimation(std::string name, float alpha) = 0;
		virtual void StopAnimation(std::string name) = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBoneInstance;

	class TTrackInstance
	{
	private:
		TBoneInstance* bone;
		TTrack* source;
		//std::set<TTrackFrame, TFrameComparer> frames;
	public:
		TTrackInstance(TBoneInstance* bone, TTrack* source);
		void Update(float time, float timeline_size);
	};

	class TSkeletonInstance;

	class TTimeLineInstance
	{
	private:
		TTimeLine* source;

		std::vector<std::unique_ptr<TTrackInstance>> tracks;
		float current_time;
		//float alpha;
		float active_alpha;
		//bool smooth_stop_active;
		bool loop;
		bool is_active;
	public:
		TTimeLineInstance(TSkeletonInstance* skeleton, TTimeLine* source);
		void SetAlpha();
		bool IsActive();
		void PlayOnce();
		void PlayLoop();
		void Stop();
		//void SmoothStop();
		void Step(float step);
		TTimeLine* GetSource();
	};

	class TSkeletonAnimationInstance: public ISkeletonAnimationInstance
	{
	private:
		TSkeletonAnimation* source;
		TSkeletonInstance* skeleton;

		std::vector<std::unique_ptr<TTimeLineInstance>> animations;
	public:
		TSkeletonAnimationInstance(TSkeletonInstance* skeleton, TSkeletonAnimation* source);
		void Init();
		void Update(float step);
		void PlayAnimation(std::string name, float alpha);
		void StopAnimation(std::string name);
};
#endif
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, ISkeletonAnimationInstance, "ISkeletonAnimationInstance");
	MUnpackA2(TYPE, PlayAnimation, TStringWrapper<std::string>, WrapValue<float>);
	MUnpackA1(TYPE, StopAnimation, TStringWrapper<std::string>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassInstance
	{
	public:
		virtual IBaluClass* GetClass() = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
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

	class TBaluClassInstance :public IBaluClassInstance
	{
	private:
		TBaluWorldInstance* world_instance;
		TBaluClass* source;

		std::vector<std::pair<TKey, TScriptInstance>> on_key_down_callbacks;
		std::vector<std::pair<TKey, TScriptInstance>> on_key_up_callbacks;
		std::vector<TScriptInstance> before_physics_callbacks;
		std::vector<TSpriteWithClassCollideInstance> on_collide_callbacks;
	public:
		TBaluClassInstance(TBaluWorldInstance* world_instance, TBaluClass* source);
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
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassInstanceSpriteInstance;
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
		virtual IBaluClassInstanceSpriteInstance* GetSprite(int index) = 0;
		virtual IBaluClassInstanceSpriteInstance* AddSprite(IBaluClassSpriteInstance* source) = 0;
		virtual IProperties* GetProperties() = 0;
		virtual IBaluClassPhysBodyIntance* GetPhysBody() = 0;
		virtual ISkeletonAnimationInstance* GetSkeletonAnimation() = 0;
		virtual bool PointCollide(TVec2 class_space_point, IBaluClassInstanceSpriteInstance* &result) = 0;
		virtual void SetTag(void* tag) = 0;
		virtual void* GetTag() = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBoneInstance
	{
	private:
		TBoneInstance* parent;
		std::vector<std::unique_ptr<TBoneInstance>> children;

		TBone* source;

		//float rotation_amount;

		//TVec2 current_position;
		float current_rotation;

		TBaluTransform global;
	public:
		TBoneInstance(TBoneInstance* parent, TBone* source);
		int GetChildrenCount();
		TBoneInstance* GetChild(int index);

		void SetRotationAmount(float amount);

		TBone* GetSourceBone();

		void UpdateTranform(TBaluTransform parent);
		TBaluTransform GetGlobalTransform();
	};

	class TBaluClassInstanceSpriteInstance;
	class TResources;

	class TSkinInstance
	{
	private:
		std::vector<std::vector<std::unique_ptr<TBaluClassInstanceSpriteInstance>>> sprites_of_bones;
	public:
		TSkinInstance(TSkin* source, TBaluInstance* parent, TResources* resources);
		void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);
		void UpdateSpritesTransform(std::vector<TBoneInstance*> bones, TBaluTransformWithScale class_transform);
	};

	class TSkeletonInstance
	{
	private:
		std::unique_ptr<TBoneInstance> root;
		std::vector<TBoneInstance*> bones;
		std::vector<std::unique_ptr<TSkinInstance>> skins;

		TSkeleton* source;
	public:
		TSkeletonInstance(TSkeleton* source, TBaluInstance* parent, TResources* resources);
		void UpdateTranform(TBaluTransformWithScale class_transform);
		void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);
		TSkeleton* GetSource();
		TBoneInstance* GetBone(int index);
	};

	class TBaluSceneClassInstance;

	class TBaluInstance : public IBaluInstance, public TSceneObjectInstance
	{
	private:
		int uid;
		TBaluClassInstance* instance_class;
		TBaluTransformWithScale instance_transform;

		//b2World* phys_world;

		TBaluSceneInstance* scene;

		std::vector<std::unique_ptr<TBaluClassInstanceSpriteInstance>> sprites;
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
		TBaluClassInstance* GetClass();
		void SetTag(void* tag)
		{
			this->tag = tag;
		}
		void* GetTag()
		{
			return tag;
		}
		TBaluInstance(TBaluSceneClassInstance* source, TBaluSceneInstance* scene);
		TBaluInstance(TBaluClass* source, TBaluTransform transform, TVec2 scale, TBaluSceneInstance* scene);
		void SetTransform(TBaluTransform transform);
		TBaluTransform GetTransform();
		TVec2 GetScale();
		void SetScale(TVec2 scale);
		TProperties* GetProperties();

		TBaluClassPhysBodyIntance* GetPhysBody();

		int GetSpritesCount();
		IBaluClassInstanceSpriteInstance* GetSprite(int index);
		IBaluClassInstanceSpriteInstance* AddSprite(IBaluClassSpriteInstance* source);

		TSkeletonAnimationInstance* GetSkeletonAnimation();

		bool PointCollide(TVec2 class_space_point, IBaluClassInstanceSpriteInstance* &result);
		bool PointCollide(TVec2 scene_space_point);
		TOBB2 GetOBB();
		TAABB2 GetAABB();
		void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);

		void UpdateTransform();
		static TSceneObjectInstance* Clone(TSceneObject* source, TBaluSceneInstance* scene);
};

	REGISTER_FACTORY_CLASS(SceneObjectInstanceFactory, TBaluInstance)
#endif
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluInstance, "IInstance");
	MUnpackA1(TYPE, SetScale, WrapValue<TVec2>);
	MUnpackRA0(WrapPointer<IProperties>, TYPE, GetProperties);
	MUnpackRA0(WrapPointer<IBaluClassPhysBodyIntance>, TYPE, GetPhysBody);
	MUnpackRA1(WrapPointer<IBaluClassInstanceSpriteInstance>, TYPE, GetSprite, WrapValue<int>);
	MUnpackRA0(WrapPointer<ISkeletonAnimationInstance>, TYPE, GetSkeletonAnimation);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}