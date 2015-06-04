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
	void Load(const pugi::xml_node& instance_node, const int version);
};

class TBaluScene : public EngineInterface::IBaluScene, public EngineInterface::IBaluWorldObject
{
public:
	class TClassInstance : public EngineInterface::IBaluSceneClassInstance
	{
		std::string class_name;
		TBaluTransformWithScale transform;
		TBaluScene* parent;
	public:
		TClassInstance()
		{
		}
		TClassInstance(std::string class_name)
		{
			this->class_name = class_name;
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
		std::string GetClassName()
		{
			return class_name;
		}
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version);
	};
private:
	std::vector<std::unique_ptr<TClassInstance>> instances;

	std::map<std::string, TViewport> viewports;

	TLayersManager layers;

	TProperties properties;

	TBaluWorld* world;
public:
	TBaluScene(){}
	TBaluScene(TBaluWorld* world)
	{
		this->world = world;
	}
	EngineInterface::IProperties* GetProperties()
	{
		return &properties;
	}
	TBaluWorld* GetWorld();
	TViewport* CreateViewport(std::string name);
	TViewport* FindViewport(std::string name);

	std::string GetName();
	void SetName(std::string name);

	int GetInstancesCount();
	TClassInstance* GetInstance(int index);

	TBaluScene::TClassInstance* CreateInstance(TBaluClass* balu_class);
	EngineInterface::IBaluSceneClassInstance* CreateInstance(EngineInterface::IBaluClass* balu_class);

	void DestroyInstance(TBaluScene::TClassInstance*);	
	void DestroyInstance(EngineInterface::IBaluSceneClassInstance* instance);

	void Save(pugi::xml_node& parent_node, const int version);
	void Load(const pugi::xml_node& instance_node, const int version);
};
