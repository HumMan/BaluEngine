
#include <baluLib.h>

#include <Interfaces\BaluEngineInterfaces.h>
#include <EditorUtils\abstractEditor.h>

using namespace EngineInterface;

EngineInterface::IDirector* director;

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
		Run(EngineInterface::as_utf8(args[1]), EngineInterface::as_utf8(args[2]));
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
	EngineInterface::ConfigureLogging();

	setlocale(LC_ALL, "C");
	director = IDirector::CreateDirector(assets_dir);

	director->Initialize(true);

	IBaluWorld* world = CreateWorld();

	world->LoadFromXML(file_to_run.c_str());

	world->GetCallbacksActiveType() = TScriptActiveType::DEFAULT;

	auto world_instance = CreateWorldInstance(world, director->GetResources());

	director->SetWorldInstance(world_instance);

	director->MainLoop();

	DestroyWorldInstance(world_instance);
	DestroyWorld(world);
	IDirector::DestroyDirector(director);
}