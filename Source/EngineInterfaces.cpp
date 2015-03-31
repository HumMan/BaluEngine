#include "EngineInterfaces.h"

#include "World.h"

#include "../Source/Semantic/SMethod.h"
#include "../Source/Semantic/SClass.h"
#include "../Source/Semantic/FormalParam.h"
#include "../Source/Semantic/SStatements.h"
#include "../Source/Syntax/Statements.h"
#include "../Source/Syntax/Method.h"
#include "../Source/semanticAnalyzer.h"


EngineInterface::IBaluWorld* CreateWorld()
{
	return (new TBaluWorld());
}

void DestroyWorld(EngineInterface::IBaluWorld* world)
{
	delete dynamic_cast<TBaluWorld*>(world);
}

#include "Director.h"

EngineInterface::IDirector* CreateDirector()
{
	return new TDirector();
}

void DestroyDirector(EngineInterface::IDirector* director)
{
	delete dynamic_cast<TDirector*>(director);
}

#include "WorldInstance.h"

EngineInterface::IBaluWorldInstance* CreateWorldInstance(EngineInterface::IBaluWorld* source, EngineInterface::IResources* resources)
{
	return new TBaluWorldInstance(dynamic_cast<TBaluWorld*>(source), dynamic_cast<TResources*>(resources));
}

void DestroyWorldInstance(EngineInterface::IBaluWorldInstance* world)
{
	delete dynamic_cast<TBaluWorldInstance*>(world);
}
