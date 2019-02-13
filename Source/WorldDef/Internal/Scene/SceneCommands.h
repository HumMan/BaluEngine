#pragma once

#include "../../Interface.h"

#include "../Common/Common.h"

#include "../World/World.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{


			class DestroySceneObject : public ICommand
			{
			public:
				IWorld* world;
				std::string scene_name;
				std::string scene_instance_serialized;
				int instance_id;

				DestroySceneObject(IWorld* world, IScene* scene, int instance_id, ISceneObject* instance);

				void Do();
				void Undo();
			};

			class CreateSceneObject : public DestroySceneObject
			{
			public:

				CreateSceneObject(IWorld* world, IScene* scene, int instance_id, ISceneObject* instance);

				void Do();
				void Undo();
			};
		}
	}
}
