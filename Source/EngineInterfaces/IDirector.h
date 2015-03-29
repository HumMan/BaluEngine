#pragma once

#include "IResources.h"

#include "IWorldInstance.h"

#include "../Render.h"

namespace EngineInterface
{
	class IDirector;
}

typedef void(*RenderWorldCallback)(TCallbackData* data, EngineInterface::IDirector* director, EngineInterface::IBaluWorldInstance* world, TRender* render);
typedef void(*VieportResizeCallback)(EngineInterface::IDirector* director, TVec2i old_size, TVec2i new_size);

namespace EngineInterface
{
	class IDirector
	{
	public:
		virtual void Step(float step)=0;
		virtual void SetWorldInstance(IBaluWorldInstance* world_instance)=0;
		virtual EngineInterface::IBaluWorldInstance* GetWorldInstance()=0;
		virtual void SetRenderWorldCallback(CallbackWithData<RenderWorldCallback> callback)=0;
		virtual void SetViewportResizeCallback(VieportResizeCallback callback) = 0;
		virtual void SetSymulatePhysics(bool enable)=0;
		virtual int Initialize(bool create_window)=0;
		virtual void MainLoop()=0;
		virtual IResources* GetResources()=0;
		virtual std::string GetBasePath() = 0;
		virtual TVec2i GetScreenSize() = 0;
		virtual void SetScreenSize(TVec2i size) = 0;
		virtual void SetViewport(TVec2i use_size)=0;
		virtual void Render()=0;

		//special only for testing
		virtual void Initialize(void* handle)=0;
		virtual void BeginFrame()=0;
		virtual void EndFrame()=0;
		//
	};
}

BALUENGINEDLL_API EngineInterface::IDirector* CreateDirector();
BALUENGINEDLL_API void DestroyDirector(EngineInterface::IDirector* director);
