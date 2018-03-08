#pragma once

#include "../../Interface.h"

#include "SpritePolygonInstance.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{

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
				//static void CheckScriptErrors(TClass* source, TBaluScriptInstance* script_engine, std::vector<std::string>& errors_list);
			};
		}
	}
}
