#include "World.h"

#include <pugixml.hpp>

using namespace pugi;

TBaluPolygonShape* TBaluPhysShapeFactory::CreatePolygonShape()
{
	return new TBaluPolygonShape();
}

TBaluCircleShape* TBaluPhysShapeFactory::CreateCircleShape(float radius)
{
	return new TBaluCircleShape(radius);
}

TBaluCircleShape* TBaluPhysShapeFactory::CreateCircleShape(float radius, TVec2 pos)
{
	return new TBaluCircleShape(radius,pos);
}

TBaluBoxShape* TBaluPhysShapeFactory::CreateBoxShape(float width, float height)
{
	return new TBaluBoxShape(width, height);
}

//void TScreen::AddView(TView view)
//{
//	views.push_back(view);
//}
//
//int TScreen::GetViewsCount()
//{
//	return views.size();
//}
//
//TView TScreen::GetView(int i)
//{
//	return views[i];
//}
//
//void TScreen::RemoveView(int i)
//{
//	views.erase(views.begin()+i);
//}

TBaluWorld::TBaluWorld()
{
	callback_active_type.active_type = 0;
}

template<class T, class find_array>
bool TryFindT(find_array& map, const char* class_name, T*& result)
{
	auto iter = map.find(class_name);
	if (iter == map.end())
		return false;
	else
	{
		result = &iter->second;
		return true;
	}
}

template<class T, class I, class find_array>
bool TryFindI(find_array& map, const char* class_name, I*& result)
{
	T* r;
	auto result0 = TryFindT<T>(map, class_name, r);
	result = static_cast<I*>(r);
	return result0;
}

bool TBaluWorld::TryFind(const char* class_name, TBaluClass*& result)
{
	return TryFindT<TBaluClass>(classes, class_name, result);
}

bool TBaluWorld::TryFind(const char* material_name, EngineInterface::IBaluMaterial*& result)
{
	return TryFindI<TBaluMaterial, EngineInterface::IBaluMaterial>(materials, material_name, result);
}
bool TBaluWorld::TryFind(const char* sprite_name, EngineInterface::IBaluSprite*& result)
{
	return TryFindI<TBaluSprite, EngineInterface::IBaluSprite>(sprites, sprite_name, result);
}
bool TBaluWorld::TryFind(const char* scene_name, EngineInterface::IBaluScene*& result)
{
	return TryFindI<TBaluScene, EngineInterface::IBaluScene>(scenes, scene_name, result);
}

bool TBaluWorld::TryFind(const char* class_name, EngineInterface::IBaluClass*& result)
{
	return TryFindI<TBaluClass, EngineInterface::IBaluClass>(classes, class_name, result);
}

TBaluMaterial* TBaluWorld::CreateMaterial(const char* mat_name)
{
	auto iter = materials.find(mat_name);
	if (iter == materials.end())
	{
		materials[mat_name].SetName(mat_name);
		return &materials[mat_name];
	}
	else
	{
		throw std::invalid_argument("Материал с данным имененем уже существует");
	}
}

TBaluSprite* TBaluWorld::CreateSprite(const char* sprite_name)
{
	auto iter = sprites.find(sprite_name);
	if (iter == sprites.end())
	{
		sprites[sprite_name].SetName(sprite_name);
		return &sprites[sprite_name];
	}
	else
	{
		throw std::invalid_argument("Спрайт с данным имененем уже существует");
	}
}
TBaluClass* TBaluWorld::CreateClass(const char* class_name)
{
	auto iter = classes.find(class_name);
	if (iter == classes.end())
	{
		classes[class_name].SetName(class_name);
		return &classes[class_name];
	}
	else
	{
		throw std::invalid_argument("Класс с данным имененем уже существует");
	}
}
TBaluScene* TBaluWorld::CreateScene(const char* scene_name)
{
	auto iter = scenes.find(scene_name);
	if (iter == scenes.end())
	{
		scenes[scene_name].SetName(scene_name);
		return &scenes[scene_name];
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем уже существует");
	}
}

void TBaluWorld::DestroySprite(const char* sprite_name)
{
	auto iter = sprites.find(sprite_name);
	if (iter != sprites.end())
	{
		sprites.erase(iter);
	}
	else
	{
		throw std::invalid_argument("Спрайта с данным имененм не существует");
	}
}

