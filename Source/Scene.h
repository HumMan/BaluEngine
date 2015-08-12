#pragma once

#include "Class.h"
#include "Layers.h"

#include "../../BaluLib/Source/BVolumes/AABB.h"
#include "../../BaluLib/Source/BVolumes/OBB.h"

#include "EngineInterfaces\IScene.h"

class TViewport : public EngineInterface::IViewport
{
	TBaluTransform transform;
	float aspect; //отношение высоты к ширине (0.5 широкий экран)
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

class TBaluSceneClassInstance : public EngineInterface::IBaluSceneClassInstance, public TSceneObject
{
	TBaluClass* balu_class;
	TBaluTransformWithScale transform;
public:
	static const char* FactoryName()
	{
		return "ClassInstance";
	}
	const char* GetFactoryName()
	{
		return FactoryName();
	}
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
	TBaluTransformWithScale GetTransformWithScale()
	{
		return transform;
	}
	TBaluClass* GetClass()
	{
		return balu_class;
	}
	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	static TSceneObject* Clone()
	{
		return new TBaluSceneClassInstance();
	}
};
REGISTER_FACTORY_CLASS(SceneObjectFactory,TBaluSceneClassInstance)
//static bool TBaluSceneClassInstance_registered = SceneObjectFactory::Register(TBaluSceneClassInstance::FactoryName(), TBaluSceneClassInstance::Clone);

class TBaluScene : public EngineInterface::IBaluScene, public EngineInterface::IBaluWorldObject
{
private:
	std::vector<std::unique_ptr<TSceneObject>> instances;
	std::string scene_name;

	std::map<std::string, TViewport> viewports;

	TLayersManager layers;

	TProperties properties;
	TBaluWorld* world;
public:
	TLayersManager& GetLayers()
	{
		return layers;
	}
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
	TSceneObject* GetInstance(int index);

	TSceneObject* CreateInstance(TBaluClass* balu_class);
	TSceneObject* CreateInstance(EngineInterface::IBaluClass* balu_class);

	void DestroyInstance(TSceneObject*);

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};
