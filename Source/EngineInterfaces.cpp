#include "EngineInterfaces.h"

#include "World.h"

EngineInterface::IBaluWorld* CreateWorld()
{
	return (new TBaluWorld());
}