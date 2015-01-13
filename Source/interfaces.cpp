#include "interfaces.h"

#include "World.h"

EngineInterface::IBaluWorld* CreateWorld()
{
	return (new TBaluWorld());
}