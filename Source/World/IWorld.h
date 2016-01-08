#pragma once

#include "ICallbacks.h"
#include "ICommon.h"
#include "Interfaces\ExportMacro.h"

#include "IEventsEditor.h"

namespace EngineInterface
{
	class IDirector;
	class IBaluWorldInstance;
	class TRender;
	class IBaluWorldObject;

	class IBaluMaterial;
	class IBaluSprite;
	class IBaluClass;
	class IBaluScene;
}

namespace EngineInterface
{
	class TBaluWorldChangeListener
	{
	public:
		virtual void OnObjectCreate(TWorldObjectType type, const std::string& name) = 0;
		virtual void OnObjectDestroy(TWorldObjectType type, const std::string& name){}
	};

	class IBaluWorld
	{
	public:
		virtual void AddChangesListener(TBaluWorldChangeListener* listener) = 0;
		virtual void RemoveChangesListener(TBaluWorldChangeListener* listener) = 0;

		virtual bool TryFind(const char* name, IBaluWorldObject*& result) = 0;

		virtual IBaluWorldObject* GetObjectByName(TWorldObjectType type, const char* name) = 0;
		virtual std::vector<IBaluWorldObject*> GetObjects(TWorldObjectType type) = 0;
		virtual bool ObjectNameExists(TWorldObjectType type, const char* name) = 0;
		virtual IBaluWorldObject* CreateObject(TWorldObjectType type, const char* name) = 0;
		virtual void DestroyObject(TWorldObjectType type, const char* name) = 0;

		virtual IBaluMaterial* CreateMaterial(const char* name) = 0;
		virtual IBaluSprite* CreateSprite(const char* name) = 0;
		virtual IBaluClass* CreateClass(const char* name) = 0;
		virtual IBaluScene* CreateScene(const char* name)=0;

		virtual IBaluScene* GetScene(const std::string& name) = 0;
		virtual IBaluMaterial* GetMaterial(const std::string& name) = 0;
		virtual IBaluSprite* GetSprite(const std::string& name) = 0;
		virtual IBaluClass* GetClass(const std::string& name) = 0;

		virtual void SaveToXML(const std::string& path) = 0;
		virtual void LoadFromXML(const std::string& path) = 0;

		virtual IEventsEditor* GetEventsEditor() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluWorldChangeListenerArray
	{
		std::vector<TBaluWorldChangeListener*> listeners;
	public:
		void OnObjectCreate(TWorldObjectType type, const std::string& name)
		{
			for (auto v : listeners)
				v->OnObjectCreate(type, name);
		}
		void OnObjectDestroy(TWorldObjectType type, const std::string& name)
		{
			for (auto v : listeners)
				v->OnObjectDestroy(type, name);
		}
		void AddChangesListener(TBaluWorldChangeListener* listener)
		{
			auto it = std::find(listeners.begin(), listeners.end(), listener);
			assert(it == listeners.end());
			listeners.push_back(listener);
		}
		void RemoveChangesListener(TBaluWorldChangeListener* listener)
		{
			auto it = std::find(listeners.begin(), listeners.end(), listener);
			assert(it != listeners.end());
			listeners.erase(it);
		}
	};

	class TBaluWorld : public IBaluWorld
	{
	private:
		friend class TBaluWorldInstance;

		std::map<std::string, std::unique_ptr<TBaluWorldObject>> world_objects[(int)TWorldObjectType::None];

		template<class T, class M>
		std::vector<T*> GetVectorFromMap(M& map)
		{
			std::vector<T*> result;
			result.reserve(map.size());
			for (auto& v : map)
			{
				result.push_back(v.second.get());
			}
			return result;
		}

		std::unique_ptr<TEventsEditor> events_editor;

		TBaluWorldChangeListenerArray listeners;
	public:

		virtual IEventsEditor* GetEventsEditor()
		{
			return events_editor.get();
		}

		virtual void AddChangesListener(TBaluWorldChangeListener* listener)
		{
			listeners.AddChangesListener(listener);
		}
		virtual void RemoveChangesListener(TBaluWorldChangeListener* listener)
		{
			listeners.RemoveChangesListener(listener);
		}

		TBaluWorld();
		~TBaluWorld();

		bool TryFind(const char* name, IBaluWorldObject*& result);

		IBaluWorldObject* GetObjectByName(TWorldObjectType type, const char* name);
		std::vector<IBaluWorldObject*> GetObjects(TWorldObjectType type);
		bool ObjectNameExists(TWorldObjectType type, const char* name);
		TBaluWorldObject* CreateObject(TWorldObjectType type, const char* name);
		void DestroyObject(TWorldObjectType type, const char* name);

		IBaluMaterial* CreateMaterial(const char* name);
		IBaluSprite* CreateSprite(const char* name);
		IBaluClass* CreateClass(const char* name);
		IBaluScene* CreateScene(const char* name);

		IBaluScene* GetScene(const std::string& name);
		IBaluMaterial* GetMaterial(const std::string& name);
		IBaluSprite* GetSprite(const std::string& name);
		IBaluClass* GetClass(const std::string& name);

		void SaveToXML(const std::string& path);
		void LoadFromXML(const std::string& path);

		void SaveToXML(pugi::xml_node& parent_node, const int version);
		void LoadFromXML(const pugi::xml_node& document_node, const int version);
	};
#endif

	BALUENGINEDLL_API IBaluWorld* CreateWorld();
	BALUENGINEDLL_API void DestroyWorld(IBaluWorld* world);

}
