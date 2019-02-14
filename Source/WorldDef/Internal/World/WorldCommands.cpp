
#include "WorldCommands.h"

#include "World.h"

#include <pugixml.hpp>
#include "../Common/SerializeCommon.h"

using namespace pugi;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;


WorldObjectCreate::WorldObjectCreate(IWorld* world, TWorldObjectType type, const std::string& name, const std::string& serialized)
{
	this->world = world;
	this->type = type;
	this->object_name = name;
	this->serialized = serialized;
}

void WorldObjectCreate::Do()
{
	world->CreateObject(type, object_name.c_str(), serialized);
}
void WorldObjectCreate::Undo()
{
	world->DestroyObject(type, object_name.c_str());
}

void WorldObjectDestroy::Do()
{
	WorldObjectCreate::Undo();
}
void WorldObjectDestroy::Undo()
{
	WorldObjectCreate::Do();
}

