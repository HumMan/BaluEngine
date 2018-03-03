#pragma once

#include <WorldDef/Scripts/IEventsEditor.h>

#include "IScriptInstance.h"

namespace EngineInterface
{
	class IDirector;
	class TDirector;
	class IComposer;
	class IBaluWorldInstance;
	class TBaluWorldInstance;
	class TRender;
	class IBaluWorldObject;
	class TBaluScriptInstance;

	class IBaluMaterial;
	class IBaluSprite;
	class IBaluTransformedSprite;
	class IBaluClass;
	class IBaluScene;
}

namespace EngineInterface
{
	
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

		virtual void ViewportResize(IDirector* director, TVec2i old_size, TVec2i new_size) = 0;
	};


#ifdef BALUENGINEDLL_EXPORTS
	struct TSpriteWithClassCollideInstance
	{
		IBaluTransformedSprite* sprite;
		IBaluClass* with_class;
		TScriptInstance script;
		TSpriteWithClassCollideInstance()
		{
			sprite = nullptr;
			with_class = nullptr;
		}
		TSpriteWithClassCollideInstance(IBaluTransformedSprite* sprite, IBaluClass* with_class, TScriptInstance script)
		{
			this->sprite = sprite;
			this->with_class = with_class;
			this->script = script;
		}
	};
#endif

#ifdef BALUENGINEDLL_EXPORTS

	class TEventsEditorInstance :public IEventsEditorInstance
	{
	private:

		std::unique_ptr<TBaluScriptInstance> script_engine;

		std::vector<TMouseEventListener*> OnMouseEventListeners;

		//global

		std::vector<TScriptInstance>
			mouse_down_callbacks,
			mouse_up_callbacks,
			mouse_move_callbacks;
		std::vector<TScriptInstance> on_start_world_callback;
		std::vector<TScriptInstance> viewport_resize_callback;
		
		std::map<TKey, std::vector<TScriptInstance>> global_on_key_down_callbacks;
		std::map<TKey, std::vector<TScriptInstance>> global_on_key_up_callbacks;
		std::vector<TScriptInstance> global_before_physics_callbacks;

		//class

		std::map<TKey, std::vector<std::tuple<TScriptInstance, IBaluClass*>>> on_key_down_callbacks;
		std::map<TKey, std::vector<std::tuple<TScriptInstance, IBaluClass*>>> on_key_up_callbacks;
		std::vector<std::tuple<TScriptInstance, IBaluClass*>> before_physics_callbacks;

		std::vector<TSpriteWithClassCollideInstance> on_collide_callbacks;

		IEventsEditor* source;
	public:
		TEventsEditorInstance(IEventsEditor* source, std::string assets_dir);
		~TEventsEditorInstance();
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

		void ViewportResize(IDirector* director, TVec2i old_size, TVec2i new_size);

		void WorldStart(IBaluWorldInstance* world_instance, IComposer* composer);

		bool CompileScripts(std::string& error_message);
		bool CheckScriptErrors(std::vector<std::string>& errors_list);

		//scene
		//void OnPrePhysStep();
		void OnKeyDown(TKey key);

		//void OnMouseUp(TMouseEventArgs e, TVec2 scene_cursor_location);
		//void OnMouseDown(TMouseEventArgs e, TVec2 scene_cursor_location);
		//void OnMouseMove(TMouseEventArgs e, TVec2 scene_cursor_location);

		//class
		static void CheckScriptErrors(TClass* source, TBaluScriptInstance* script_engine, std::vector<std::string>& errors_list);

		//void DoKeyDown(TKey key, TBaluTransformedClassInstance* instance);
		//void DoKeyUp(TKey key, TBaluTransformedClassInstance* instance);
		//void DoBeforePhysicsStep(TBaluTransformedClassInstance* instance);
		//void DoCollide(TBaluTransformedClassInstance* source_object, TBaluTransformedSpriteInstance* obj_a, TBaluTransformedClassInstance* obstancle);
		//void DoSensorCollide(TSensorInstance* sensor, TBaluTransformedClassInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
		//void DoBeginContact(TSensorInstance* sensor, TBaluTransformedClassInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
		//void DoEndContact(TSensorInstance* sensor, TBaluTransformedClassInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
	};
#endif
}
