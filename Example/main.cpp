
#include <baluLib.h>

//#define USE_CALLBACKS
#include "DemoWorld.h"

WorldInstance::IScene* scene_instance;
WorldInstance::TScreen* screen;
WorldDef::IViewport* main_viewport;
WorldInstance::TView main_viewport_view;

WorldInstance::IDirector* director;

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
	director = WorldInstance::IDirector::CreateDirector(assets_dir);

	director->Initialize(true);

	auto demo_world = CreateDemoWorld(director->GetAssetsDir());
	demo_world->SaveToXML("demo_test.xml");

	auto temp = WorldDef::CreateWorld();
	temp->LoadFromXML("demo_test.xml");
	temp->SaveToXML("demo_test_2.xml");

	screen = new WorldInstance::TScreen(director->GetScreenSize());

	main_viewport_view = WorldInstance::TView(BaluLib::TVec2(0.5, 0.5), BaluLib::TVec2(1, 1));

	std::string error;
	bool compile_success;
	auto demo_world_instance = WorldInstance::CreateWorld(demo_world, director->GetResources(), assets_dir, true, compile_success, error);
	
	//TODO убрать после исправления скриптов - оно есть в WorldStart_source
	auto scene = demo_world_instance->GetSource()->GetScene("scene0");
	auto scene_instance = demo_world_instance->RunScene(scene);
	demo_world_instance->GetComposer()->AddToRender(scene_instance, scene->FindViewport("main_viewport"));
	
	WorldInstance::TDrawingHelperContext drawing_context;
	drawing_context.screen = screen;
	drawing_context.view = &main_viewport_view;
	drawing_context.viewport = main_viewport;

	director->SetWorldInstance(demo_world_instance);

	director->SetSymulatePhysics(true);

	director->MainLoop();

	WorldInstance::DestroyWorld(demo_world_instance);
	WorldDef::DestroyWorld(demo_world);
	delete screen;
	WorldInstance::IDirector::DestroyDirector(director, true);
}