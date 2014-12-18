#pragma once

#include "Class.h"

class TBaluScene
{
public:
	class TClassInstance
	{
		public:
		TBaluClass* balu_class;
		std::string tag;
		TBaluTransform transform;
	};
private:
	std::vector<std::unique_ptr<TClassInstance>> instances;
	std::string scene_name;
public:
	std::string GetName()
	{
		return scene_name;
	}

	TBaluScene::TClassInstance* CreateInstance(char* class_name);

	TVec2 WorldToScene(const TVec2& v);
	TVec2 SceneToWorld(const TVec2& v);
};
