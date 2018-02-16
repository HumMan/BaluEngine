#include "IEventsEditor.h"

#include <pugixml.hpp>

using namespace pugi;
using namespace EngineInterface;

void TEventsEditor::AddOnMouseDownGlobal(TScript callback)
{
	global_mouse_down_callbacks.push_back(callback);
}

void TEventsEditor::AddOnMouseUpGlobal(TScript callback)
{
	global_mouse_up_callbacks.push_back(callback);
}

void TEventsEditor::AddOnMouseMoveGlobal(TScript callback)
{
	global_mouse_move_callbacks.push_back(callback);
}

std::vector<TScript>& TEventsEditor::GetOnMouseDownGlobal()
{
	return global_mouse_down_callbacks;
}
std::vector<TScript>& TEventsEditor::GetOnMouseUpGlobal()
{
	return global_mouse_up_callbacks;
}
std::vector<TScript>& TEventsEditor::GetOnMouseMoveGlobal()
{
	return global_mouse_move_callbacks;
}

void TEventsEditor::RemoveOnMouseDownGlobal(int index)
{
	global_mouse_down_callbacks.erase(global_mouse_down_callbacks.begin() + index);
}

void TEventsEditor::RemoveOnMouseUpGlobal(int index)
{
	global_mouse_up_callbacks.erase(global_mouse_up_callbacks.begin() + index);
}

void TEventsEditor::RemoveOnMouseMoveGlobal(int index)
{
	global_mouse_move_callbacks.erase(global_mouse_move_callbacks.begin() + index);
}


void TEventsEditor::AddOnWorldStart(TScript callback)
{
	on_start_world_callback.push_back(callback);
}

std::vector<TScript>& TEventsEditor::GetOnWorldStart()
{
	return on_start_world_callback;
}

void TEventsEditor::RemoveOnWorldStart(int index)
{
	on_start_world_callback.erase(on_start_world_callback.begin() + index);
}

void TEventsEditor::AddOnViewportResize(TScript callback)
{
	viewport_resize_callback.push_back(callback);
}

std::vector<TScript>& TEventsEditor::GetOnViewportResize()
{
	return viewport_resize_callback;
}

void TEventsEditor::RemoveOnViewportResize(int index)
{
	viewport_resize_callback.erase(viewport_resize_callback.begin() + index);
}


std::vector<TSpriteWithClassCollide>& TEventsEditor::GetOnCollide()
{
	return on_collide_callbacks;
}

TScript* TEventsEditor::GetOnCollide(IBaluTransformedSprite* sprite, IBaluClass* obstancle_class)
{
	for (auto& v : on_collide_callbacks)
		if (v.with_class == obstancle_class && v.sprite == sprite)
			return &v.script;
	return nullptr;
}

void TEventsEditor::AddOnCollide(IBaluTransformedSprite* sprite, IBaluClass* obstancle_class, TScript callback)
{
	on_collide_callbacks.push_back(TSpriteWithClassCollide(sprite, obstancle_class, callback));
}

void TEventsEditor::RemoveOnCollide(int index)
{
	on_collide_callbacks.erase(on_collide_callbacks.begin() + index);
}


void TEventsEditor::OnKeyDownGlobal(TKey key, TScript callback)
{
	global_on_key_down_callbacks[key].push_back(callback);
}

void TEventsEditor::OnKeyUpGlobal(TKey key, TScript callback)
{
	global_on_key_up_callbacks[key].push_back(callback);
}


void TEventsEditor::OnBeforePhysicsStepGlobal(TScript callback)
{
	global_before_physics_callbacks.push_back(callback);
}

std::map<TKey, std::vector<TScript>>& TEventsEditor::GetOnKeyDownGlobal()
{
	return global_on_key_down_callbacks;
}

std::map<TKey, std::vector<TScript>>& TEventsEditor::GetOnKeyUpGlobal()
{
	return global_on_key_up_callbacks;
}

std::vector<TScript>& TEventsEditor::GetOnBeforePhysicsStepGlobal()
{
	return global_before_physics_callbacks;
}

std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>>& TEventsEditor::GetOnKeyDown()
{
	return on_key_down_callbacks;
}

std::map<TKey, std::vector<std::tuple<TScript, IBaluClass*>>>& TEventsEditor::GetOnKeyUp()
{
	return on_key_up_callbacks;
}
std::vector<std::tuple<TScript, IBaluClass*>>& TEventsEditor::GetOnBeforePhysicsStep()
{
	return before_physics_callbacks;
}
void TEventsEditor::OnKeyDown(TKey key, TScript callback, IBaluClass* use_class)
{
	on_key_down_callbacks[key].push_back(std::tuple<TScript, IBaluClass*>(callback, use_class));
}
void TEventsEditor::OnKeyUp(TKey key, TScript callback, IBaluClass* use_class)
{
	on_key_up_callbacks[key].push_back(std::tuple<TScript, IBaluClass*>(callback, use_class));
}
void TEventsEditor::OnBeforePhysicsStep(TScript callback, IBaluClass* use_class)
{
	before_physics_callbacks.push_back(std::tuple<TScript, IBaluClass*>(callback, use_class));
}