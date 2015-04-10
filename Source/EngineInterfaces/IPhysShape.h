
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
#include "../../BaluLib/Source/Math/vec.h"
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluPhysShape
	{
	public:
		virtual void SetIsSensor(bool value)=0;
		virtual bool IsSensor()=0;
		virtual ~IBaluPhysShape(){};
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluPhysShape, "IPhysShape");
	MUnpackA1(TYPE, SetIsSensor, WrapValue<bool>);
	MUnpackRA0(WrapValue<bool>, TYPE, IsSensor);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluPolygonShape
	{
	public:
		virtual IBaluPhysShape* GetPhysShape() = 0;
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluCircleShape
	{
	public:
		virtual IBaluPhysShape* GetPhysShape() = 0;
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluBoxShape
	{
	public:
		virtual IBaluPhysShape* GetPhysShape() = 0;
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluPhysShapeFactory
	{
	public:
		virtual IBaluPolygonShape* CreatePolygonShape() = 0;
		virtual IBaluCircleShape* CreateCircleShape(float radius) = 0;
		virtual IBaluCircleShape* CreateCircleShape(float radius, TVec2 pos) = 0;
		virtual IBaluBoxShape* CreateBoxShape(float width, float height) = 0;
	};
#endif

}