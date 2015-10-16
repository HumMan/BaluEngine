
#include <baluLib.h>

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

	director->Initialize(true);

	auto demo_world = CreateDemoWorld(director->GetAssetsDir());

	demo_world->GetCallbacksActiveType() = TScriptActiveType::DEFAULT;

	screen = new TScreen(director->GetScreenSize());

	main_viewport_view = TView(TVec2(0.5, 0.5), TVec2(1, 1));

	auto demo_world_instance = CreateWorldInstance(demo_world, director->GetResources());

	auto demo_scene = dynamic_cast<IBaluScene*>(demo_world->GetObjectByName(TWorldObjectType::Scene, "scene0"));

	main_viewport = demo_scene->FindViewport("main_viewport");

	scene_instance = demo_world_instance->RunScene(demo_scene);
	
	TDrawingHelperContext drawing_context;
	drawing_context.screen = screen;
	drawing_context.view = &main_viewport_view;
	drawing_context.viewport = main_viewport;

	director->SetWorldInstance(demo_world_instance);

	director->SetSymulatePhysics(true);

	director->MainLoop();

	DestroyWorldInstance(demo_world_instance);
	DestroyWorld(demo_world);
	IDirector::DestroyDirector(director);
}