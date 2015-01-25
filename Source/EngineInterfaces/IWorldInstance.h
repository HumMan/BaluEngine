#pragma once

#include "IScene.h"
#include "ISceneInstance.h"

namespace EngineInterface
{
	class IBaluWorldInstance
	{
	public:
		virtual IBaluSceneInstance* RunScene(IBaluScene* scene_source)=0;
		virtual void StopScene(IBaluSceneInstance*)=0;
	};
}