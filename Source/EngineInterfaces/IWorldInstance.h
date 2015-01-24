#pragma once

#include "IScene.h"
#include "ISceneInstance.h"

namespace EngineInterface
{
	class IBaluWorldInstance
	{
	public:
		virtual ~IBaluWorldInstance(){}

		IBaluSceneInstance* RunScene(IBaluScene* scene_source);
		void StopScene(IBaluSceneInstance*);
	};
}