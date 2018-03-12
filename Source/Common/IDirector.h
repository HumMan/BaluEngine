#pragma once

#include "WorldInstance/Interface.h"

#include "../Interfaces/ExportMacro.h"

#include "../Render/Render.h"

namespace BaluEngine
{
	namespace WorldInstance
	{

		class IDirector
		{
		public:
			virtual void Step(float step) = 0;
			virtual void SetWorldInstance(IWorld* world_instance) = 0;
			virtual IWorld* GetWorld() = 0;
			//virtual void SetRenderWorldCallback(CallbackWithData<RenderWorldCallback> callback)=0;
			//virtual void SetViewportResizeCallback(CallbackWithData<ViewportResizeCallback> callback) = 0;
			virtual void SetSymulatePhysics(bool enable) = 0;
			virtual int Initialize(bool create_window) = 0;
			virtual void MainLoop() = 0;
			virtual TResources* GetResources() = 0;
			virtual std::string GetAssetsDir() = 0;
			virtual BaluLib::TVec2i GetScreenSize() = 0;
			virtual void SetScreenSize(BaluLib::TVec2i size) = 0;
			virtual void SetViewport(BaluLib::TVec2i use_size) = 0;
			virtual void Render() = 0;

			//special only for testing
			virtual void Initialize(void* handle) = 0;
			virtual void BeginFrame() = 0;
			virtual void EndFrame() = 0;
			//

			BALUENGINEDLL_API static IDirector* CreateDirector(std::string assets_dir);
			BALUENGINEDLL_API static void DestroyDirector(IDirector* director, bool clear_static_data);
		};
	}
}




