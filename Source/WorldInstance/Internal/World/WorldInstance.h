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

				/*TResources* GetResources()
				{
					return resources;
				}*/

				WorldDef::IWorld* GetSource();

				TWorld(WorldDef::IWorld* source, TResources* resources, std::string assets_dir);

				void SetThisPtr(std::weak_ptr <IWorld> this_ptr);

				std::shared_ptr < IScene> RunScene(WorldDef::IScene* scene_source);
				void StopScene(std::shared_ptr < IScene>);

				//IScene* RunScene();
				//IScene* RunScene(WorldDef::ILayersManager* scene_layers);

				int GetSceneCount();
				std::shared_ptr < IScene> GetScene(int index);

				std::shared_ptr<IComposer> GetComposer();

				void PhysStep(float step);

				void CallOnProcessCollisions();

				void OnStep(float step);

				//void Render(TDirector* director, TRender* render);

				void UpdateTransform();				

				void SetCollideListener(ISceneContactListener* contacts_listener);
			};
		}
	}
}


