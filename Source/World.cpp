#include "World.h"

#include <pugixml.hpp>

using namespace pugi;

//needed for polygon from image contruction
#include <IL/ilut.h>

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
	ilInit();
}

TBaluWorld::~TBaluWorld()
{
	ilShutDown();
}

template<class T, class find_array>
bool TryFindT(find_array& map, const char* class_name, T*& result)
{
	auto iter = map.find(class_name);
	if (iter == map.end())
		return false;
	else
	{
		result = iter->second.get();
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
		materials[mat_name]->SetName(mat_name);
		return materials[mat_name].get();
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
		sprites[sprite_name]->SetName(sprite_name);
		return sprites[sprite_name].get();
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
		classes[class_name]->SetName(class_name);
		return classes[class_name].get();
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
		scenes[scene_name]->SetName(scene_name);
		return scenes[scene_name].get();
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

template<class T, class M>
std::vector<T*> GetObjectsFromMap(M& map)
{
	std::vector<T*> result;
	for (auto& v : map)
	{
		result.push_back(v.second.get());
	}
	return result;
}

IBaluWorldObject* TBaluWorld::GetObjectByName(TWorldObjectType type, const char* name)
{
	switch (type)
	{
	case TWorldObjectType::Material:
		return materials[name].get();
		break;
	case TWorldObjectType::Sprite:
		return sprites[name].get();
		break;
	case TWorldObjectType::Class:
		return classes[name].get();
		break;
	case TWorldObjectType::Scene:
		return scenes[name].get();
		break;
	case TWorldObjectType::None:
		assert(false);
		break;
	default:
		assert(false);
		break;
	}
}

std::vector<IBaluWorldObject*> TBaluWorld::GetObjects(TWorldObjectType type)
{
	switch (type)
	{
	case TWorldObjectType::Material:
		return GetObjectsFromMap<IBaluWorldObject>(materials);
		break;
	case TWorldObjectType::Sprite:
		return GetObjectsFromMap<IBaluWorldObject>(sprites);
		break;
	case TWorldObjectType::Class:
		return GetObjectsFromMap<IBaluWorldObject>(classes);
		break;
	case TWorldObjectType::Scene:
		return GetObjectsFromMap<IBaluWorldObject>(scenes);
		break;
	case TWorldObjectType::None:
		assert(false);
		break;
	default:
		assert(false);
		break;
	}
	
}

bool TBaluWorld::ObjectNameExists(TWorldObjectType type, const char* name)
{
	switch (type)
	{
	case TWorldObjectType::Material:
		return materials.find(name) != materials.end();
		break;
	case TWorldObjectType::Sprite:
		return sprites.find(name) != sprites.end();
		break;
	case TWorldObjectType::Class:
		return classes.find(name) != classes.end();
		break;
	case TWorldObjectType::Scene:
		return scenes.find(name) != scenes.end();
		break;
	case TWorldObjectType::None:
		assert(false);
		break;
	default:
		assert(false);
		break;
	}
	//TODO rename - после перехода на shared_ptr не нужно будет заботиться о том что объект map был перемещен и нужно обновлять указатели в остальных местах (world_instance например)
}

void TBaluWorld::CreateObject(TWorldObjectType type, const char* name)
{
	switch (type)
	{
	case TWorldObjectType::Material:
		materials.emplace(std::piecewise_construct, std::make_tuple(name), std::make_tuple(name, this));
		break;
	case TWorldObjectType::Sprite:
		sprites.emplace(name, name);
		break;
	case TWorldObjectType::Class:
		classes.emplace(name, name);
		break;
	case TWorldObjectType::Scene:
		scenes.emplace(name, name);
		break;
	case TWorldObjectType::None:
		assert(false);
		break;
	default:
		assert(false);
		break;
	}
}

void TBaluWorld::DestroyObject(TWorldObjectType type, const char* name)
{
	switch (type)
	{
	case TWorldObjectType::Material:
		materials.erase(name);
		break;
	case TWorldObjectType::Sprite:
		sprites.erase(name);
		break;
	case TWorldObjectType::Class:
		classes.erase(name);
		break;
	case TWorldObjectType::Scene:
		scenes.erase(name);
		break;
	case TWorldObjectType::None:
		assert(false);
		break;
	default:
		assert(false);
		break;
	}
}

TBaluMaterial* TBaluWorld::GetMaterial(const char* scene_name)
{
	auto iter = materials.find(scene_name);
	if (iter != materials.end())
	{
		return iter->second.get();
	}
	else
	{
		throw std::invalid_argument("Материал с данным имененем отсутсвует");
	}
}

TBaluSprite* TBaluWorld::GetSprite(const char* scene_name)
{
	auto iter = sprites.find(scene_name);
	if (iter != sprites.end())
	{
		return iter->second.get();
	}
	else
	{
		throw std::invalid_argument("Спрайт с данным имененем отсутсвует");
	}
}

TBaluClass* TBaluWorld::GetClass(const char* scene_name)
{
	auto iter = classes.find(scene_name);
	if (iter != classes.end())
	{
		return iter->second.get();
	}
	else
	{
		throw std::invalid_argument("Класс с данным имененем отсутсвует");
	}
}

TBaluScene* TBaluWorld::GetScene(const char* scene_name)
{
	auto iter = scenes.find(scene_name);
	if (iter != scenes.end())
	{
		return iter->second.get();
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

void TBaluWorld::AddOnMouseDown(CallbackWithData<MouseCallback> callback)
{
	mouse_down_callbacks.push_back(callback);
}

void TBaluWorld::AddOnMouseUp(CallbackWithData<MouseCallback> callback)
{
	mouse_up_callbacks.push_back(callback);
}

void TBaluWorld::AddOnMouseMove(CallbackWithData<MouseCallback> callback)
{
	mouse_move_callbacks.push_back(callback);
}

std::vector<CallbackWithData<MouseCallback>>& TBaluWorld::GetOnMouseDown()
{
	return mouse_down_callbacks;
}
std::vector<CallbackWithData<MouseCallback>>& TBaluWorld::GetOnMouseUp()
{
	return mouse_up_callbacks;
}
std::vector<CallbackWithData<MouseCallback>>& TBaluWorld::GetOnMouseMove()
{
	return mouse_move_callbacks;
}

void TBaluWorld::RemoveOnMouseDown(int index)
{
	mouse_down_callbacks.erase(mouse_down_callbacks.begin() + index);
}

void TBaluWorld::RemoveOnMouseUp(int index)
{
	mouse_up_callbacks.erase(mouse_up_callbacks.begin() + index);
}

void TBaluWorld::RemoveOnMouseMove(int index)
{
	mouse_move_callbacks.erase(mouse_move_callbacks.begin() + index);
}

void TBaluWorld::AddOnWorldStart(CallbackWithData<OnStartWorldCallback> callback)
{
	on_start_world_callback.push_back(callback);
}

std::vector<CallbackWithData<OnStartWorldCallback>>& TBaluWorld::GetOnWorldStart()
{
	return on_start_world_callback;
}

void TBaluWorld::RemoveOnWorldStart(int index)
{
	on_start_world_callback.erase(on_start_world_callback.begin() + index);
}

void TBaluWorld::AddOnViewportResize(CallbackWithData<ViewportResizeCallback> callback)
{
	viewport_resize_callback.push_back(callback);
}

std::vector<CallbackWithData<ViewportResizeCallback>>& TBaluWorld::GetOnViewportResize()
{
	return viewport_resize_callback;
}

void TBaluWorld::RemoveOnViewportResize(int index)
{
	viewport_resize_callback.erase(viewport_resize_callback.begin() + index);
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
