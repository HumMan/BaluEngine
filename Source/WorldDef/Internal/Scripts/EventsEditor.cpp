#include "EventsEditor.h"

#include <pugixml.hpp>

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace pugi;

template<class T>
void ArrInsert(std::vector<T>& arr, int after_index, const T& value)
{
	if (after_index + 1 == arr.size())
		arr.push_back(value);
	else
		arr.insert(arr.begin() + (after_index + 1), value);
}

int TEventsEditor::GlobalGetCount(GlobalCallbackType type)
{
	return global[(int)type].size();
}

TScript& TEventsEditor::GlobalGet(GlobalCallbackType type, int index)
{
	return global[(int)type][index];
}

void TEventsEditor::GlobalInsert(GlobalCallbackType type, int after_index, TScript script)
{
	auto& arr = global[(int)type];
	arr.insert((after_index + 1 == arr.size()) ? arr.end() : (arr.begin() + after_index + 1), script);
}

void TEventsEditor::GlobalRemove(GlobalCallbackType type, int index)
{
	global[(int)type].erase(global[(int)type].begin() + index);
}

int TEventsEditor::GlobalKeyGetCount(GlobalKeyCallbackType type)
{
	return global_key[(int)type].size();
}

std::tuple<TKey, TScript>& TEventsEditor::GlobalKeyGet(GlobalKeyCallbackType type, int index)
{
	return global_key[(int)type][index];
}

void TEventsEditor::GlobalKeyInsert(GlobalKeyCallbackType type, TKey key, int after_index, TScript script)
{
	auto& arr = global_key[(int)type];
	ArrInsert(arr, after_index, std::tuple<TKey, TScript>(key,script));
}

void TEventsEditor::GlobalKeyRemove(GlobalKeyCallbackType type, int index)
{
	global_key[(int)type].erase(global_key[(int)type].begin() + index);
}

int TEventsEditor::ClassGetCount(ClassCallbackType type)
{
	return class_callbacks[(int)type].size();
}

std::tuple<std::string, TScript>& TEventsEditor::ClassGet(ClassCallbackType type, int index)
{
	return class_callbacks[(int)type][index];
}

void TEventsEditor::ClassInsert(ClassCallbackType type, std::string class_name, int after_index, TScript script)
{
	auto& arr = class_callbacks[(int)type];
	ArrInsert(arr, after_index, std::tuple<std::string, TScript>(class_name, script));
}

void TEventsEditor::ClassRemove(ClassCallbackType type, int index)
{
	class_callbacks[(int)type].erase(class_callbacks[(int)type].begin() + index);
}

int TEventsEditor::ClassKeyGetCount(ClassKeyCallbackType type)
{
	return class_key[(int)type].size();
}

std::tuple<TKey, TScript, std::string>& TEventsEditor::ClassKeyGet(ClassKeyCallbackType type, int index)
{
	return class_key[(int)type][index];
}

void TEventsEditor::ClassKeyInsert(ClassKeyCallbackType type, TKey key, std::string class_name, int after_index, TScript script)\
{
	auto& arr = class_key[(int)type];
	ArrInsert(arr, after_index, std::tuple<TKey, TScript, std::string>(key, script, class_name));
}

void TEventsEditor::ClassKeyRemove(ClassKeyCallbackType type, int index)
{
	class_key[(int)type].erase(class_key[(int)type].begin() + index);
}


int TEventsEditor::OnCollideGetCount()
{
	return on_collide.size();
}

TSpriteWithClassCollide& TEventsEditor::OnCollideGet(int index)
{
	return on_collide[index];
}

void TEventsEditor::OnCollideInsert(int after_index, std::string source_class, int sprite, std::string  obstancle_class, TScript callback)
{
	auto& arr = on_collide;
	ArrInsert(arr, after_index, TSpriteWithClassCollide(source_class, sprite, obstancle_class, callback));
}

void TEventsEditor::OnCollideRemove(int index)
{
	on_collide.erase(on_collide.begin() + index);
}