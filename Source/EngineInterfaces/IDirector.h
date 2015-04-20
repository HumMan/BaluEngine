
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IResources.h"
#include "IWorldInstance.h"
#include "../Render.h"
#endif

namespace EngineInterface
{
	class IDirector;
}
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IDirector
	{
	public:
		virtual void Step(float step)=0;
		virtual void SetWorldInstance(IBaluWorldInstance* world_instance)=0;
		virtual EngineInterface::IBaluWorldInstance* GetWorldInstance()=0;
		//virtual void SetRenderWorldCallback(CallbackWithData<RenderWorldCallback> callback)=0;
		//virtual void SetViewportResizeCallback(CallbackWithData<ViewportResizeCallback> callback) = 0;
		virtual void SetSymulatePhysics(bool enable)=0;
		virtual int Initialize(bool create_window)=0;
		virtual void MainLoop()=0;
		virtual IResources* GetResources()=0;
		virtual std::string GetAssetsDir() = 0;
		virtual TVec2i GetScreenSize() = 0;
		virtual void SetScreenSize(TVec2i size) = 0;
		virtual void SetViewport(TVec2i use_size)=0;
		virtual void Render()=0;

		//special only for testing
		virtual void Initialize(void* handle)=0;
		virtual void BeginFrame()=0;
		virtual void EndFrame()=0;
		//

		BALUENGINEDLL_API static EngineInterface::IDirector* CreateDirector(std::string assets_dir, std::string log_file_path);
		BALUENGINEDLL_API static void DestroyDirector(EngineInterface::IDirector* director);
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IDirector, "IDirector");
	MUnpackRA0(WrapPointer<IBaluWorldInstance>, WrapInterface<IDirector>, GetWorldInstance);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

}




