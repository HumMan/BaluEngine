#pragma once

#include "../../Interface.h"

#include "../Common/Common.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			class TPhysShape : public TProperties, public virtual IPhysShape
			{
			protected:
				void InitAllProperties()
				{
					InitProperty_Local();
					InitProperty_IsSensor();
				}
			public:

				TPhysShape();

				BALU_ENGINE_REGISTER_PROPERTY(Local, PropertyType::TransformWithScale, TTransformWithScale())
				BALU_ENGINE_REGISTER_PROPERTY(IsSensor, PropertyType::Bool, false)

				virtual ~TPhysShape() {}
				//virtual b2Shape* GetShape(TTransformWithScale class_transform) = 0;
				//virtual TPhysShape* GetPhysShape() = 0;
			};


			typedef TPhysShape*(*PhysShapeClone)();
			class PhysShapeFactory
			{
			public:
				static bool Register(const char* name, PhysShapeClone clone);
				static TPhysShape* Create(const char* name);
				static void UnregisterAll();
			};

			class TBaluPolygonShape : public TPhysShape, public virtual IPolygonShape
			{
			protected:
				std::vector<BaluLib::TVec2> vertices;
			public:
				TBaluPolygonShape()
				{
				}
				static TPhysShape* Clone()
				{
					return new TBaluPolygonShape();
				}
				void Accept(IPhysShapeVisitor* visitor)
				{
					visitor->Visit(this);
				}
				std::vector<BaluLib::TVec2> GetVertices()const
				{
					return vertices;
				}
				//b2PolygonShape* GetShape(TTransformWithScale class_transform);
				TPhysShape* GetPhysShape();
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
			static bool TBaluPolygonShape_registered = PhysShapeFactory::Register("PolygonShape", TBaluPolygonShape::Clone);

			class TBaluCircleShape : public TPhysShape, public ICircleShape
			{
			protected:
				void InitAllProperties()
				{
					InitProperty_Radius();
				}
			public:

				BALU_ENGINE_REGISTER_PROPERTY(Radius, PropertyType::Float, 1)

				TBaluCircleShape()
				{
					InitAllProperties();
				}
				static TPhysShape* Clone()
				{
					return new TBaluCircleShape();
				}
				void Accept(IPhysShapeVisitor* visitor)
				{
					visitor->Visit(this);
				}
				TBaluCircleShape(float radius, BaluLib::TVec2 pos);
				//b2CircleShape* GetShape(TTransformWithScale class_transform);
				TPhysShape* GetPhysShape();
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
			static bool TBaluCircleShape_registered = PhysShapeFactory::Register("CircleShape", TBaluCircleShape::Clone);

			class TBaluBoxShape : public TPhysShape, public IBoxShape
			{
			protected:
				void InitAllProperties()
				{
					InitProperty_Width();
					InitProperty_Height();
				}
			public:
				BALU_ENGINE_REGISTER_PROPERTY(Width, PropertyType::Float, 1)
				BALU_ENGINE_REGISTER_PROPERTY(Height, PropertyType::Float, 1)

				TBaluBoxShape()
				{
					InitAllProperties();
				}
				static TPhysShape* Clone()
				{
					return new TBaluBoxShape();
				}
				void Accept(IPhysShapeVisitor* visitor)
				{
					visitor->Visit(this);
				}
				TBaluBoxShape(float width, float height);
				//b2PolygonShape* GetShape(TTransformWithScale class_transform);
				TPhysShape* GetPhysShape();
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
			static bool TBaluBoxShape_registered = PhysShapeFactory::Register("BoxShape", TBaluBoxShape::Clone);

			class TPhysShapeFactory : public IPhysShapeFactory
			{
			public:
				TBaluPolygonShape * CreatePolygonShape();
				TBaluCircleShape* CreateCircleShape(float radius, BaluLib::TVec2 pos);
				TBaluBoxShape* CreateBoxShape(float width, float height);
			};
		}
	}
}
