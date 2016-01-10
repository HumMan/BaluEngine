#include "IEventsEditor.h"

#include <pugixml.hpp>

using namespace pugi;
using namespace EngineInterface;

void TEventsEditor::AddOnMouseDown(TScript callback)
{
	mouse_down_callbacks.push_back(callback);
}

void TEventsEditor::AddOnMouseUp(TScript callback)
{
	mouse_up_callbacks.push_back(callback);
}

void TEventsEditor::AddOnMouseMove(TScript callback)
{
	mouse_move_callbacks.push_back(callback);
}

std::vector<TScript>& TEventsEditor::GetOnMouseDown()
{
	return mouse_down_callbacks;
}
std::vector<TScript>& TEventsEditor::GetOnMouseUp()
{
	return mouse_up_callbacks;
}
std::vector<TScript>& TEventsEditor::GetOnMouseMove()
{
	return mouse_move_callbacks;
}

void TEventsEditor::RemoveOnMouseDown(int index)
{
	mouse_down_callbacks.erase(mouse_down_callbacks.begin() + index);
}

void TEventsEditor::RemoveOnMouseUp(int index)
{
	mouse_up_callbacks.erase(mouse_up_callbacks.begin() + index);
}

void TEventsEditor::RemoveOnMouseMove(int index)
{
	mouse_move_callbacks.erase(mouse_move_callbacks.begin() + index);
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

//
//std::vector<TSpriteWithClassCollide>& TBaluClass::GetOnCollide()
//{
//	return on_collide_callbacks;
//}
//
//TScript* TBaluClass::GetOnCollide(IBaluSprite* sprite, TBaluClass* obstancle_class)
//{
//	for (auto& v : on_collide_callbacks)
//		if (v.with_class == obstancle_class && v.sprite == sprite)
//			return &v.script;
//	return nullptr;
//}
//
//void TBaluClass::AddOnCollide(IBaluSprite* sprite, IBaluClass* obstancle_class, TScript callback)
//{
//	on_collide_callbacks.push_back(TSpriteWithClassCollide(sprite, obstancle_class, callback));
//}
//
//void TBaluClass::RemoveOnCollide(int index)
//{
//	on_collide_callbacks.erase(on_collide_callbacks.begin() + index);
//}
//
//
//void TBaluClass::OnKeyDown(TKey key, TScript callback)
//{
//	on_key_down_callbacks[key].push_back(callback);
//}
//
//void TBaluClass::OnKeyUp(TKey key, TScript callback)
//{
//	on_key_up_callbacks[key].push_back(callback);
//}
//
//
//void TBaluClass::OnBeforePhysicsStep(TScript callback)
//{
//	before_physics_callbacks.push_back(callback);
//}
//
//std::map<TKey, std::vector<TScript>>& TBaluClass::GetOnKeyDown()
//{
//	return on_key_down_callbacks;
//}
//
//std::map<TKey, std::vector<TScript>>& TBaluClass::GetOnKeyUp()
//{
//	return on_key_up_callbacks;
//}
//
//std::vector<TScript>& TBaluClass::GetOnBeforePhysicsStep()
//{
//	return before_physics_callbacks;
//}