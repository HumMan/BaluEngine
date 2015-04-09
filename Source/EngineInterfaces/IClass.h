
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IProperties.h"
#include "ISprite.h"
#include "IPhysShape.h"
#endif

namespace EngineInterface
{
	class IBaluInstance;
	class IBaluPhysShapeInstance;
}
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	enum TKey :int
	{
		Left,
		Right,
		Up,
		Down
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	void TKey_register(TClassRegistryParams& params)
	{
		auto scl = RegisterEnum(params,
			"enum TKey\n"
			"{\n"
			"	Left,\n"
			"	Right,\n"
			"	Up,\n"
			"	Down,\n"
			"}\n");
	}
	static bool TKey_registered = TScriptClassesRegistry::RegisterEnum("TKey", TKey_register);
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	typedef void(*KeyUpDownCallback)(TCallbackData* data, EngineInterface::IBaluInstance* object);

	typedef void(*BeforePhysicsCallback)(TCallbackData* data, EngineInterface::IBaluInstance* object);
	

	enum TPhysBodyType
	{
		Static,
		Dynamic,
		Kinematic
	};
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassSprite
	{
	public:
	};
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBone
	{
	public:
		virtual void SetTransform(TBaluTransform)=0;
	};
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ISkin
	{
	public:
		virtual void SetBoneSprite(int bone_index, IBaluSprite* sprite, TBaluTransform global)=0;
	};
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ISkeleton
	{
	public:
		virtual ISkin* CreateSkin() = 0;
		virtual void DestroySkin(ISkin* skin) = 0;
		virtual int GetSkinsCount() = 0;
		virtual ISkin* GetSkin(int index) = 0;
		virtual IBone* CreateBone(IBone* parent) = 0;
		virtual void DestroyBone(IBone* bone) = 0;
		virtual int GetBoneIndex(IBone* bone) = 0;
		virtual IBone* GetRoot() = 0;
		//virtual std::vector<IBone*> GetAllBones() = 0;
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ITrackFrame
	{
	public:
	};
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ITrack
	{
	public:
		virtual ITrackFrame* CreateFrame(float time, float rotation)=0;
	};
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ITimeLine
	{
	public:
		virtual ITrack* CreateTrack(IBone* bone)=0;
		virtual void DestroyTrack(ITrack* track) = 0;
		virtual void SetTimelineSize(float size) = 0;
	};
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class ISkeletonAnimation
	{
	public:
		virtual ITimeLine* CreateAnimation(std::string name)=0;
	};
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassPhysBody
	{
	public:
		virtual void SetFixedRotation(bool fixed) = 0;
		virtual void SetPhysBodyType(TPhysBodyType type) = 0;
		virtual void Enable(bool enable) = 0;
		virtual bool IsEnable() = 0;
	};
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClass
	{
	public:
		virtual std::string GetName()=0;
		static std::string GetDefaultName()
		{
			return "class";
		}
		virtual TAABB2 GetAABB()=0;
		virtual IBaluClassSprite* AddSprite(IBaluSprite* sprite)=0;

		virtual int GetSpritesCount() = 0;
		virtual IBaluClassSprite* GetSprite(int index) = 0;
		virtual ISkeletonAnimation* GetSkeletonAnimation() = 0;
		virtual IBaluClassPhysBody* GetPhysBody()=0;
		virtual ISkeleton* GetSkeleton()=0;

		virtual void OnKeyDown(TKey key, CallbackWithData<KeyUpDownCallback> callback) = 0;
		virtual void OnKeyUp(TKey key, CallbackWithData<KeyUpDownCallback> callback) = 0;

		virtual void OnBeforePhysicsStep(CallbackWithData<BeforePhysicsCallback> callback) = 0;
	};
#endif
}