#pragma once

#include "Scene.h"
#include "ClassInstance.h"

class TBaluSceneInstance
{
private:
	std::unique_ptr<b2World> phys_world;
	TBaluScene* source;
	std::vector<std::unique_ptr<TBaluInstance>> instances;

	std::map<std::string, TViewport> viewports;
public:

	TViewport* GetViewport(std::string name);

	TBaluSceneInstance(TBaluScene* source);
	TBaluSceneInstance(TBaluSceneInstance&& right);

	TBaluInstance* CreateInstance(TBaluClass* use_class);

	TVec2 WorldToScene(const TVec2& v);
	TVec2 SceneToWorld(const TVec2& v);
	
	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance*>& results);

	void OnStep(float step);
};
