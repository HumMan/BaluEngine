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

	enum TKey :int
	{
		Left,
		Right,
		Up,
		Down
	};

	class IEventsEditor
	{
	public:
		virtual void AddOnMouseDown(TScript) = 0;
		virtual void AddOnMouseUp(TScript) = 0;
		virtual void AddOnMouseMove(TScript) = 0;

		virtual void RemoveOnMouseDown(int index) = 0;
		virtual void RemoveOnMouseUp(int index) = 0;
		virtual void RemoveOnMouseMove(int index) = 0;

		virtual std::vector<TScript>& GetOnMouseDown() = 0;
		virtual std::vector<TScript>& GetOnMouseUp() = 0;
		virtual std::vector<TScript>& GetOnMouseMove() = 0;

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
			mouse_down_callbacks,
			mouse_up_callbacks,
			mouse_move_callbacks;
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

		void AddOnMouseDown(TScript);
		void AddOnMouseUp(TScript);
		void AddOnMouseMove(TScript);

		void RemoveOnMouseDown(int index);
		void RemoveOnMouseUp(int index);
		void RemoveOnMouseMove(int index);

		std::vector<TScript>& GetOnMouseDown();
		std::vector<TScript>& GetOnMouseUp();
		std::vector<TScript>& GetOnMouseMove();

		void AddOnWorldStart(TScript callback);
		std::vector<TScript>& GetOnWorldStart();
		void RemoveOnWorldStart(int index);

		void AddOnViewportResize(TScript callback);
		std::vector<TScript>& GetOnViewportResize();
		void RemoveOnViewportResize(int index);

		//class

		void AddOnCollide(IBaluTransformedSprite* sprite, IBaluClass* obstancle_class, TScript callback);
		std::vector<TSpriteWithClassCollide>& GetOnCollide();
		TScript* GetOnCollide(IBaluTransformedSprite* sprite, IBaluClass* obstancle_class);
		void RemoveOnCollide(int index);

		void OnKeyDownGlobal(TKey key, TScript callback);
		void OnKeyDown(TKey key, TScript callback, IBaluClass* use_class);
		void OnKeyUpGlobal(TKey key, TScript callback);
		void OnKeyUp(TKey key, TScript callback, IBaluClass* use_class);
		void OnBeforePhysicsStepGlobal(TScript callback);
		void OnBeforePhysicsStep(TScript callback, IBaluClass* use_class);

		std::map<TKey, std::vector<TScript>>& GetOnKeyDownGlobal();
		std::map<TKey, std::vector<TScript>>& GetOnKeyUpGlobal();
		std::vector<TScript>& GetOnBeforePhysicsStepGlobal();
		std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>>& GetOnKeyDown();
		std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>>& GetOnKeyUp();
		std::vector<std::tuple<TScript, IBaluClass*>>& GetOnBeforePhysicsStep();
	};
#endif

}
