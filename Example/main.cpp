
#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

using namespace EngineInterface;

//#define USE_CALLBACKS
#include "DemoWorld.h"

IBaluSceneInstance* scene_instance;
TScreen* screen;
IViewport* main_viewport;
TView main_viewport_view;

EngineInterface::IDirector* director;

#include <Windows.h>

std::string WideToMultiByte(std::wstring source)
{
	char buf[1000];
	size_t num;
	wcstombs_s(&num, buf, source.c_str(), 1000);
	return std::string(buf);
}

void Run(std::string assets_dir);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	int num_args;
	LPWSTR* args;
	args = CommandLineToArgvW(GetCommandLine(), &num_args);

	if (num_args == 2)
	{
		Run(WideToMultiByte(args[1]));
	}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return 0;
}

void Run(std::string assets_dir)
{
	director = IDirector::CreateDirector(assets_dir);

	//auto base_path = director->GetBasePath();

	director->Initialize(true);

	auto demo_world = CreateDemoWorld(director->GetAssetsDir());

	demo_world->GetCallbacksActiveType().active_type = TCallbacksActiveType::DEFAULT;

#ifdef USE_CALLBACKS
	//demo_world->SetRenderWorldCallback(CallbackWithData<RenderWorldCallback>(RenderWorld, &demo_world->GetCallbacksActiveType()));
	demo_world->AddOnWorldStart(CallbackWithData<OnStartWorldCallback>(WorldStart, &demo_world->GetCallbacksActiveType()));
	demo_world->SetViewportResizeCallback(CallbackWithData<ViewportResizeCallback>(ViewportResize, &demo_world->GetCallbacksActiveType()));
#else
	//demo_world->SetRenderWorldCallback(CallbackWithData<RenderWorldCallback>(RenderWorld_source, &demo_world->GetCallbacksActiveType(), TCallbacksActiveType::DEFAULT));
	//demo_world->SetRenderWorldCallback(CallbackWithData<RenderWorldCallback>(RenderWorld, &demo_world->GetCallbacksActiveType()));
	//demo_world->AddOnWorldStart(CallbackWithData<OnStartWorldCallback>(WorldStart_source, &demo_world->GetCallbacksActiveType(), TCallbacksActiveType::DEFAULT));
	//demo_world->SetViewportResizeCallback(CallbackWithData<ViewportResizeCallback>(ViewportResize_source, &demo_world->GetCallbacksActiveType(), TCallbacksActiveType::DEFAULT));
#endif

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

	director->SetSymulatePhysics(true);

	director->MainLoop();

	DestroySceneEditor(scene_editor);

	DestroyWorldInstance(demo_world_instance);
	DestroyWorld(demo_world);
	IDirector::DestroyDirector(director);
}