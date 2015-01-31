#pragma once

#include "IProperties.h"
#include "ISprite.h"
#include "IPhysShape.h"

namespace EngineInterface
{
	class IBaluInstance;
	class IBaluPhysShapeInstance;
	class ISensorInstance;
}

enum TKey :int
{
	Left,
	Right,
	Up,
	Down
};

typedef void(*KeyUpDownCallback)(EngineInterface::IBaluInstance* object);

typedef void(*BeforePhysicsCallback)(EngineInterface::IBaluInstance* object);
typedef void(*SensorCollideCallback)(EngineInterface::IBaluInstance* source, EngineInterface::ISensorInstance* sensor, EngineInterface::IBaluInstance* obstacle, EngineInterface::IBaluPhysShapeInstance* obstacle_shape);

enum TPhysBodyType
{
	Static,
	Dynamic,
	Kinematic
};

namespace EngineInterface
{

	

	class IBaluClassSprite
	{
	public:
	};

	class IBone
	{
	public:
		virtual void SetTransform(TBaluTransform)=0;
	};

	class ISkin
	{
	public:
		virtual void SetBoneSprite(int bone_index, IBaluSprite* sprite, TBaluTransform global)=0;
	};

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

	class ITrackFrame
	{
	public:
	};

	class ITrack
	{
	public:
		virtual ITrackFrame* CreateFrame(float time, float rotation)=0;
	};

	class ITimeLine
	{
	public:
		virtual ITrack* CreateTrack(IBone* bone)=0;
		virtual void DestroyTrack(ITrack* track) = 0;
		virtual void SetTimelineSize(float size) = 0;
	};

	class ISkeletonAnimation
	{
	public:
		virtual ITimeLine* CreateAnimation(std::string name)=0;
	};

	class  ISensor
	{
	public:
		virtual ~ISensor() {}
	};

	class IBaluClassPhysBody
	{
	public:
		virtual int GetSensorsCount() = 0;
		virtual ISensor* GetSensor(int index) = 0;
		virtual void SetFixedRotation(bool fixed) = 0;
		virtual void SetPhysBodyType(TPhysBodyType type) = 0;
		virtual void Enable(bool enable) = 0;
		virtual bool IsEnable() = 0;
		virtual ISensor* CreateSensor(IBaluPhysShape* shape) = 0;
	};

	class IBaluClass
	{
	public:
		virtual IBaluClassSprite* AddSprite(IBaluSprite* sprite)=0;

		virtual int GetSpritesCount() = 0;
		virtual IBaluClassSprite* GetSprite(int index) = 0;
		virtual ISkeletonAnimation* GetSkeletonAnimation() = 0;
		virtual IBaluClassPhysBody* GetPhysBody()=0;
		virtual ISkeleton* GetSkeleton()=0;

		virtual void OnKeyDown(TKey key, KeyUpDownCallback callback) = 0;
		virtual void OnKeyUp(TKey key, KeyUpDownCallback callback) = 0;

		virtual void OnBeforePhysicsStep(BeforePhysicsCallback callback) = 0;
		virtual void OnBeginContact(ISensor* sensor, SensorCollideCallback callback) = 0;
		virtual void OnEndContact(ISensor* sensor, SensorCollideCallback callback) = 0;
	};
}