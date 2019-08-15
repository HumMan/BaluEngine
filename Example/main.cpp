
#include <baluLib.h>

//#define USE_CALLBACKS
#include "DemoWorld.h"

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

	LocalFree(args);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return 0;
}

void Run(std::string assets_dir)
{
	auto director = WorldInstance::IDirector::Create(assets_dir);

	director->Initialize(true);

	auto demo_world = CreateDemoWorld(director->GetAssetsDir());
	
	demo_world->SaveToXML("demo_test.xml");
	auto temp = WorldDef::CreateWorld();
	temp->LoadFromXML("demo_test.xml");
	temp->SaveToXML("demo_test_2.xml");
	WorldDef::DestroyWorld(temp);

	auto screen = new WorldInstance::TScreen(director->GetScreenSize());

	auto main_viewport_view = WorldInstance::TView(BaluLib::TVec2(0.5, 0.5), BaluLib::TVec2(1, 1));
	

	auto demo_world_instance = WorldInstance::CreateWorld(demo_world, director->GetResources(),  assets_dir);

	auto script_instance = BaluEngine::WorldInstance::CreateEventsEditor(demo_world_instance, demo_world->GetEventsEditor());
	script_instance->Compile();
	
	WorldInstance::TDrawingHelperContext drawing_context;
	drawing_context.screen = screen;
	drawing_context.view = &main_viewport_view;
	drawing_context.viewport = nullptr;

	demo_world_instance->SetCollideListener(script_instance.get());

	script_instance->WorldStart(demo_world_instance, demo_world_instance->GetComposer());

	director->SetWorldInstance(demo_world_instance);
	director->SetEventsEditor(script_instance);

	director->SetSymulatePhysics(true);

	director->MainLoop();

	WorldDef::DestroyWorld(demo_world);
	delete screen;

	director.reset();

	BaluEngine::WorldInstance::IDirector::ClearStaticData();
}