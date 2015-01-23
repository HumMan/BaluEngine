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

typedef void(*KeyDownCallback)(EngineInterface::IBaluInstance* object);
typedef void(*BeforePhysicsCallback)(EngineInterface::IBaluInstance* object);
typedef void(*SensorCollideCallback)(EngineInterface::IBaluInstance* source, EngineInterface::ISensorInstance* sensor, EngineInterface::IBaluInstance* obstacle, EngineInterface::IBaluPhysShapeInstance* obstacle_shape);

enum TKey :int
{
	Left,
	Right,
	Up,
	Down
};

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

	class ISkeletonAnimation
	{
	public:
	};

	class ISensor
	{
	public:

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

		virtual void OnKeyDown(TKey key, KeyDownCallback callback) = 0;
		virtual void OnBeforePhysicsStep(BeforePhysicsCallback callback) = 0;
		virtual void OnBeginContact(ISensor* sensor, SensorCollideCallback callback) = 0;
		virtual void OnEndContact(ISensor* sensor, SensorCollideCallback callback) = 0;
	};
}