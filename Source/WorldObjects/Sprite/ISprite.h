
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "../../World/ICallbacks.h"
#include "IPhysShape.h"
#include "ISpritePolygon.h"
#endif

namespace EngineInterface
{
	class IBaluPhysShapeInstance;
	class IBaluClass;
}

#include <string>
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluSprite
	{
	public:
		static std::string GetDefaultName()
		{
			return "sprite";
		}
		virtual std::string GetName() = 0;
		virtual void SetName(std::string name) = 0;
		virtual void SetPhysShape(IBaluPhysShape* shape) = 0;
		virtual IBaluPhysShape* GetPhysShape() = 0;
		virtual void SetPhysShapeFromGeometry() = 0;
		virtual IBaluSpritePolygon* GetPolygon() = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
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
		TBaluSprite();

		std::string GetName();
		void SetName(std::string name);

		void SetPhysShape(TBaluPhysShape* shape);
		void SetPhysShape(IBaluPhysShape* shape);

		TBaluPhysShape* GetPhysShape();
		void SetPhysShapeFromGeometry();

		TBaluSpritePolygon* GetPolygon();

		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);

		IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IBaluSceneInstance* editor_scene_instance);
};
#endif
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSprite, "ISprite");
	MUnpackA1(TYPE, SetPhysShape, WrapInterface<IBaluPhysShape>);
	MUnpackRA0(WrapPointer<IBaluPhysShape>, TYPE, GetPhysShape);
	MUnpackRA0(WrapPointer<IBaluSpritePolygon>, TYPE, GetPolygon);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluClassSpriteInstance
	{
	public:
		virtual IBaluSprite* GetSprite() = 0;
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual TVec2 GetScale() = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBaluClassSpriteInstance : public IBaluClassSpriteInstance
	{
		TBaluSprite* sprite;
		TBaluTransformWithScale local;
	public:
		TBaluSprite* GetSprite()
		{
			return sprite;
		}
		TBaluClassSpriteInstance()
		{
			sprite = nullptr;
		}
		TBaluClassSpriteInstance(TBaluSprite* sprite)
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
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluClassSpriteInstance, "IClassSpriteInstance");
	MUnpackRA0(WrapPointer<IBaluSprite>, TYPE, GetSprite);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}