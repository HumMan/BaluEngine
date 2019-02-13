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
			class SceneObjectPropertyChange : public ICommand
			{
			public:
				IWorld* world;
				std::string scene_name;
				int instance_id;
				std::string property_name;
				std::string old_value, new_value;

				SceneObjectPropertyChange(IWorld* world, IScene* scene, int instance_id, const std::string& property_name
					, const std::string& old_value, const std::string& new_value);

				void Do();
				void Undo();
			};
		}
	}
}
