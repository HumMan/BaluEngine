#pragma once

#include "../Interfaces/ExportMacro.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		class IWorld
		{
		public:
			//virtual TResources* GetResources() = 0;


			virtual WorldDef::IWorld* GetSource() = 0;
			virtual IScene* RunScene(WorldDef::IScene* scene_source) = 0;
			//virtual IScene* RunScene() = 0;

			virtual void StopScene(IScene*) = 0;

			virtual int GetSceneCount() = 0;
			virtual IScene* GetScene(int index) = 0;

			virtual IEventsEditorInstance* GetEventsEditor() = 0;

			virtual IComposer* GetComposer() = 0;

			virtual ~IWorld() {}
		};

		BALUENGINEDLL_API IWorld* CreateWorld(WorldDef::IWorld* source, TResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message);
		BALUENGINEDLL_API void DestroyWorld(IWorld* world);

		BALUENGINEDLL_API void GenerateScriptBindings(std::string output_path);
	}
}


