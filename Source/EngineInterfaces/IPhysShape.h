#pragma once

#include "../../BaluLib/Source/Math/vec.h"

namespace EngineInterface
{
	class IBaluPhysShape
	{
	public:
		virtual ~IBaluPhysShape(){};
	};

	class IBaluPolygonShape
	{
	public:
		virtual IBaluPhysShape* GetPhysShape() = 0;
	};

	class IBaluCircleShape
	{
	public:
		virtual IBaluPhysShape* GetPhysShape() = 0;
	};

	class IBaluBoxShape
	{
	public:
		virtual IBaluPhysShape* GetPhysShape() = 0;
	};

	class IBaluPhysShapeFactory
	{
	public:
		virtual IBaluPolygonShape* CreatePolygonShape() = 0;
		virtual IBaluCircleShape* CreateCircleShape(float radius) = 0;
		virtual IBaluCircleShape* CreateCircleShape(float radius, TVec2 pos) = 0;
		virtual IBaluBoxShape* CreateBoxShape(float width, float height) = 0;
	};
}