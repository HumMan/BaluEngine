#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			class TPhysShape : public IPhysShape, public TChangeListenerArray
			{
			protected:
				TTransformWithScale local;
				bool is_sensor;
			public:
				TPhysShape()
				{
					is_sensor = false;
				}
				virtual ~TPhysShape() {}
				//virtual b2Shape* GetShape(TTransformWithScale class_transform) = 0;
				void SetTransform(TTransform local)
				{
					this->local.transform = local;
				}
				void SetScale(BaluLib::TVec2 scale)
				{
					this->local.scale = scale;
				}
				void SetIsSensor(bool value)
				{
					is_sensor = value;
				}
				bool IsSensor()
				{
					return is_sensor;
				}
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

			class TBaluPolygonShape : public TPhysShape, public IPolygonShape
			{
			protected:
				//b2PolygonShape b2shape;
			public:
				TBaluPolygonShape()
				{
				}
				static TPhysShape* Clone()
				{
					return new TBaluPolygonShape();
				}
				//b2PolygonShape* GetShape(TTransformWithScale class_transform);
				TPhysShape* GetPhysShape();
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
			static bool TBaluPolygonShape_registered = PhysShapeFactory::Register("PolygonShape", TBaluPolygonShape::Clone);

			class TBaluCircleShape : public TPhysShape, public ICircleShape
			{
			private:
				//b2CircleShape b2shape;
			public:
				TBaluCircleShape()
				{
				}
				static TPhysShape* Clone()
				{
					return new TBaluCircleShape();
				}
				TBaluCircleShape(float radius);
				TBaluCircleShape(float radius, BaluLib::TVec2 pos);
				//b2CircleShape* GetShape(TTransformWithScale class_transform);
				TPhysShape* GetPhysShape();
				void Save(pugi::xml_node& parent_node, const int version)const;
				void Load(const pugi::xml_node& instance_node, const int version, IWorld* world);
			};
			static bool TBaluCircleShape_registered = PhysShapeFactory::Register("CircleShape", TBaluCircleShape::Clone);

			class TBaluBoxShape : public TBaluPolygonShape, public IBoxShape
			{
				float width, height;
			public:
				TBaluBoxShape()
				{
				}
				static TPhysShape* Clone()
				{
					return new TBaluBoxShape();
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
				TBaluCircleShape* CreateCircleShape(float radius);
				TBaluCircleShape* CreateCircleShape(float radius, BaluLib::TVec2 pos);
				TBaluBoxShape* CreateBoxShape(float width, float height);
			};
		}
	}
}
