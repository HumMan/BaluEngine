#pragma once

#include "IResources.h"

#include "IWorldInstance.h"

#include "../Render.h"

typedef void(*RenderWorldCallback)(EngineInterface::IBaluWorldInstance* world, TRender* render);

namespace EngineInterface
{
	class IDirector
	{
	public:
		virtual void SetWorldInstance(IBaluWorldInstance* world_instance)=0;
		virtual void SetRenderWorldCallback(RenderWorldCallback callback)=0;
		virtual int Initialize()=0;
		virtual void MainLoop()=0;
		virtual IResources* GetResources()=0;
	};
}