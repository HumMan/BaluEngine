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
	};

#ifdef BALUENGINEDLL_EXPORTS
	
	class TEventsEditor : public IEventsEditor
	{
	private:
		std::vector<TScript>
			mouse_down_callbacks,
			mouse_up_callbacks,
			mouse_move_callbacks;
		std::vector<TScript> on_start_world_callback;
		std::vector<TScript> viewport_resize_callback;
	public:

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
	};
#endif

	class TMouseEventListener
	{
	public:
		virtual void OnMouseMove(TMouseEventArgs e){}
		virtual void OnMouseDown(TMouseEventArgs e){}
		virtual void OnMouseUp(TMouseEventArgs e){}
	};

	class IEventsEditorInstance
	{
	public:
		virtual void MouseDown(TMouseEventArgs e) = 0;
		virtual void MouseMove(TMouseEventArgs e) = 0;
		virtual void MouseUp(TMouseEventArgs e) = 0;
		virtual void MouseVerticalWheel(int amount) = 0;

		virtual void AddMouseEventListener(TMouseEventListener*) = 0;
		virtual void RemoveMouseEventListener(TMouseEventListener*) = 0;
	};


#ifdef BALUENGINEDLL_EXPORTS

	/*class TEventsEditor
	{
	private:

		std::vector<TScriptInstance>
			mouse_down_callbacks,
			mouse_up_callbacks,
			mouse_move_callbacks;
		std::vector<TScriptInstance> on_start_world_callback;
		std::vector<TScriptInstance> viewport_resize_callback;
		std::vector<TMouseEventListener*> OnMouseEventListeners;

		std::vector<std::unique_ptr<TBaluClassCompiledScripts>> class_compiled_instances;

		TBaluScriptInstance script_engine;
	public:

		TBaluClassCompiledScripts* GetClassCompiled(TBaluClass* source)
		{
			for (auto& v : class_compiled_instances)
				if (v->GetClass() == source)
					return v.get();
			return nullptr;
		}
		TBaluScriptInstance* GetScriptEngine()
		{
			return &script_engine;
		}
		//world
		void AddMouseEventListener(TMouseEventListener*);
		void RemoveMouseEventListener(TMouseEventListener*);
		void OnPrePhysStep();
		void OnProcessCollisions();


		void KeyDown(TKey key);
		void KeyUp(TKey key);

		void MouseDown(TMouseEventArgs e);
		void MouseMove(TMouseEventArgs e);
		void MouseUp(TMouseEventArgs e);
		void MouseVerticalWheel(int amount);

		void ViewportResize(TDirector* director, TVec2i old_size, TVec2i new_size);

		bool CompileScripts();
		static bool CheckScriptErrors(TBaluWorld* source, TBaluScriptInstance* script_engine, std::vector<std::string>& errors_list);

		//scene
		void OnPrePhysStep();
		void OnKeyDown(TKey key);

		void OnMouseUp(TMouseEventArgs e, TVec2 scene_cursor_location);
		void OnMouseDown(TMouseEventArgs e, TVec2 scene_cursor_location);
		void OnMouseMove(TMouseEventArgs e, TVec2 scene_cursor_location);
	};*/
#endif
}
