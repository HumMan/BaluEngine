#pragma once

#include "../../Interface.h"


namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{


			class TWorld : public IWorld
			{
			private:
				class TPrivate;
				std::unique_ptr<TPrivate> p;
			public:
				~TWorld();
				IEventsEditorInstance* GetEventsEditor();

				/*TResources* GetResources()
				{
					return resources;
				}*/

				WorldDef::IWorld* GetSource();

				TWorld(WorldDef::IWorld* source, TResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message);

				IScene* RunScene(WorldDef::IScene* scene_source);
				void StopScene(IScene*);

				//IScene* RunScene();
				//IScene* RunScene(WorldDef::ILayersManager* scene_layers);

				int GetSceneInstancesCount();
				IScene* GetScene(int index);

				IComposer* GetComposer();

				void PhysStep(float step);

				void CallOnProcessCollisions();

				void OnStep(float step);

				//void Render(TDirector* director, TRender* render);

				void UpdateTransform();				
			};
		}
	}
}


