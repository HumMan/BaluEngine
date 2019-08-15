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
			virtual std::shared_ptr < IScene> RunScene(WorldDef::IScene* scene_source) = 0;
			//virtual IScene* RunScene() = 0;

			virtual void StopScene(std::shared_ptr < IScene>) = 0;

			virtual int GetSceneCount() = 0;
			virtual std::shared_ptr < IScene> GetScene(int index) = 0;

			virtual std::shared_ptr < IComposer> GetComposer() = 0;

			virtual void SetCollideListener(ISceneContactListener* contacts_listener) = 0;

			virtual ~IWorld() {}
		};

		BALUENGINEDLL_API std::shared_ptr<IWorld> CreateWorld(WorldDef::IWorld* source, TResources* resources, std::string assets_dir);
		BALUENGINEDLL_API std::shared_ptr<IEventsEditorInstance> CreateEventsEditor(std::shared_ptr<IWorld> world, WorldDef::IEventsEditor* source);

		BALUENGINEDLL_API void GenerateScriptBindings(std::string output_path);
	}
}


