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

		virtual void MouseDown(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
		virtual void MouseMove(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
		virtual void MouseUp(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
		virtual void MouseVerticalWheel(int amount)=0;
	};
}