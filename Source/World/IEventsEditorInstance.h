#pragma once

#include "IEventsEditor.h"

namespace EngineInterface
{
	class IDirector;
	class TDirector;
	class IBaluWorldInstance;
	class TBaluWorldInstance;
	class TRender;
	class IBaluWorldObject;

	class IBaluMaterial;
	class IBaluSprite;
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
	};


#ifdef BALUENGINEDLL_EXPORTS
	struct TSpriteWithClassCollideInstance
	{
		IBaluSprite* sprite;
		IBaluClass* with_class;
		TScriptInstance script;
		TSpriteWithClassCollideInstance()
		{
			sprite = nullptr;
			with_class = nullptr;
		}
		TSpriteWithClassCollideInstance(IBaluSprite* sprite, IBaluClass* with_class, TScriptInstance script)
		{
			this->sprite = sprite;
			this->with_class = with_class;
			this->script = script;
		}
	};

	class TBaluClassCompiledScripts
	{
	private:
		TBaluWorldInstance* world_instance;
		TBaluClass* source;

		std::vector<std::pair<TKey, TScriptInstance>> on_key_down_callbacks;
		std::vector<std::pair<TKey, TScriptInstance>> on_key_up_callbacks;
		std::vector<TScriptInstance> before_physics_callbacks;
		std::vector<TSpriteWithClassCollideInstance> on_collide_callbacks;
	public:
		TBaluClassCompiledScripts(TBaluWorldInstance* world_instance, TBaluClass* source);
		TBaluClass* GetClass()
		{
			return source;
		}
		/*void CompileScripts();
		static void CheckScriptErrors(TBaluClass* source, TBaluScriptInstance* script_engine, std::vector<std::string>& errors_list);

		void DoKeyDown(TKey key, TBaluTransformedClassInstance* instance);
		void DoKeyUp(TKey key, TBaluTransformedClassInstance* instance);
		void DoBeforePhysicsStep(TBaluTransformedClassInstance* instance);
		void DoCollide(TBaluTransformedClassInstance* source_object, TBaluTransformedSpriteInstance* obj_a, TBaluTransformedClassInstance* obstancle);*/
		//void DoSensorCollide(TSensorInstance* sensor, TBaluTransformedClassInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
		//void DoBeginContact(TSensorInstance* sensor, TBaluTransformedClassInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
		//void DoEndContact(TSensorInstance* sensor, TBaluTransformedClassInstance* obstancle, TBaluPhysShapeInstance* obstacle_shape);
	};
#endif

#ifdef BALUENGINEDLL_EXPORTS

	class TEventsEditorInstance :public IEventsEditorInstance
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

		//TBaluScriptInstance script_engine;
	public:

		//TBaluClassCompiledScripts* GetClassCompiled(TBaluClass* source)
		//{
		//	for (auto& v : class_compiled_instances)
		//		if (v->GetClass() == source)
		//			return v.get();
		//	return nullptr;
		//}
		//TBaluScriptInstance* GetScriptEngine()
		//{
		//	return &script_engine;
		//}
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
		static bool CheckScriptErrors(TBaluWorld* source, std::vector<std::string>& errors_list);

		//scene
		//void OnPrePhysStep();
		//void OnKeyDown(TKey key);

		//void OnMouseUp(TMouseEventArgs e, TVec2 scene_cursor_location);
		//void OnMouseDown(TMouseEventArgs e, TVec2 scene_cursor_location);
		//void OnMouseMove(TMouseEventArgs e, TVec2 scene_cursor_location);
	};
#endif
}
