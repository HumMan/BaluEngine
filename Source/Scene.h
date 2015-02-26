#pragma once

#include "Class.h"
#include "Layers.h"

#include "../../BaluLib/Source/BVolumes/AABB.h"
#include "../../BaluLib/Source/BVolumes/OBB.h"

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
		TVec2 scale;
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
	};
private:
	std::vector<std::unique_ptr<TClassInstance>> instances;
	std::string scene_name;

	std::map<std::string, TViewport> viewports;

	TLayersManager layers;
public:

	TVec2 FromViewportToScene(EngineInterface::IViewport* viewport, TVec2 viewport_coord);
	TVec2 FromSceneToViewport(EngineInterface::IViewport* viewport, TVec2 scene_coord);

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
