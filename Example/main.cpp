
#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

using namespace EngineInterface;

#include "DemoWorld.h"

IBaluSceneInstance* scene_instance;
TScreen* screen;
IViewport* main_viewport;
TView main_viewport_view;

EngineInterface::IDirector* director;

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	

	director = CreateDirector();

	auto base_path = director->GetBasePath();

	director->Initialize(true);

	auto demo_world = CreateDemoWorld(base_path);

	demo_world->GetCallbacksActiveType().active_type = TCallbacksActiveType::DEFAULT;

	screen = new TScreen(director->GetScreenSize());

	main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));

	auto demo_world_instance = CreateWorldInstance(demo_world, director->GetResources());
	auto demo_scene = demo_world->GetScene("scene0");

	main_viewport = demo_scene->FindViewport("main_viewport");

	scene_instance = demo_world_instance->RunScene(demo_scene);
	
	TDrawingHelperContext drawing_context;
	drawing_context.screen = screen;
	drawing_context.view = &main_viewport_view;
	drawing_context.viewport = main_viewport;

	auto scene_editor = CreateSceneEditor(drawing_context, demo_world, demo_scene, scene_instance);
	auto& tools = scene_editor->GetAvailableTools();
	scene_editor->SetActiveTool(tools[1].tool.get());

	director->SetWorldInstance(demo_world_instance);
	director->SetRenderWorldCallback(CallbackWithData<RenderWorldCallback>(RenderWorld, &demo_world->GetCallbacksActiveType()));
	director->SetViewportResizeCallback(ViewportResize);
	director->SetSymulatePhysics(true);
	director->MainLoop();

	return 0;
}