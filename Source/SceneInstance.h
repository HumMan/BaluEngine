#pragma once

#include "Scene.h"
#include "ClassInstance.h"

class TBaluSceneInstance
{
private:
	TBaluScene* source;
	std::vector<std::unique_ptr<TBaluInstance>> instances;
public:
	TBaluSceneInstance(TBaluScene* source);
	TBaluSceneInstance(TBaluSceneInstance&& right);

	TBaluInstance* CreateInstance(TBaluClass* use_class);

	TVec2 WorldToScene(const TVec2& v);
	TVec2 SceneToWorld(const TVec2& v);
	
	void QueryAABB(TAABB2 frustum, std::vector<TBaluSpritePolygonInstance>& results);
};
