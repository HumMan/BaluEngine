#pragma once

#include "../../Interface.h"

#include "../Composer/Composer.h"

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{


			class TWorld : public IWorld
			{
			private:
				WorldDef::IWorld* source;
				std::vector<std::unique_ptr<IScene>> scene_instances;

				//TResources* resources;

				TComposer composer;

				//std::unique_ptr<TEventsEditorInstance> events_editor;

			public:
				~TWorld();
				//IEventsEditorInstance* GetEventsEditor();

				/*TResources* GetResources()
				{
					return resources;
				}*/

				WorldDef::IWorld* GetSource();

				TWorld(WorldDef::IWorld* source, /*TResources* resources,*/ std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message);

				IScene* RunScene(WorldDef::IScene* scene_source);
				void StopScene(IScene*);

				IScene* RunScene();
				IScene* RunScene(WorldDef::ILayersManager* scene_layers);

				int GetSceneInstancesCount()
				{
					return scene_instances.size();
				}
				IScene* GetSceneInstance(int index)
				{
					return scene_instances[index].get();
				}

				void PhysStep(float step);


				void OnStep(float step);

				//void Render(TDirector* director, TRender* render);

				void UpdateTransform();


				TComposer* GetComposer()
				{
					return &composer;
				}
			};
		}
	}
}


