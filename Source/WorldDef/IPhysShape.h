#pragma once

namespace BaluEngine
{
	namespace WorldDef
	{

		class IPhysShape: public ISerializable
		{
		public:
			virtual void SetIsSensor(bool value) = 0;
			virtual bool IsSensor() = 0;
			virtual ~IPhysShape() {};
		};

		class IPolygonShape
		{
		public:
			virtual IPhysShape* GetPhysShape() = 0;
		};

		class ICircleShape
		{
		public:
			virtual IPhysShape* GetPhysShape() = 0;
		};

		class IBoxShape
		{
		public:
			virtual IPhysShape* GetPhysShape() = 0;
		};

		class IPhysShapeFactory
		{
		public:
			virtual IPolygonShape* CreatePolygonShape() = 0;
			virtual ICircleShape* CreateCircleShape(float radius) = 0;
			virtual ICircleShape* CreateCircleShape(float radius, BaluLib::TVec2 pos) = 0;
			virtual IBoxShape* CreateBoxShape(float width, float height) = 0;
		};

		IPhysShapeFactory* GetPhysShapeFactory();
	}
}
