#include "EngineInterfaces.h"

#include "World.h"

#include "Director.h"
#include "WorldInstance.h"
#include "ScriptInstance.h"

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

	bool CompileScripts(IBaluWorld* source, IBaluScriptInstance* script_engine, std::vector<std::string>& errors_list)
	{
		return TBaluWorldInstance::CompileScripts(dynamic_cast<TBaluWorld*>(source), *(dynamic_cast<TBaluScriptInstance*>(script_engine)), errors_list);
	}

	IBaluScriptInstance* CreateScriptInstance(std::string assets_dir)
	{
		return new TBaluScriptInstance(assets_dir);
	}

	void DestroyScriptInstance(IBaluScriptInstance* instance)
	{
		auto ed = dynamic_cast<TBaluScriptInstance*>(instance);
		delete ed;
	}
}