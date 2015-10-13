#pragma once

#include "ICallbacks.h"
#include "ICommon.h"
#include "Interfaces\ExportMacro.h"

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
		virtual void OnObjectCreate(TWorldObjectType type, std::string name) = 0;
		virtual void OnObjectDestroy(TWorldObjectType type, std::string name){}
	};

	class IBaluWorld
	{
	public:
		virtual void AddChangesListener(TBaluWorldChangeListener* listener) = 0;
		virtual void RemoveChangesListener(TBaluWorldChangeListener* listener) = 0;

		virtual TScriptActiveType& GetCallbacksActiveType() = 0;

		virtual bool TryFind(const char* name, IBaluWorldObject*& result) = 0;

		virtual IBaluWorldObject* GetObjectByName(TWorldObjectType type, const char* name) = 0;
		virtual std::vector<IBaluWorldObject*> GetObjects(TWorldObjectType type) = 0;
		virtual bool ObjectNameExists(TWorldObjectType type, const char* name) = 0;
		virtual IBaluWorldObject* CreateObject(TWorldObjectType type, const char* name) = 0;
		virtual void DestroyObject(TWorldObjectType type, const char* name) = 0;

		virtual void AddOnMouseDown(TScript) = 0;
		virtual void AddOnMouseUp(TScript) = 0;
		virtual void AddOnMouseMove(TScript) = 0;

		virtual std::vector<TScript>& GetOnMouseDown() = 0;
		virtual std::vector<TScript>& GetOnMouseUp() = 0;
		virtual std::vector<TScript>& GetOnMouseMove() = 0;

		virtual void AddOnWorldStart(TScript callback) = 0;
		virtual std::vector<TScript>& GetOnWorldStart() = 0;
		virtual void RemoveOnWorldStart(int index) = 0;

		virtual IBaluMaterial* CreateMaterial(const char* name) = 0;
		virtual IBaluSprite* CreateSprite(const char* name) = 0;
		virtual IBaluClass* CreateClass(const char* name) = 0;
		virtual IBaluScene* CreateScene(const char* name)=0;

		virtual IBaluScene* GetScene(std::string name) = 0;

		virtual void AddOnViewportResize(TScript callback) = 0;
		virtual std::vector<TScript>& GetOnViewportResize() = 0;
		virtual void RemoveOnViewportResize(int index) = 0;

		virtual void RemoveOnMouseDown(int index) = 0;
		virtual void RemoveOnMouseUp(int index) = 0;
		virtual void RemoveOnMouseMove(int index) = 0;

		virtual void SaveToXML(std::string path) = 0;
		virtual void LoadFromXML(std::string path) = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluWorldChangeListenerArray
	{
		std::vector<TBaluWorldChangeListener*> listeners;
	public:
		void OnObjectCreate(TWorldObjectType type, std::string name)
		{
			for (auto v : listeners)
				v->OnObjectCreate(type, name);
		}
		void OnObjectDestroy(TWorldObjectType type, std::string name)
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

		TScriptActiveType callback_active_type;

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

		std::vector<TScript>
			mouse_down_callbacks,
			mouse_up_callbacks,
			mouse_move_callbacks;
		std::vector<TScript> on_start_world_callback;
		std::vector<TScript> viewport_resize_callback;

		TBaluWorldChangeListenerArray listeners;
	public:
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
		//TODO убрать отсюда, указывать при создании экземпл€ра мира
		TScriptActiveType& GetCallbacksActiveType()
		{
			return callback_active_type;
		}
		bool TryFind(const char* name, IBaluWorldObject*& result);

		IBaluWorldObject* GetObjectByName(TWorldObjectType type, const char* name);
		std::vector<IBaluWorldObject*> GetObjects(TWorldObjectType type);
		bool ObjectNameExists(TWorldObjectType type, const char* name);
		TBaluWorldObject* CreateObject(TWorldObjectType type, const char* name);
		void DestroyObject(TWorldObjectType type, const char* name);

		void AddOnMouseDown(TScript);
		void AddOnMouseUp(TScript);
		void AddOnMouseMove(TScript);

		std::vector<TScript>& GetOnMouseDown();
		std::vector<TScript>& GetOnMouseUp();
		std::vector<TScript>& GetOnMouseMove();

		void RemoveOnMouseDown(int index);
		void RemoveOnMouseUp(int index);
		void RemoveOnMouseMove(int index);

		IBaluMaterial* CreateMaterial(const char* name);
		IBaluSprite* CreateSprite(const char* name);
		IBaluClass* CreateClass(const char* name);
		IBaluScene* CreateScene(const char* name);

		IBaluScene* GetScene(std::string name);

		void AddOnWorldStart(TScript callback);
		std::vector<TScript>& GetOnWorldStart();
		void RemoveOnWorldStart(int index);

		void AddOnViewportResize(TScript callback);
		std::vector<TScript>& GetOnViewportResize();
		void RemoveOnViewportResize(int index);

		void SaveToXML(std::string path);
		void LoadFromXML(std::string path);

		void SaveToXML(pugi::xml_node& parent_node, const int version);
		void LoadFromXML(const pugi::xml_node& document_node, const int version);
	};
#endif

	BALUENGINEDLL_API IBaluWorld* CreateWorld();
	BALUENGINEDLL_API void DestroyWorld(IBaluWorld* world);

}
