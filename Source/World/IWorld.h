
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "ICallbacks.h"
#include "ICommon.h"
#endif

namespace EngineInterface
{
	class IDirector;
	class IBaluWorldInstance;
	class TRender;
}
#endif


namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES

	class IBaluWorld
	{
	public:
		virtual TScriptActiveType& GetCallbacksActiveType() = 0;

		virtual bool TryFind(const char* name, TBaluWorldObject*& result) = 0;

		virtual TBaluWorldObject* GetObjectByName(const char* name) = 0;
		virtual std::vector<TBaluWorldObject*> GetObjects(TWorldObjectType type) = 0;
		virtual bool ObjectNameExists(TWorldObjectType type, const char* name)=0;
		virtual void CreateObject(TWorldObjectType type, const char* name)=0;
		virtual void DestroyObject(TWorldObjectType type, const char* name)=0;

		virtual void AddOnMouseDown(TScript) = 0;
		virtual void AddOnMouseUp(TScript) = 0;
		virtual void AddOnMouseMove(TScript) = 0;

		virtual std::vector<TScript>& GetOnMouseDown() = 0;
		virtual std::vector<TScript>& GetOnMouseUp() = 0;
		virtual std::vector<TScript>& GetOnMouseMove() = 0;

		virtual void AddOnWorldStart(TScript callback) = 0;
		virtual std::vector<TScript>& GetOnWorldStart() = 0;
		virtual void RemoveOnWorldStart(int index) = 0;

		virtual void AddOnViewportResize(TScript callback) = 0;
		virtual std::vector<TScript>& GetOnViewportResize() = 0;
		virtual void RemoveOnViewportResize(int index) = 0;

		virtual void RemoveOnMouseDown(int index) = 0;
		virtual void RemoveOnMouseUp(int index) = 0;
		virtual void RemoveOnMouseMove(int index) = 0;

		virtual void SaveToXML(std::string path) = 0;
		virtual void LoadFromXML(std::string path) = 0;
	};


	class TBaluWorld : public IBaluWorld
	{
	private:
		friend class TBaluWorldInstance;

		std::map<std::string, std::unique_ptr<TBaluWorldObject>> world_objects;

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
	public:
		TBaluWorld();
		~TBaluWorld();
		//TODO убрать отсюда, указывать при создании экземпл€ра мира
		TScriptActiveType& GetCallbacksActiveType()
		{
			return callback_active_type;
		}
		bool TryFind(const char* name, TBaluWorldObject*& result);

		TBaluWorldObject* GetObjectByName(TWorldObjectType type, const char* name);
		std::vector<TBaluWorldObject*> GetObjects(TWorldObjectType type);
		bool ObjectNameExists(TWorldObjectType type, const char* name);
		void CreateObject(TWorldObjectType type, const char* name);
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

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluWorld, "IBaluWorld");
	MUnpackRA1(WrapPointer<IBaluScene>, WrapInterface<IBaluWorld>, GetScene, WrapValue<int>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	BALUENGINEDLL_API IBaluWorld* CreateWorld();
	BALUENGINEDLL_API void DestroyWorld(IBaluWorld* world);
#endif
}
