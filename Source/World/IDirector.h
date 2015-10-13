#pragma once

#include "IResources.h"
#include "IWorldInstance.h"
#include <World\Render.h>

namespace EngineInterface
{
	class IDirector;
	class IResources;
	class IBaluWorldInstance;
}

namespace EngineInterface
{

	class IDirector
	{
	public:
		virtual void Step(float step)=0;
		virtual void SetWorldInstance(IBaluWorldInstance* world_instance)=0;
		virtual IBaluWorldInstance* GetWorldInstance()=0;
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

		BALUENGINEDLL_API static IDirector* CreateDirector(std::string assets_dir);
		BALUENGINEDLL_API static void DestroyDirector(IDirector* director);
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TGameInternal;
	class TBaluWorldInstance;

	using namespace EngineInterface;

	class TRender;

	class TDirector: public IDirector
	{
		std::unique_ptr < TGameInternal > p;


	public:
		void Step(float step);

		//special only for testing
		void Initialize(void* handle);
		void BeginFrame();
		void EndFrame();
		//

		TDirector(std::string assets_dir);
		void SetWorldInstance(TBaluWorldInstance* world_instance);
		void SetWorldInstance(IBaluWorldInstance* world_instance);
		IBaluWorldInstance* GetWorldInstance();

		int Initialize(bool create_window);
		TResources* GetResources();
		~TDirector();

		std::string GetAssetsDir();
		TVec2i GetScreenSize();
		void SetScreenSize(TVec2i size);

		//used if create_windows==true
		void MainLoop();
		void SetSymulatePhysics(bool enable);

		//used if create_windows==false
		void Render();
		void SetViewport(TVec2i use_size);
};
#endif

}




