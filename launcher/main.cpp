
#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

using namespace EngineInterface;

EngineInterface::IDirector* director;

#include <Windows.h>


std::string WideToMultiByte(std::wstring source)
{
	char buf[1000];
	size_t num;
	wcstombs_s(&num, buf, source.c_str(), 1000);
	return std::string(buf);
}

void Run(std::string assets_dir, std::string file_to_run);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	int num_args;
	LPWSTR* args;
	args = CommandLineToArgvW(GetCommandLine(), &num_args);

	if (num_args == 3)
	{
		Run(WideToMultiByte(args[1]), WideToMultiByte(args[2]));
	}	

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return 0;
}

void Run(std::string assets_dir, std::string file_to_run)
{
	director = IDirector::CreateDirector(assets_dir);

	director->Initialize(true);

	IBaluWorld* world = CreateWorld();

	world->LoadFromXML(file_to_run.c_str());

	world->GetCallbacksActiveType().active_type = TCallbacksActiveType::DEFAULT;

	auto world_instance = CreateWorldInstance(world, director->GetResources());

	director->SetWorldInstance(world_instance);

	director->MainLoop();

	DestroyWorldInstance(world_instance);
	DestroyWorld(world);
	IDirector::DestroyDirector(director);
}