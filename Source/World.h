#pragma once

#include "Material.h"
#include "Sprite.h"
#include "Class.h"
#include "Scene.h"

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

class TBaluWorld : public EngineInterface::IBaluWorld
{
private:
	friend class TBaluWorldInstance;

	std::map<std::string, TBaluMaterial> materials;
	std::map<std::string, TBaluSprite> sprites;
	std::map<std::string, TBaluClass> classes;
	std::map<std::string, TBaluScene> scenes;

	TBaluPhysShapeFactory shape_factory;

	//TODO такие колбэки должны задаваться в worldInstance, а здесь только исходники скриптов
	std::vector<CallbackWithData<MouseCallback>> 
		mouse_down_callbacks,
		mouse_up_callbacks,
		mouse_move_callbacks;

	TCallbacksActiveType callback_active_type;

	template<class T, class M>
	std::vector<std::pair<std::string, T*>> GetPairsFromMap(M& map)
	{
		std::vector<std::pair<std::string, T*>> result;
		result.reserve(map.size());
		for (auto& v : map)
		{
			std::pair<std::string, T*> temp;
			temp.first = v.first;
			temp.second = &v.second;
			result.push_back(temp);
		}
		return result;
	}

	//CallbackWithData<RenderWorldCallback> render_world_callback;
	std::vector<CallbackWithData<OnStartWorldCallback>> on_start_world_callback;
	std::vector<CallbackWithData<ViewportResizeCallback>> viewport_resize_callback;

public:
	TBaluWorld();
	~TBaluWorld();
	TCallbacksActiveType& GetCallbacksActiveType()
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

	void DestroySprite(const char* class_name);
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
		return GetScenes()[0].second;
	}
	
	std::vector<std::pair<std::string, EngineInterface::IBaluMaterial*>> GetMaterials()
	{
		return GetPairsFromMap<EngineInterface::IBaluMaterial>(materials);
	}
	std::vector<std::pair<std::string, EngineInterface::IBaluSprite*>> GetSprites()
	{
		return GetPairsFromMap<EngineInterface::IBaluSprite>(sprites);
	}
	std::vector<std::pair<std::string, EngineInterface::IBaluClass*>> GetClasses()
	{
		return GetPairsFromMap<EngineInterface::IBaluClass>(classes);
	}
	std::vector<std::pair<std::string, EngineInterface::IBaluScene*>> GetScenes()
	{
		return GetPairsFromMap<EngineInterface::IBaluScene>(scenes);
	}

	TBaluPhysShapeFactory* GetPhysShapeFactory();

	//void OnKeyDown(TKey key, KeyDownCallback callback);

	void AddOnMouseDown(CallbackWithData<MouseCallback>);
	void AddOnMouseUp(CallbackWithData<MouseCallback>);
	void AddOnMouseMove(CallbackWithData<MouseCallback>);

	std::vector<CallbackWithData<MouseCallback>>& GetOnMouseDown();
	std::vector<CallbackWithData<MouseCallback>>& GetOnMouseUp();
	std::vector<CallbackWithData<MouseCallback>>& GetOnMouseMove();

	void RemoveOnMouseDown(int index);
	void RemoveOnMouseUp(int index);
	void RemoveOnMouseMove(int index);

	void AddOnWorldStart(CallbackWithData<OnStartWorldCallback> callback);
	std::vector<CallbackWithData<OnStartWorldCallback>>& GetOnWorldStart();
	void RemoveOnWorldStart(int index);
	
	void AddOnViewportResize(CallbackWithData<ViewportResizeCallback> callback);
	std::vector<CallbackWithData<ViewportResizeCallback>>& GetOnViewportResize();
	void RemoveOnViewportResize(int index);

	void SaveToXML(std::string path);
	void LoadFromXML(std::string path);

	void SaveToXML(pugi::xml_node& parent_node, const int version);
	void LoadFromXML(const pugi::xml_node& document_node, const int version);
};