void TBaluWorld::DestroyClass(const char* class_name)
{
	auto iter = classes.find(class_name);
	if (iter != classes.end())
	{
		classes.erase(iter);
	}
	else
	{
		throw std::invalid_argument("Класса с данным имененм не существует");
	}
}

void TBaluWorld::DestroyScene(const char* scene_name)
{
	auto iter = scenes.find(scene_name);
	if (iter != scenes.end())
	{
		scenes.erase(iter);
	}
	else
	{
		throw std::invalid_argument("Сцены с данным имененм не существует");
	}
}



TBaluMaterial* TBaluWorld::GetMaterial(const char* scene_name)
{
	auto iter = materials.find(scene_name);
	if (iter != materials.end())
	{
		return &iter->second;
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем отсутсвует");
	}
}

TBaluSprite* TBaluWorld::GetSprite(const char* scene_name)
{
	auto iter = sprites.find(scene_name);
	if (iter != sprites.end())
	{
		return &iter->second;
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем отсутсвует");
	}
}

TBaluClass* TBaluWorld::GetClass(const char* scene_name)
{
	auto iter = classes.find(scene_name);
	if (iter != classes.end())
	{
		return &iter->second;
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем отсутсвует");
	}
}

TBaluScene* TBaluWorld::GetScene(const char* scene_name)
{
	auto iter = scenes.find(scene_name);
	if (iter != scenes.end())
	{
		return &iter->second;
	}
	else
	{
		throw std::invalid_argument("Сцена с данным имененем отсутсвует");
	}
}

TBaluPhysShapeFactory* TBaluWorld::GetPhysShapeFactory()
{
	return &shape_factory;
}

template<class T, class ArrayType>
void AddCallback(T callback, ArrayType& array)
{
	for (auto& v : array)
		if (v == callback)
			assert(false);
	array.push_back(callback);
}

template<class T, class ArrayType>
void RemoveCallback(T callback, ArrayType& array)
{
	bool exists = false;
	for (int i = 0; i < array.size();i++)
		if (array[i] == callback)
		{
			array.erase(array.begin() + i);
			return;
		}
	assert(false);
	return;
}

void TBaluWorld::AddOnMouseDown(CallbackWithData<MouseUpDownCallback> callback)
{
	AddCallback(callback, mouse_down_callbacks);
}

void TBaluWorld::AddOnMouseUp(CallbackWithData<MouseUpDownCallback> callback)
{
	AddCallback(callback, mouse_up_callbacks);
}

void TBaluWorld::AddOnMouseMove(CallbackWithData<MouseMoveCallback> callback)
{
	AddCallback(callback, mouse_move_callbacks);
}

void TBaluWorld::RemoveOnMouseDown(CallbackWithData<MouseUpDownCallback> callback)
{
	RemoveCallback(callback, mouse_down_callbacks);
}

void TBaluWorld::RemoveOnMouseUp(CallbackWithData<MouseUpDownCallback> callback)
{
	RemoveCallback(callback, mouse_up_callbacks);
}

void TBaluWorld::RemoveOnMouseMove(CallbackWithData<MouseMoveCallback> callback)
{
	RemoveCallback(callback, mouse_move_callbacks);
}

void TBaluWorld::SaveToXML(std::string path)
{
	xml_document doc;
	auto doc_el = doc.append_child("BaluEditorWorldFile");
	SaveToXML(doc_el, 1);
	doc.save_file(path.c_str());
}

void TBaluWorld::LoadFromXML(std::string path)
{
	xml_document doc;
	doc.load_file(path.c_str());
	LoadFromXML(doc.child("BaluEditorWorldFile"), 1);
}

std::vector < std::pair<const char*, PropertyClone>> properties_registry;

bool PropertiesFactory::Register(const char* name, PropertyClone clone)
{
	properties_registry.push_back(std::pair<const char*, PropertyClone>(name, clone));
	return true;
}

TProperty* PropertiesFactory::Create(const char* name)
{
	for (int i = 0; i < properties_registry.size(); i++)
		if (strcmp(properties_registry[i].first, name) == 0)
			return properties_registry[i].second();
	throw std::invalid_argument("Тип не зарегистрирован");
}
