
#include <baluEngine.h>

#include <Windows.h>

void Run(std::string assets_dir, std::string file_to_run);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	
	MessageBox(0, L"Launcher started", L"", MB_OK);
	int num_args;
	LPWSTR* args;
	args = CommandLineToArgvW(GetCommandLine(), &num_args);

	if (num_args == 3)
	{
		Run(BaluEngine::WorldInstance::IDirector::as_utf8(args[1]),
			BaluEngine::WorldInstance::IDirector::as_utf8(args[2]));
	}
	else
	{
		Run("assets", "game.bew");
	}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return 0;
}

void Run(std::string assets_dir, std::string file_to_run)
{
	setlocale(LC_ALL, "C");
	auto director = BaluEngine::WorldInstance::IDirector::Create(assets_dir);

	director->Initialize(true);

	auto world = BaluEngine::WorldDef::CreateWorld();

	world->LoadFromXML(file_to_run.c_str());

	auto world_instance = BaluEngine::WorldInstance::CreateWorld(world, director->GetResources(), assets_dir);

	auto script_instance = BaluEngine::WorldInstance::CreateEventsEditor(world_instance, world->GetEventsEditor());
	script_instance->Compile();

	world_instance->SetCollideListener(script_instance.get());

	script_instance->WorldStart(world_instance, world_instance->GetComposer());

	director->SetWorldInstance(world_instance);
	director->SetEventsEditor(script_instance);

	director->MainLoop();


	BaluEngine::WorldDef::DestroyWorld(world);

	BaluEngine::WorldInstance::IDirector::ClearStaticData();
}