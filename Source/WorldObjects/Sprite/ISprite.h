#pragma once

#include "../../World/ICallbacks.h"
#include "IPhysShape.h"
#include "ISpritePolygon.h"

namespace EngineInterface
{
	class IBaluPhysShapeInstance;
	class IBaluClass;
}

#include <string>

namespace EngineInterface
{
	class IBaluSprite : public virtual IBaluWorldObject
	{
	public:
		static std::string GetDefaultName()
		{
			return "sprite";
		}
		virtual void SetPhysShape(IBaluPhysShape* shape) = 0;
		virtual IBaluPhysShape* GetPhysShape() = 0;
		virtual void SetPhysShapeFromGeometry() = 0;
		virtual IBaluSpritePolygon* GetPolygon() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluSprite :public IBaluSprite, public TBaluWorldObject
	{
	private:
		TBaluWorld* world;
		std::string sprite_name;

		TBaluSpritePolygon sprite_polygon;
		std::unique_ptr<TBaluPhysShape> phys_shape;

		int layer;
		TProperties properties;


	public:
		TBaluSprite(const char* name, TBaluWorld* world);

		IProperties* GetProperties();

		void SetPhysShape(TBaluPhysShape* shape);
		void SetPhysShape(IBaluPhysShape* shape);

		TBaluPhysShape* GetPhysShape();
		void SetPhysShapeFromGeometry();

		TBaluSpritePolygon* GetPolygon();

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);

		IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IBaluWorldInstance* world_instance);
	};
#endif

	class IBaluTransformedSprite
	{
	public:
		virtual IBaluSprite* GetSprite() = 0;
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual TVec2 GetScale() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluTransformedSprite : public IBaluTransformedSprite
	{
		TBaluSprite* sprite;
		TBaluTransformWithScale local;
	public:
		TBaluSprite* GetSprite()
		{
			return sprite;
		}
		TBaluTransformedSprite()
		{
			sprite = nullptr;
		}
		TBaluTransformedSprite(TBaluSprite* sprite)
		{
			this->sprite = sprite;
		}
		void SetTransform(TBaluTransform transform)
		{
			this->local.transform = transform;
		}
		void SetScale(TVec2 scale)
		{
			this->local.scale = scale;
		}
		TBaluTransformWithScale GetTransformWithScale()
		{
			return local;
		}
		TBaluTransform GetTransform()
		{
			return local.transform;
		}
		TVec2 GetScale()
		{
			return local.scale;
		}
		bool PointCollide(TVec2 class_space_point)
		{
			TVec2 p = local.ToLocal(class_space_point);
			bool is_in_sprite = GetSprite()->GetPolygon()->PointCollide(p);
			return (is_in_sprite);
		}
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
#endif

}