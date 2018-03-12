#pragma once

#include "../Interfaces/ExportMacro.h"

namespace BaluEngine
{
	namespace WorldDef
	{

		class IPhysShapeVisitor;

		class IPhysShape: public ISerializable, public virtual IProperties
		{
		public:
			BALU_ENGINE_VPROPERTY(Local, TTransformWithScale)
			BALU_ENGINE_VPROPERTY(IsSensor, bool)

			virtual ~IPhysShape() {}

			virtual void Accept(IPhysShapeVisitor* visitor) = 0;
		};

		class IPolygonShape: public virtual IPhysShape
		{
		public:
			virtual IPhysShape* GetPhysShape() = 0;
			virtual std::vector<BaluLib::TVec2> GetVertices()const = 0;
		};

		class ICircleShape : public virtual IPhysShape
		{
		public:
			BALU_ENGINE_VPROPERTY(Radius, float)

			virtual IPhysShape* GetPhysShape() = 0;
		};

		class IBoxShape : public virtual IPhysShape
		{
		public:
			BALU_ENGINE_VPROPERTY(Width, float)
			BALU_ENGINE_VPROPERTY(Height, float)

			virtual IPhysShape* GetPhysShape() = 0;
		};

		class IPhysShapeVisitor
		{
		public:
			virtual void Visit(IPolygonShape* shape) = 0;
			virtual void Visit(ICircleShape* shape) = 0;
			virtual void Visit(IBoxShape* shape) = 0;
		};

		class IPhysShapeFactory
		{
		public:
			virtual IPolygonShape* CreatePolygonShape() = 0;
			virtual ICircleShape* CreateCircleShape(float radius, BaluLib::TVec2 pos) = 0;
			virtual IBoxShape* CreateBoxShape(float width, float height) = 0;
		};

		BALUENGINEDLL_API IPhysShapeFactory* GetPhysShapeFactory();
	}
}
