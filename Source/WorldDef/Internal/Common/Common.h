#pragma once

#include "../../Interface.h"

#include "Properties.h"

//#define REGISTER_FACTORY_CLASS(factory_name,class_name)\
//	static bool class_name##_registered = factory_name::Register(class_name::FactoryName(), class_name::Clone);

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			struct TDrawingHelperContext
			{
				//TScreen* screen;
				//TView* view;
				//IViewport* viewport;
				//TDrawingHelperContext()
				//{
				//	screen = nullptr;
				//	view = nullptr;
				//	viewport = nullptr;
				//}
				//BaluLib::TVec2 FromScreenPixelsToScene(BaluLib::TVec2i screen_pixels);
				//BaluLib::TVec2i FromSceneToScreenPixels(BaluLib::TVec2 scene_coordinates);
			};

			typedef ISceneObject*(*SceneObjectClone)();
			class SceneObjectFactory
			{
			public:
				static bool Register(const char* name, SceneObjectClone clone);
				static ISceneObject* Create(const char* name);
				static void UnregisterAll();
			};

			class TGui : public ISceneObject
			{
			public:
			};

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

			class TWorldObject : public TProperties, public virtual IWorldObject
			{
			protected:
				IWorld * world;

				void InitAllProperties()
				{
					InitProperty_Name();
				}

			public:

				BALU_ENGINE_REGISTER_PROPERTY(Name, PropertyType::String, "")

				TWorldObject(IWorld* world, std::string name);
				IWorld* GetWorld();
			};



			//template<class T>
			//class TObjLocator : TWorldChangeListener
			//{
			//	TWorld* world;
			//	std::string name;
			//	T* curr_ref;
			//public:
			//	TObjLocator(TWorld* world, std::string name)
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

		}
	}
}

