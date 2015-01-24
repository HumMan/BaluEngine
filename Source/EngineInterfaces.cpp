#include "EngineInterfaces.h"

#include "World.h"

EngineInterface::IBaluWorld* CreateWorld()
{
	return (new TBaluWorld());
}

#include "Director.h"

EngineInterface::IDirector* CreateDirector()
{
	return new TDirector();
}

#include "WorldInstance.h"

EngineInterface::IBaluWorldInstance* CreateWorldInstance(EngineInterface::IBaluWorld* source, EngineInterface::IResources* resources)
{
	return new TBaluWorldInstance(dynamic_cast<TBaluWorld*>(source), dynamic_cast<TResources*>(resources));
}