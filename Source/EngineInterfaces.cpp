#include "EngineInterfaces.h"

#include "World.h"

#include "Director.h"
#include "WorldInstance.h"

namespace EngineInterface
{
	EngineInterface::IBaluWorld* CreateWorld()
	{
		return (new TBaluWorld());
	}

	void DestroyWorld(EngineInterface::IBaluWorld* world)
	{
		delete dynamic_cast<TBaluWorld*>(world);
	}



	EngineInterface::IDirector* IDirector::CreateDirector(std::string assets_dir, std::string log_file_path)
	{
		return new TDirector(assets_dir, log_file_path);
	}

	void IDirector::DestroyDirector(EngineInterface::IDirector* director)
	{
		delete dynamic_cast<TDirector*>(director);
	}

	EngineInterface::IBaluWorldInstance* CreateWorldInstance(EngineInterface::IBaluWorld* source, EngineInterface::IResources* resources)
	{
		return new TBaluWorldInstance(dynamic_cast<TBaluWorld*>(source), dynamic_cast<TResources*>(resources));
	}

	void DestroyWorldInstance(EngineInterface::IBaluWorldInstance* world)
	{
		delete dynamic_cast<TBaluWorldInstance*>(world);
	}
}