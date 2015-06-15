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
		//TODO uncomment
		//return TBaluWorldInstance::CompileScripts(dynamic_cast<TBaluWorld*>(source), *(dynamic_cast<TBaluScriptInstance*>(script_engine)), errors_list);
		return false;
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

	TVec2 TDrawingHelperContext::FromScreenPixelsToScene(TVec2i screen_pixels)
	{

		auto screen_coords = screen->FromScreenPixels2(screen_pixels);
		auto view_coord = screen->FromScreenToView(*view, screen_coords);
		auto scene_coord = IBaluScene::FromViewportToScene(viewport, view_coord);
		return scene_coord;
	}
	TVec2i TDrawingHelperContext::FromSceneToScreenPixels(TVec2 scene_coordinates)
	{
		auto viewport_coord = IBaluScene::FromSceneToViewport(viewport, scene_coordinates);
		auto screen_coord = screen->FromViewToScreen(*view, viewport_coord);
		auto screen_pixels = screen->ToScreenPixels2(screen_coord);
		return screen_pixels;
	}
}