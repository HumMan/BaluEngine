#pragma once

namespace EngineInterface
{
	class IBaluPhysShape
	{
	public:
	};

	class IBaluPolygonShape
	{
	public:
	};

	class IBaluCircleShape
	{
	public:
	};

	class IBaluBoxShape
	{
	public:
	};

	class IBaluPhysShapeFactory
	{
	public:
		virtual IBaluPolygonShape* CreatePolygonShape() = 0;
		virtual IBaluCircleShape* CreateCircleShape() = 0;
		virtual IBaluBoxShape* CreateBoxShape() = 0;
	};
}