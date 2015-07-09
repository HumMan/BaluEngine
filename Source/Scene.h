#pragma once

#include "Class.h"
#include "Layers.h"

#include "../../BaluLib/Source/BVolumes/AABB.h"
#include "../../BaluLib/Source/BVolumes/OBB.h"

#include "EngineInterfaces\IScene.h"

class TViewport : public EngineInterface::IViewport
{
	TBaluTransform transform;
	float aspect; //��������� ������ � ������ (0.5 ������� �����)
	float width;
public:
	void SetTransform(TBaluTransform transform);
	TBaluTransform GetTransform()
	{
		return transform;
	}
	void SetAspectRatio(float aspect);
	void SetWidth(float width);
	TAABB2 GetAABB();
	TVec2 GetSize()
	{
		return TVec2(width, width * aspect);
	}
	void SetSize(TVec2 size)
	{
		width = size[0];
		aspect = size[1] / size[0];
	}

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};

class TBaluSceneClassInstance : public EngineInterface::IBaluSceneClassInstance
{
	TSceneObject* balu_class;
	TBaluTransformWithScale transform;
public:
	TBaluSceneClassInstance()
	{
		balu_class = nullptr;
	}
	TBaluSceneClassInstance(TBaluClass* balu_class)
	{
		this->balu_class = balu_class;
	}
	void SetTransform(TBaluTransform transform)
	{
		this->transform.transform = transform;
	}
	void SetScale(TVec2 scale)
	{
		this->transform.scale = scale;
	}
	TBaluTransform GetTransform()
	{
		return transform.transform;
	}
	TVec2 GetScale()
	{
		return transform.scale;
	}
	TSceneObject* GetClass()
	{
		return balu_class;
	}
	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};

class TBaluScene : public EngineInterface::IBaluScene, public EngineInterface::IBaluWorldObject
{
private:
	std::vector<std::unique_ptr<TBaluSceneClassInstance>> instances;
	std::string scene_name;

	std::map<std::string, TViewport> viewports;

	TLayersManager layers;

	TProperties properties;
	TBaluWorld* world;
public:
	TBaluScene(){}
	TBaluScene(const char* name, TBaluWorld* world)
	{
		this->world = world;
		this->scene_name = name;
	}
	EngineInterface::IProperties* GetProperties()
	{
		return &properties;
	}
	
	TViewport* CreateViewport(std::string name);
	TViewport* FindViewport(std::string name);

	std::string GetName();
	void SetName(std::string name);

	int GetInstancesCount();
	TBaluSceneClassInstance* GetInstance(int index);

	TBaluSceneClassInstance* CreateInstance(TBaluClass* balu_class);
	EngineInterface::IBaluSceneClassInstance* CreateInstance(EngineInterface::IBaluClass* balu_class);

	void DestroyInstance(TBaluSceneClassInstance*);
	void DestroyInstance(EngineInterface::IBaluSceneClassInstance* instance);

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};
