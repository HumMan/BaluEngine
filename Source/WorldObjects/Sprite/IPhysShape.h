#pragma once

#include <Common/ICommon.h>

#ifdef BALUENGINEDLL_EXPORTS
#include <Box2D.h>
#endif

#include <Interfaces/ExportMacro.h>

namespace EngineInterface
{

	class IBaluPhysShape
	{
	public:
		virtual void SetIsSensor(bool value)=0;
		virtual bool IsSensor()=0;
		virtual ~IBaluPhysShape(){};
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluPhysShape: public IBaluPhysShape, public TChangeListenerArray
	{
	protected:
		TBaluTransformWithScale local;
		bool is_sensor;
	public:
		TBaluPhysShape()
		{
			is_sensor = false;
		}
		virtual ~TBaluPhysShape(){}
		virtual b2Shape* GetShape(TBaluTransformWithScale class_transform) = 0;
		void SetTransform(TBaluTransform local)
		{
			this->local.transform = local;
		}
		void SetScale(TVec2 scale)
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
		//virtual TBaluPhysShape* GetPhysShape() = 0;
		virtual void Save(pugi::xml_node& parent_node, const int version) = 0;
		virtual void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world) = 0;
	};


	typedef TBaluPhysShape*(*PhysShapeClone)();
	class PhysShapeFactory
	{
	public:
		static bool Register(const char* name, PhysShapeClone clone);
		static TBaluPhysShape* Create(const char* name);
		static void UnregisterAll();
	};
#endif

	class IBaluPolygonShape
	{
	public:
		virtual IBaluPhysShape* GetPhysShape() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluPolygonShape : public TBaluPhysShape, public IBaluPolygonShape
	{
	protected:
		b2PolygonShape b2shape;
	public:
		TBaluPolygonShape()
		{
		}
		static TBaluPhysShape* Clone()
		{
			return new TBaluPolygonShape();
		}
		b2PolygonShape* GetShape(TBaluTransformWithScale class_transform);
		TBaluPhysShape* GetPhysShape();
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
	static bool TBaluPolygonShape_registered = PhysShapeFactory::Register("PolygonShape", TBaluPolygonShape::Clone);
#endif

	class IBaluCircleShape
	{
	public:
		virtual IBaluPhysShape* GetPhysShape() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluCircleShape : public TBaluPhysShape, public IBaluCircleShape
	{
	private:
		b2CircleShape b2shape;
	public:
		TBaluCircleShape()
		{
		}
		static TBaluPhysShape* Clone()
		{
			return new TBaluCircleShape();
		}
		TBaluCircleShape(float radius);
		TBaluCircleShape(float radius, TVec2 pos);
		b2CircleShape* GetShape(TBaluTransformWithScale class_transform);
		TBaluPhysShape* GetPhysShape();
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
	static bool TBaluCircleShape_registered = PhysShapeFactory::Register("CircleShape", TBaluCircleShape::Clone);
#endif

	class IBaluBoxShape
	{
	public:
		virtual IBaluPhysShape* GetPhysShape() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluBoxShape : public TBaluPolygonShape, public IBaluBoxShape
	{
		float width, height;
	public:
		TBaluBoxShape()
		{
		}
		static TBaluPhysShape* Clone()
		{
			return new TBaluBoxShape();
		}
		TBaluBoxShape(float width, float height);
		b2PolygonShape* GetShape(TBaluTransformWithScale class_transform);
		TBaluPhysShape* GetPhysShape();
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
	static bool TBaluBoxShape_registered = PhysShapeFactory::Register("BoxShape", TBaluBoxShape::Clone);
#endif

	class IBaluPhysShapeFactory
	{
	public:
		virtual IBaluPolygonShape* CreatePolygonShape() = 0;
		virtual IBaluCircleShape* CreateCircleShape(float radius) = 0;
		virtual IBaluCircleShape* CreateCircleShape(float radius, TVec2 pos) = 0;
		virtual IBaluBoxShape* CreateBoxShape(float width, float height) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluPhysShapeFactory : public IBaluPhysShapeFactory
	{
	public:
		TBaluPolygonShape* CreatePolygonShape();
		TBaluCircleShape* CreateCircleShape(float radius);
		TBaluCircleShape* CreateCircleShape(float radius, TVec2 pos);
		TBaluBoxShape* CreateBoxShape(float width, float height);
	};
#endif

	BALUENGINEDLL_API IBaluPhysShapeFactory* GetPhysShapeFactory();

}
