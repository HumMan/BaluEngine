#pragma once

#include "Class.h"
#include "Layers.h"

#include "../BaluLib/Source/BVolumes/AABB.h"
#include "../BaluLib/Source/BVolumes/OBB.h"

class TViewport : public EngineInterface::IViewport
{
	TBaluTransform transform;
	float aspect;
	float width;
public:
	void SetTransform(TBaluTransform transform);
	void SetAspectRatio(float aspect);
	void SetWidth(float width);
	TAABB2 GetAABB();
};

class TBaluScene: public EngineInterface::IBaluScene
{
public:
	class TClassInstance : public EngineInterface::IBaluSceneClassInstance
	{
		public:
		TBaluClass* balu_class;
		std::string tag;
		TBaluTransform transform;
		TClassInstance(TBaluClass* balu_class)
		{
			this->balu_class = balu_class;
		}
		void SetTransform(TBaluTransform transform)
		{
			this->transform = transform;
		}
	};
private:
	std::vector<std::unique_ptr<TClassInstance>> instances;
	std::string scene_name;

	std::map<std::string, TViewport> viewports;

	TLayersManager layers;
public:

	TViewport* CreateViewport(std::string name);

	std::string GetName();
	void SetName(std::string name);

	int GetInstancesCount();
	TClassInstance* GetInstance(int index);

	TBaluScene::TClassInstance* CreateInstance(TBaluClass* balu_class);
	EngineInterface::IBaluSceneClassInstance* CreateInstance(EngineInterface::IBaluClass* balu_class);

	void DestroyInstance(TBaluScene::TClassInstance*);	
	void DestroyInstance(EngineInterface::IBaluSceneClassInstance* instance);
};
