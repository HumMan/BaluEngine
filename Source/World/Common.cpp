#include "ICommon.h"

#include "IWorld.h"

using namespace EngineInterface;

void TBaluWorldObject::SetName(std::string name)
{
	assert(!world->ObjectNameExists(TWorldObjectType::Material, name.c_str()));
	this->name = name;
}

std::string TBaluWorldObject::GetName()
{
	return name;
}

TBaluWorldObject::TBaluWorldObject(IBaluWorld* world, std::string name)
{
	this->world = world;
	this->name = name;
}
TProperties& TBaluWorldObject::GetProperties()
{
	return properties;
}
std::string TBaluWorldObject::GetName()
{
	return name;
}
IBaluWorld* TBaluWorldObject::GetWorld()
{
	return world;
}