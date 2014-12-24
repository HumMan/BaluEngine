#pragma once

#include "Class.h"

#include "../BaluLib/Source/BVolumes/AABB.h"
#include "../BaluLib/Source/BVolumes/OBB.h"

class TViewport
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

class TBaluScene
{
public:
	class TClassInstance
	{
		public:
		TBaluClass* balu_class;
		std::string tag;
		TBaluTransform transform;
		TClassInstance(TBaluClass* balu_class)
		{
			this->balu_class = balu_class;
		}
	};
private:
	std::vector<std::unique_ptr<TClassInstance>> instances;
	std::string scene_name;

	std::map<std::string, TViewport> viewports;
public:

	TViewport* CreateViewport(std::string name);

	std::string GetName();
	void SetName(std::string name);

	int GetInstancesCount();
	TClassInstance* GetInstance(int index);

	TBaluScene::TClassInstance* CreateInstance(TBaluClass* balu_class);
	void DestroyIntance(TBaluScene::TClassInstance*);
};
