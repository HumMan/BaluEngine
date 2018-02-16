#pragma once

#include "../../Interface.h"


namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{
			struct TSpriteWithClassCollide
			{
				ITransformedSprite* sprite;
				IClass* with_class;
				TScript script;
				TSpriteWithClassCollide()
				{
					sprite = nullptr;
					with_class = nullptr;
				}
				TSpriteWithClassCollide(ITransformedSprite* sprite, IClass* with_class, TScript script)
				{
					this->sprite = sprite;
					this->with_class = with_class;
					this->script = script;
				}
			};

			class TEventsEditor : public IEventsEditor
			{
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
				std::map<TKey, std::vector<std::tuple<TScript, IClass*>>> on_key_down_callbacks;
				std::map<TKey, std::vector<std::tuple<TScript, IClass*>>> on_key_up_callbacks;
				std::vector<std::tuple<TScript, IClass*>> before_physics_callbacks;

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

				void AddOnCollide(ITransformedSprite* sprite, IClass* obstancle_class, TScript callback);
				std::vector<TSpriteWithClassCollide>& GetOnCollide();
				TScript* GetOnCollide(ITransformedSprite* sprite, IClass* obstancle_class);
				void RemoveOnCollide(int index);

				void OnKeyDown(TKey key, TScript callback, IClass* use_class);
				std::map<TKey, std::vector<std::tuple<TScript, IClass*>>>& GetOnKeyDown();

				void OnKeyUp(TKey key, TScript callback, IClass* use_class);
				std::map<TKey, std::vector<std::tuple<TScript, IClass*>>>& GetOnKeyUp();

				void OnBeforePhysicsStep(TScript callback, IClass* use_class);
				std::vector<std::tuple<TScript, IClass*>>& GetOnBeforePhysicsStep();

				//

				void SaveToXML(pugi::xml_node& parent_node, const int version);
				void LoadFromXML(const pugi::xml_node& document_node, const int version);
			};
		}
	}
}
