#pragma once

#include "Scene.h"
#include "ClassInstance.h"

class TBaluSceneInstance
{
private:
	TBaluScene* source;
	std::vector<std::unique_ptr<TBaluInstance>> instances;
public:
	TBaluSceneInstance(){}
	TBaluSceneInstance(TBaluSceneInstance&& right)
	{
		instances = std::move(right.instances);
	}

	TBaluInstance* CreateInstance(char* class_name);

	TVec2 WorldToScene(const TVec2& v);
	TVec2 SceneToWorld(const TVec2& v);
	
	void QueryAABB(TAABB frustum, std::vector<TSpritePolyInstance);
};
