#pragma once

#include <WorldObjects/Material/Material.h>
#include <WorldObjects/Sprite/Sprite.h>
#include <WorldObjects/Class/Class.h>
#include <WorldObjects/Scene/Scene.h>

#include <map>

#include "EngineInterfaces\IWorld.h"

class TBaluPhysShapeFactory : public EngineInterface::IBaluPhysShapeFactory
{
public:
	TBaluPolygonShape* CreatePolygonShape();
	TBaluCircleShape* CreateCircleShape(float radius);
	TBaluCircleShape* CreateCircleShape(float radius, TVec2 pos);
	TBaluBoxShape* CreateBoxShape(float width, float height);
};

namespace pugi
{
	class xml_node;
}

class TBaluWorldChangeListenerArray
{
	std::vector<TBaluWorldChangeListener*> listeners;
public:
	void OnObjectCreate(TWorldObjectType type, std::string name)
	{
		for (auto v : listeners)
			v->OnObjectCreate(type, name);
	}
	void OnObjectDestroy(TWorldObjectType type, std::string name)
	{
		for (auto v : listeners)
			v->OnObjectDestroy(type, name);
	}
	void OnObjectChange(TWorldObjectType type, std::string name)
	{
		for (auto v : listeners)
			v->OnObjectChange(type, name);
	}
	void OnSubObjectCreate(TWorldObjectType obj_type, std::string name, TWorldObjectSubType sub_obj_type, int sub_obj_index)
	{
		for (auto v : listeners)
			v->OnSubObjectCreate(obj_type, name, sub_obj_type, sub_obj_index);
	}
	void OnSubObjectDestroy(TWorldObjectType obj_type, std::string name, TWorldObjectSubType sub_obj_type, int sub_obj_index)
	{
		for (auto v : listeners)
			v->OnSubObjectDestroy(obj_type, name, sub_obj_type, sub_obj_index);
	}
	void OnSubObjectChange(TWorldObjectType obj_type, std::string name, TWorldObjectSubType sub_obj_type, int sub_obj_index)
	{
		for (auto v : listeners)
			v->OnSubObjectChange(obj_type, name, sub_obj_type, sub_obj_index);
	}
	void AddChangesListener(TBaluWorldChangeListener* listener)
	{
		auto it = std::find(listeners.begin(), listeners.end(), listener);
		assert(it == listeners.end());
		listeners.push_back(listener);
	}
	void RemoveChangesListener(TBaluWorldChangeListener* listener)
	{
		auto it = std::find(listeners.begin(), listeners.end(), listener);
		assert(it != listeners.end());
		listeners.erase(it);
	}
};

class TBaluWorld : public EngineInterface::IBaluWorld
{
private:
	friend class TBaluWorldInstance;

	std::map<std::string, std::unique_ptr<TBaluMaterial>> materials;
	std::map<std::string, std::unique_ptr<TBaluSprite>> sprites;
	std::map<std::string, std::unique_ptr<TBaluClass>> classes;
	std::map<std::string, std::unique_ptr<TBaluScene>> scenes;

	TBaluPhysShapeFactory shape_factory;

	

	TScriptActiveType callback_active_type;

	template<class T, class M>
	std::vector<T*> GetVectorFromMap(M& map)
	{
		std::vector<T*> result;
		result.reserve(map.size());
		for (auto& v : map)
		{
			result.push_back(v.second.get());
		}
		return result;
	}

	//TODO такие колбэки должны задаватьс€ в worldInstance, а здесь только исходники скриптов
	std::vector<TScript>
		mouse_down_callbacks,
		mouse_up_callbacks,
		mouse_move_callbacks;
	std::vector<TScript> on_start_world_callback;
	std::vector<TScript> viewport_resize_callback;

	TBaluWorldChangeListenerArray listeners;
public:

	virtual void AddChangesListener(TBaluWorldChangeListener* listener)
	{
		listeners.AddChangesListener(listener);
	}
	virtual void RemoveChangesListener(TBaluWorldChangeListener* listener)
	{
		listeners.RemoveChangesListener(listener);
	}

	TBaluWorld();
	~TBaluWorld();
	//TODO убрать отсюда, указывать при создании экземпл€ра мира
	TScriptActiveType& GetCallbacksActiveType()
	{
		return callback_active_type;
	}
	bool TryFind(const char* material_name, EngineInterface::IBaluMaterial*& result);
	bool TryFind(const char* sprite_name, EngineInterface::IBaluSprite*& result);
	bool TryFind(const char* scene_name, EngineInterface::IBaluScene*& result);
	bool TryFind(const char* class_name, TBaluClass*& result);
	bool TryFind(const char* class_name, EngineInterface::IBaluClass*& result);

	TBaluMaterial* CreateMaterial(const char* mat_name);
	TBaluSprite* CreateSprite(const char* sprite_name);
	TBaluClass* CreateClass(const char* class_name);
	TBaluScene* CreateScene(const char* scene_name);

	void DestroyMaterial(const char* material_name);
	void DestroySprite(const char* sprite_name);
	void DestroyClass(const char* class_name);
	void DestroyScene(const char* scene_name);	

	TBaluMaterial* GetMaterial(const char* mat_name);
	TBaluSprite* GetSprite(const char* sprite_name);
	TBaluClass* GetClass(const char* class_name);
	TBaluScene* GetScene(const char* scene_name);

	IBaluWorldObject* GetObjectByName(TWorldObjectType type, const char* name);
	std::vector<IBaluWorldObject*> GetObjects(TWorldObjectType type);
	bool ObjectNameExists(TWorldObjectType type, const char* name);
	void CreateObject(TWorldObjectType type, const char* name);
	void DestroyObject(TWorldObjectType type, const char* name);

	IBaluScene* GetScene(int index)
	{
		return GetScenes()[0];
	}
	
	std::vector<EngineInterface::IBaluMaterial*> GetMaterials()
	{
		return GetVectorFromMap<EngineInterface::IBaluMaterial>(materials);
	}
	std::vector<EngineInterface::IBaluSprite*> GetSprites()
	{
		return GetVectorFromMap<EngineInterface::IBaluSprite>(sprites);
	}
	std::vector<EngineInterface::IBaluClass*> GetClasses()
	{
		return GetVectorFromMap<EngineInterface::IBaluClass>(classes);
	}
	std::vector<EngineInterface::IBaluScene*> GetScenes()
	{
		return GetVectorFromMap<EngineInterface::IBaluScene>(scenes);
	}

	TBaluPhysShapeFactory* GetPhysShapeFactory();

	//void OnKeyDown(TKey key, KeyDownCallback callback);

	void AddOnMouseDown(TScript);
	void AddOnMouseUp(TScript);
	void AddOnMouseMove(TScript);

	std::vector<TScript>& GetOnMouseDown();
	std::vector<TScript>& GetOnMouseUp();
	std::vector<TScript>& GetOnMouseMove();

	void RemoveOnMouseDown(int index);
	void RemoveOnMouseUp(int index);
	void RemoveOnMouseMove(int index);

	void AddOnWorldStart(TScript callback);
	std::vector<TScript>& GetOnWorldStart();
	void RemoveOnWorldStart(int index);
	
	void AddOnViewportResize(TScript callback);
	std::vector<TScript>& GetOnViewportResize();
	void RemoveOnViewportResize(int index);

	void SaveToXML(std::string path);
	void LoadFromXML(std::string path);

	void SaveToXML(pugi::xml_node& parent_node, const int version);
	void LoadFromXML(const pugi::xml_node& document_node, const int version);
};