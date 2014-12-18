#pragma once

#include "SceneInstance.h"

class TBaluWorldInstance
{
private:
	std::vector<std::unique_ptr<TBaluSceneInstance>> instances;
public:
};