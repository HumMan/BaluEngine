#pragma once

#include "IDirector.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{
			class TDirector : public IDirector
			{
				class TPrivate;
				std::unique_ptr<TPrivate> p;

			public:
				void Step(float step);

				//special only for testing
				void Initialize(void* handle);
				void BeginFrame();
				void EndFrame();
				//

				TDirector(std::string assets_dir);
				void SetWorldInstance(std::shared_ptr < IWorld> world_instance);
				void SetEventsEditor(std::shared_ptr<IEventsEditorInstance> events_editor);
				std::shared_ptr<IWorld> GetWorld();

				int Initialize(bool create_window);
				TResources* GetResources();
				~TDirector();

				std::string GetAssetsDir();
				BaluLib::TVec2i GetScreenSize();
				void SetScreenSize(BaluLib::TVec2i size);

				//used if create_windows==true
				void MainLoop();
				void SetSymulatePhysics(bool enable);

				//used if create_windows==false
				void Render();
				void SetViewport(BaluLib::TVec2i use_size);
			};
		}
	}
}




