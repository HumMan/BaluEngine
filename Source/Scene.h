#pragma once

#include "Class.h"
#include "Layers.h"

#include "../../BaluLib/Source/BVolumes/AABB.h"
#include "../../BaluLib/Source/BVolumes/OBB.h"

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

class TBaluScene : public EngineInterface::IBaluScene, public EngineInterface::IBaluWorldObject
{
public:
	class TClassInstance : public EngineInterface::IBaluSceneClassInstance
	{
		TBaluClass* balu_class;
		//std::string tag;
		TBaluTransform transform;
		TVec2 scale;
	public:
		TClassInstance()
		{
			balu_class = nullptr;
		}
		TClassInstance(TBaluClass* balu_class)
		{
			this->transform = TBaluTransform(TVec2(0, 0), TRot(0));
			this->scale = TVec2(1, 1);
			this->balu_class = balu_class;
		}
		void SetTransform(TBaluTransform transform)
		{
			this->transform = transform;
		}
		void SetScale(TVec2 scale)
		{
			this->scale = scale;
		}
		TBaluTransform GetTransform()
		{
			return transform;
		}
		TVec2 GetScale()
		{
			return scale;
		}
		TBaluClass* GetClass()
		{
			return balu_class;
		}
		void Save(pugi::xml_node& parent_node, const int version);
		void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
	};
private:
	std::vector<std::unique_ptr<TClassInstance>> instances;
	std::string scene_name;

	std::map<std::string, TViewport> viewports;

	TLayersManager layers;

	TProperties properties;
public:
	EngineInterface::IProperties* GetProperties()
	{
		return &properties;
	}
	
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
	void Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world);
};
