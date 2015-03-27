#pragma once

#include "IScene.h"
#include "ISceneInstance.h"
#include "IWorld.h"

namespace EngineInterface
{
	class IBaluWorldInstance
	{
	public:
		virtual IBaluWorld* GetSource()=0;
		virtual IBaluSceneInstance* RunScene(IBaluScene* scene_source)=0;
		virtual void StopScene(IBaluSceneInstance*)=0;

		virtual void MouseDown(TMouseEventArgs e) = 0;
		virtual void MouseMove(TMouseEventArgs e) = 0;
		virtual void MouseUp(TMouseEventArgs e) = 0;
		virtual void MouseVerticalWheel(int amount)=0;
	};

	class IResources;
}

BALUENGINEDLL_API EngineInterface::IBaluWorldInstance* CreateWorldInstance(EngineInterface::IBaluWorld* source, EngineInterface::IResources* resources);
BALUENGINEDLL_API void DestroyWorldInstance(EngineInterface::IBaluWorldInstance* world);