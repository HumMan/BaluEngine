#pragma once

#include <algorithm>
#include <baluLib.h>
#include <string>
#include "IProperties.h"
using namespace BaluLib;

#define REGISTER_FACTORY_CLASS(factory_name,class_name)\
	static bool class_name##_registered = factory_name::Register(class_name::FactoryName(), class_name::Clone);

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

namespace EngineInterface
{

	enum class TMouseButton
	{
		Left,
		Right,
		Middle
	};

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

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluClass;
	typedef TSceneObject*(*SceneObjectClone)();
	class SceneObjectFactory
	{
	public:
		static bool Register(const char* name, SceneObjectClone clone);
		static TSceneObject* Create(const char* name);
		static void UnregisterAll();
	};

	class TGui : public TSceneObject
	{
	public:
	};
#endif

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
	
	class IBaluWorld;
	class IProperties;
	class IAbstractEditor;
	class IBaluWorldInstance;
	class IBaluWorldObject
	{
	public:
		virtual IProperties* GetProperties()=0;
		virtual std::string GetName()=0;
		virtual void SetName(const std::string& name) = 0;
		virtual IBaluWorld* GetWorld()=0;
		virtual IAbstractEditor* CreateEditor(TDrawingHelperContext drawing_context, IBaluWorldInstance* world_instance) = 0;
		virtual void Save(pugi::xml_node& parent_node, const int version)=0;
		virtual void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world) = 0;
		virtual ~IBaluWorldObject() {}
		//virtual TWorldObjectType GetWorldObjectType() = 0;
	};

	class IChangeListener
	{
	public:
		virtual void SourceChanged() {}
		virtual void ElementToSourceAdded(TWorldObjectSubType type) {}
		virtual void ElementFromSourceRemoved(TWorldObjectSubType type) {}
		virtual void BeforeDeleteSource(){}
	};

	class IChangeListenerArray
	{
	public:
		virtual void AddChangesListener(IChangeListener* listener)=0;
		virtual void RemoveChangesListener(IChangeListener* listener)=0;
		virtual void OnChanged() = 0; 
		virtual void OnElementAdded(TWorldObjectSubType type) = 0;
		virtual void OnElementRemoved(TWorldObjectSubType type) = 0;
		virtual void OnBeforeDelete() = 0;
	};

	class TBaluWorldChangeListener
	{
	public:
		virtual void OnObjectCreate(TWorldObjectType type, const std::string& name) = 0;
		virtual void OnObjectDestroy(TWorldObjectType type, const std::string& name){}
		virtual void OnObjectRename(TWorldObjectType type, const std::string& old_name, const std::string& new_name){}
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TChangeListenerArray : public virtual IChangeListenerArray
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
		void OnChanged()
		{
			for (auto& l : listeners)
				l->SourceChanged();
		}
		void OnElementAdded(TWorldObjectSubType type)
		{
			for (auto& l : listeners)
				l->ElementToSourceAdded(type);
		}
		void OnElementRemoved(TWorldObjectSubType type)
		{
			for (auto& l : listeners)
				l->ElementFromSourceRemoved(type);
		}
		void OnBeforeDelete()
		{
			for (auto& l : listeners)
				l->BeforeDeleteSource();
		}
	};

	class IProperties;
	class IAbstractEditor;
	class IBaluSceneInstance;
	class IBaluWorld;
	class TBaluWorldObject : public virtual IBaluWorldObject
	{
	protected:
		IBaluWorld* world;
		TProperties properties;
		std::string name;
	public:
		TBaluWorldObject(IBaluWorld* world, std::string name);
		IProperties* GetProperties();
		std::string GetName();
		void SetName(const std::string& name);
		IBaluWorld* GetWorld();
	};



	//template<class T>
	//class TObjLocator : TBaluWorldChangeListener
	//{
	//	TBaluWorld* world;
	//	std::string name;
	//	T* curr_ref;
	//public:
	//	TObjLocator(TBaluWorld* world, std::string name)
	//	{
	//		this->world = world;
	//		this->name = name;
	//		curr_ref = nullptr;
	//	}
	//	void OnObjectCreate(TWorldObjectType type, const std::string& name)
	//	{
	//		curr_ref = world->GetObjectByName(T::GetWorldObjectType(), name);
	//	}
	//	void OnObjectDestroy(TWorldObjectType type, const std::string& name)
	//	{
	//		curr_ref = nullptr;
	//	}
	//	void OnObjectRename(TWorldObjectType type, const std::string& old_name, const std::string& new_name)
	//	{
	//		if (old_name == name)
	//		{
	//			name = old_name;
	//		}
	//	}
	//	T* Get()
	//	{
	//		if (curr_ref == nullptr)
	//		{
	//			curr_ref = world->GetObjectByName(T::GetWorldObjectType(), name);
	//		}
	//		return curr_ref;
	//	}
	//};

#endif



}

