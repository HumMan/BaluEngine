#include "EventsEditor.h"

#include <pugixml.hpp>

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace pugi;

size_t TEventsEditor::GlobalGetCount(GlobalCallbackType type)
{
	return global[(int)type].size();
}

TScript& TEventsEditor::GlobalGet(GlobalCallbackType type, size_t index)
{
	return global[(int)type][index];
}

void TEventsEditor::GlobalInsert(GlobalCallbackType type, size_t after_index, TScript script)
{
	auto& arr = global[(int)type];
	arr.insert((after_index + 1 == arr.size()) ? arr.end() : (arr.begin() + after_index + 1), script);
}

void TEventsEditor::GlobalRemove(GlobalCallbackType type, size_t index)
{
	global[(int)type].erase(global[(int)type].begin() + index);
}

size_t TEventsEditor::GlobalKeyGetCount(GlobalCallbackType type)
{
	return global_key[(int)type].size();
}

std::tuple<TKey, TScript>& TEventsEditor::GlobalKeyGet(GlobalCallbackType type, size_t index)
{
	return global_key[(int)type][index];
}

void TEventsEditor::GlobalKeyInsert(GlobalCallbackType type, TKey key, size_t after_index, TScript script)
{
	auto& arr = global_key[(int)type];
	arr.insert((after_index+1== arr.size())?arr.end():(arr.begin() + after_index + 1), 
		std::tuple<TKey, TScript>(key,script));
}

void TEventsEditor::GlobalKeyRemove(GlobalCallbackType type, size_t index)
{
	global_key[(int)type].erase(global_key[(int)type].begin() + index);
}


size_t TEventsEditor::ClassGetCount(GlobalCallbackType type)
{
	return class_callbacks[(int)type].size();
}

std::tuple<TScript, std::string>& TEventsEditor::ClassGet(GlobalCallbackType type, size_t index)
{
	return class_callbacks[(int)type][index];
}

void TEventsEditor::ClassInsert(GlobalCallbackType type, std::string class_name, size_t after_index, TScript script)
{
	auto& arr = class_callbacks[(int)type];
	arr.insert((after_index + 1 == arr.size()) ? arr.end() : (arr.begin() + after_index + 1),
		std::tuple<std::string, TScript>(class_name, script));
}

void TEventsEditor::ClassRemove(GlobalCallbackType type, size_t index)
{
	class_callbacks[(int)type].erase(class_callbacks[(int)type].begin() + index);
}

size_t TEventsEditor::ClassKeyGetCount(GlobalCallbackType type)
{
	return class_key[(int)type].size();
}

std::tuple<TKey, TScript, std::string>& TEventsEditor::ClassKeyGet(GlobalCallbackType type, size_t index)
{
	return class_key[(int)type][index];
}

void TEventsEditor::ClassKeyInsert(GlobalCallbackType type, TKey key, std::string class_name, size_t after_index, TScript script)\
{
	auto& arr = class_key[(int)type];
	arr.insert((after_index + 1 == arr.size()) ? arr.end() : (arr.begin() + after_index + 1),
		std::tuple<TKey, TScript, std::string>(key, script, class_name));
}

void TEventsEditor::ClassKeyRemove(GlobalCallbackType type, size_t index)
{
	class_key[(int)type].erase(class_key[(int)type].begin() + index);
}


size_t TEventsEditor::OnCollideGetCount()
{
	return on_collide.size();
}

TSpriteWithClassCollide& TEventsEditor::OnCollideGet(size_t index)
{
	return on_collide[index];
}

void TEventsEditor::OnCollideInsert(int after_index, std::string source_class, int sprite, std::string  obstancle_class, TScript callback)
{
	auto& arr = on_collide;
	arr.insert((after_index + 1 == arr.size()) ? arr.end() : (arr.begin() + after_index + 1),
		TSpriteWithClassCollide(source_class, sprite, obstancle_class, callback));
}

void TEventsEditor::OnCollideRemove(size_t index)
{
	on_collide.erase(on_collide.begin() + index);
}