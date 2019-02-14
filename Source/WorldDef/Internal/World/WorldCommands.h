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
			class WorldObjectCreate : public ICommand
			{
			public:
				IWorld* world;
				TWorldObjectType type;
				std::string object_name;
				std::string serialized;

				WorldObjectCreate(IWorld* world, TWorldObjectType type, const std::string& name, const std::string& serialized);

				void Do();
				void Undo();
			};

			class WorldObjectDestroy : public WorldObjectCreate
			{
			public:
				void Do();
				void Undo();
			};
		}
	}
}
