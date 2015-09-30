
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#if !defined(BALU_ENGINE_SCRIPT_CLASSES)  && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)
#include <baluLib.h>
#include <string>
#include "IProperties.h"
using namespace BaluLib;

namespace pugi
{
	class xml_node;
}

namespace EngineInterface
{
	class TScreen;
	class TView;
	class TBaluWorld;
}
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	enum class TMouseButton
	{
		Left,
		Right,
		Middle
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	void TMouseButton_register(TClassRegistryParams& params)
	{
		auto scl = RegisterEnum(params,
			"enum TMouseButton\n"
			"{\n"
			"	Left,\n"
			"	Right,\n"
			"	Middle,\n"
			"}\n");
	}
	static bool TMouseButton_registered = TScriptClassesRegistry::RegisterEnum("TMouseButton", TMouseButton_register);
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class TMouseEventArgs
	{
	public:
		TMouseButton button;
		TVec2i location;
		TMouseEventArgs(){}
		TMouseEventArgs(TMouseButton button, TVec2i location)
		{
			this->button = button;
			this->location = location;
		}
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, TMouseEventArgs, "TMouseEventArgs");
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	struct TRot
	{
		TRot() {}
		TRot(float s, float c)
		{
			this->s = s;
			this->c = c;
		}
		explicit TRot(float angle)
		{
			Set(angle);
		}
		explicit TRot(const TOBB2& box)
		{
			c = box.orient[0][0];
			s = box.orient[0][1];
		}
		void Set(float angle)
		{
			s = sinf(angle);
			c = cosf(angle);
		}
		void SetIdentity()
		{
			s = 0.0f;
			c = 1.0f;
		}
		float GetAngle() const
		{
			return atan2(s, c);
		}
		TVec2 GetXAxis() const
		{
			return TVec2(c, s);
		}
		TVec2 GetYAxis() const
		{
			return TVec2(-s, c);
		}
		float s, c;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapValue, TRot, "TRot");
	MUnpackA1(TYPE, Set, WrapValue<float>);
	MUnpackA0(TYPE, SetIdentity);
	MUnpackCRA0(WrapValue<float>, TYPE, GetAngle);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class TBaluTransform
	{
	public:
		TVec2 position;
		TRot angle;
		TBaluTransform()
		{
			position = TVec2(0, 0);
			angle = TRot(0);
		}
		TBaluTransform(TVec2 position, TRot angle)
		{
			this->position = position;
			this->angle = angle;
		}
		TMatrix2 GetOrientation()
		{
			return TMatrix2(angle.GetXAxis(), angle.GetYAxis());
		}
		TVec2 ToGlobal(TVec2 p)
		{
			return GetOrientation()*p + position;
		}
		TVec2 ToLocal(TVec2 p)
		{
			return GetOrientation().TransMul((p - position));
		}

		TOBB2 ToGlobal(TOBB2 box)
		{
			return TOBB2(box.pos + position, GetOrientation()*box.orient, box.local);
		}
		TOBB2 ToGlobal(TAABB2 box)
		{
			return TOBB2(position, GetOrientation(), box);
		}
		TBaluTransform ToGlobal(TBaluTransform local)
		{
			TBaluTransform global;
			global.position = position + GetOrientation()*local.position;
			global.angle = TRot(angle.GetAngle() + local.angle.GetAngle());
			return global;
		}
		TVec2 Transform(TVec2 vertex, TVec2 scale)
		{
			return this->ToGlobal((vertex).ComponentMul(scale));
		}
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapValue, TBaluTransform, "TTransform");
	MUnpackRA2(WrapValue<TVec2>, TYPE, Transform, WrapValue<TVec2>, WrapValue<TVec2>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class TBaluTransformWithScale
	{
	public:
		TBaluTransform transform;
		TVec2 scale;
		TBaluTransformWithScale()
		{
			scale = TVec2(1, 1);
			transform = TBaluTransform(TVec2(0, 0), TRot(0));
		}
		TBaluTransformWithScale(TBaluTransform transform, TVec2 scale)
		{
			this->transform = transform;
			this->scale = scale;
		}
		TVec2 ToLocal(TVec2 point)
		{
			TVec2 p = transform.ToLocal(point);
			p /= scale;
			return p;
		}
		TVec2 ToGlobal(TVec2 p)
		{
			return transform.ToGlobal(p.ComponentMul(scale));
		}
		TBaluTransformWithScale ToGlobal(TBaluTransformWithScale local)
		{
			TBaluTransformWithScale global;
			global.transform.position = transform.position + transform.GetOrientation()*(local.transform.position.ComponentMul(scale));
			global.transform.angle = TRot(transform.angle.GetAngle() + local.transform.angle.GetAngle());
			global.scale = scale.ComponentMul(local.scale);
			return global;
		}
		TOBB2 ToGlobal(TAABB2 box)
		{
			box.border[0] *= scale;
			box.border[1] *= scale;
			return transform.ToGlobal(box);
		}
		TOBB2 ToGlobal(TOBB2 box)
		{
			box.local.border[0] *= scale;
			box.local.border[1] *= scale;
			return transform.ToGlobal(box);
		}
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IViewport
	{
	public:
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual void SetAspectRatio(float aspect) = 0;
		virtual void SetWidth(float width) = 0;
		virtual TAABB2 GetAABB() = 0;
		virtual void SetSize(TVec2 size) = 0;
		virtual TVec2 GetSize() = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IViewport, "IViewport");
	MUnpackA1(TYPE, SetSize, WrapValue<TVec2>);
	MUnpackRA0(WrapValue<TVec2>, TYPE, GetSize);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	struct TDrawingHelperContext
	{
		TScreen* screen;
		TView* view;
		IViewport* viewport;
		TDrawingHelperContext()
		{
			screen = nullptr;
			view = nullptr;
			viewport = nullptr;
		}
		TVec2 FromScreenPixelsToScene(TVec2i screen_pixels);
		TVec2i FromSceneToScreenPixels(TVec2 scene_coordinates);
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class TBaluWorld;
	class TSceneObject
	{
	public:
		virtual const char* GetFactoryName() = 0;
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual TVec2 GetScale() = 0;
		virtual TBaluTransformWithScale GetTransformWithScale() = 0;
		virtual void Save(pugi::xml_node& parent_node, const int version) = 0;
		virtual void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world) = 0;
		virtual ~TSceneObject()
		{
		}
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	typedef TSceneObject*(*SceneObjectClone)();
	class SceneObjectFactory
	{
	public:
		static bool Register(const char* name, SceneObjectClone clone);
		static TSceneObject* Create(const char* name);
	};

	class TGui : public TSceneObject
	{
	public:
	};
#endif
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	enum class TWorldObjectType
	{
		Material,
		Sprite,
		Class,
		Scene,
		None
	};

	enum class TWorldObjectSubType
	{
		//SpritePolygon,
		//SpritePhysShape,
		ClassSpriteInstance,
		SceneClassInstance
	};

	class TWorldObjectTypeString
	{
	public:
		static inline const char* Get(TWorldObjectType index)
		{
			char* values[] =
			{
				"Material",
				"Sprite",
				"Class",
				"Scene",
				"None",
			};
			return values[(int)index];
		}
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	
	class IBaluWorld;
	class IProperties;
	class IAbstractEditor;
	class IBaluSceneInstance;
	class IBaluWorld;
	class IBaluWorldObject
	{
	public:
		virtual IProperties* GetProperties()=0;
		virtual std::string GetName()=0;
		virtual void SetName(std::string name)=0;
		virtual IBaluWorld* GetWorld()=0;
		virtual IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IBaluSceneInstance* editor_scene_instance) = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES

	class IProperties;
	class IAbstractEditor;
	class IBaluSceneInstance;
	class IBaluWorld;
	class TBaluWorldObject: public IBaluWorldObject
	{
	protected:
		IBaluWorld* world;
		TProperties properties;
		std::string name;
	public:
		TBaluWorldObject(IBaluWorld* world, std::string name);
		IProperties* GetProperties();
		std::string GetName();
		void SetName(std::string name);
		IBaluWorld* GetWorld();
	};

#endif
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluWorldObject, "TBaluWorldObject");
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IChangeListener
	{
	public:
		virtual void Changed()=0;
		virtual void ElementAdded(TWorldObjectSubType type) = 0;
		virtual void ElementRemoved(TWorldObjectSubType type) = 0;
		virtual void BeforeDelete() = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TChangeListenerArray
	{
	private:
		std::vector<IChangeListener*> listeners;
	public:
		std::vector<IChangeListener*> GetListeners()
		{
			return listeners;
		}
		void AddChangesListener(IChangeListener* listener)
		{
			auto it = std::find(listeners.begin(), listeners.end(), listener);
			assert(it == listeners.end());
			listeners.push_back(listener);
		}
		void RemoveChangesListener(IChangeListener* listener)
		{
			auto it = std::find(listeners.begin(), listeners.end(), listener);
			assert(it != listeners.end());
			listeners.erase(it);
		}
	};
#endif
#endif

#define REGISTER_FACTORY_CLASS(factory_name,class_name)\
	static bool class_name##_registered = factory_name::Register(class_name::FactoryName(), class_name::Clone);

}

