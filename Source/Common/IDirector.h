#pragma once

#include "../WorldInstance/Interface.h"

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
			virtual void SetWorldInstance(std::shared_ptr < IWorld> world_instance) = 0;
			virtual void SetEventsEditor(std::shared_ptr<IEventsEditorInstance> events_editor) = 0;
			virtual std::shared_ptr < IWorld> GetWorld() = 0;
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
			virtual ~IDirector() {}

			BALUENGINEDLL_API static std::shared_ptr < IDirector> Create(std::string assets_dir);
			BALUENGINEDLL_API static void ClearStaticData();

			BALUENGINEDLL_API static std::wstring as_wide(std::string utf_8_string);
			BALUENGINEDLL_API static std::string as_utf8(std::wstring wide_string);
		};
	}
}




