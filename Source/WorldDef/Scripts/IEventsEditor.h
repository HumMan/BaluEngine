#pragma once

#include "ICallbacks.h"
#include <Common/ICommon.h>
#include <Interfaces/ExportMacro.h>

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
	class IBaluTransformedSprite;
}

namespace EngineInterface
{

	struct TSpriteWithClassCollide
	{
		IBaluTransformedSprite* sprite;
		IBaluClass* with_class;
		TScript script;
		TSpriteWithClassCollide()
		{
			sprite = nullptr;
			with_class = nullptr;
		}
		TSpriteWithClassCollide(IBaluTransformedSprite* sprite, IBaluClass* with_class, TScript script)
		{
			this->sprite = sprite;
			this->with_class = with_class;
			this->script = script;
		}
	};

	class IEventsEditor
	{
	public:
		virtual void AddOnMouseDownGlobal(TScript) = 0;
		virtual void AddOnMouseUpGlobal(TScript) = 0;
		virtual void AddOnMouseMoveGlobal(TScript) = 0;

		virtual void RemoveOnMouseDownGlobal(int index) = 0;
		virtual void RemoveOnMouseUpGlobal(int index) = 0;
		virtual void RemoveOnMouseMoveGlobal(int index) = 0;

		virtual std::vector<TScript>& GetOnMouseDownGlobal() = 0;
		virtual std::vector<TScript>& GetOnMouseUpGlobal() = 0;
		virtual std::vector<TScript>& GetOnMouseMoveGlobal() = 0;

		virtual void AddOnWorldStart(TScript callback) = 0;
		virtual std::vector<TScript>& GetOnWorldStart() = 0;
		virtual void RemoveOnWorldStart(int index) = 0;

		virtual void AddOnViewportResize(TScript callback) = 0;
		virtual std::vector<TScript>& GetOnViewportResize() = 0;
		virtual void RemoveOnViewportResize(int index) = 0;

		//class
		virtual void OnKeyDownGlobal (TKey key, TScript callback) = 0;
		virtual void OnKeyDown(TKey key, TScript callback, IBaluClass* use_class) = 0;
		virtual void OnKeyUpGlobal(TKey key, TScript callback) = 0;
		virtual void OnKeyUp(TKey key, TScript callback, IBaluClass* use_class) = 0;
		virtual void OnBeforePhysicsStepGlobal(TScript callback) = 0;
		virtual void OnBeforePhysicsStep(TScript callback, IBaluClass* use_class) = 0;

		virtual std::map<TKey, std::vector<TScript>>& GetOnKeyDownGlobal() = 0;
		virtual std::map<TKey, std::vector<TScript>>& GetOnKeyUpGlobal() = 0;
		virtual std::vector<TScript>& GetOnBeforePhysicsStepGlobal() = 0;
		virtual std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>>& GetOnKeyDown() = 0;
		virtual std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>>& GetOnKeyUp() = 0;
		virtual std::vector<std::tuple<TScript, IBaluClass*>>& GetOnBeforePhysicsStep() = 0;

		virtual void AddOnCollide(IBaluTransformedSprite* sprite, IBaluClass* obstancle_class, TScript script) = 0;
		virtual std::vector<TSpriteWithClassCollide>& GetOnCollide() = 0;
		virtual void RemoveOnCollide(int index) = 0;

	};

#ifdef BALUENGINEDLL_EXPORTS
	
	class TEventsEditor : public IEventsEditor
	{
		friend class TEventsEditorInstance;
	private:

		//global
		std::vector<TScript>
			global_mouse_down_callbacks,
			global_mouse_up_callbacks,
			global_mouse_move_callbacks;

		std::vector<TScript> on_start_world_callback;
		std::vector<TScript> viewport_resize_callback;

		std::map<TKey, std::vector<TScript>> global_on_key_down_callbacks;
		std::map<TKey, std::vector<TScript>> global_on_key_up_callbacks;
		std::vector<TScript> global_before_physics_callbacks;

		//class
		std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>> on_key_down_callbacks;
		std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>> on_key_up_callbacks;
		std::vector<std::tuple<TScript, IBaluClass*>> before_physics_callbacks;

		std::vector<TSpriteWithClassCollide> on_collide_callbacks;

	public:

		//global

		void AddOnMouseDownGlobal(TScript);
		void AddOnMouseUpGlobal(TScript);
		void AddOnMouseMoveGlobal(TScript);

		void RemoveOnMouseDownGlobal(int index);
		void RemoveOnMouseUpGlobal(int index);
		void RemoveOnMouseMoveGlobal(int index);

		std::vector<TScript>& GetOnMouseDownGlobal();
		std::vector<TScript>& GetOnMouseUpGlobal();
		std::vector<TScript>& GetOnMouseMoveGlobal();

		void AddOnWorldStart(TScript callback);
		std::vector<TScript>& GetOnWorldStart();
		void RemoveOnWorldStart(int index);

		void AddOnViewportResize(TScript callback);
		std::vector<TScript>& GetOnViewportResize();
		void RemoveOnViewportResize(int index);

		void OnKeyDownGlobal(TKey key, TScript callback);
		void OnKeyUpGlobal(TKey key, TScript callback);
		void OnBeforePhysicsStepGlobal(TScript callback);

		std::map<TKey, std::vector<TScript>>& GetOnKeyDownGlobal();
		std::map<TKey, std::vector<TScript>>& GetOnKeyUpGlobal();
		std::vector<TScript>& GetOnBeforePhysicsStepGlobal();

		//class

		void AddOnCollide(IBaluTransformedSprite* sprite, IBaluClass* obstancle_class, TScript callback);
		std::vector<TSpriteWithClassCollide>& GetOnCollide();
		TScript* GetOnCollide(IBaluTransformedSprite* sprite, IBaluClass* obstancle_class);
		void RemoveOnCollide(int index);

		void OnKeyDown(TKey key, TScript callback, IBaluClass* use_class);		
		std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>>& GetOnKeyDown();

		void OnKeyUp(TKey key, TScript callback, IBaluClass* use_class);		
		std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>>& GetOnKeyUp();

		void OnBeforePhysicsStep(TScript callback, IBaluClass* use_class);
		std::vector<std::tuple<TScript, IBaluClass*>>& GetOnBeforePhysicsStep();

		//

		void SaveToXML(pugi::xml_node& parent_node, const int version);
		void LoadFromXML(const pugi::xml_node& document_node, const int version);
	};
#endif

}
