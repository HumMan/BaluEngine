
#include <baluLib.h>

#include "../Source/EngineInterfaces.h"
#include "../Source/EditorInterfaces.h"

using namespace EngineInterface;

EngineInterface::IDirector* director;

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	director = IDirector::CreateDirector();

	auto base_path = director->GetBasePath();

	director->Initialize(true);

	IBaluWorld* world = CreateWorld();

	world->LoadFromXML("");

	world->GetCallbacksActiveType().active_type = TCallbacksActiveType::DEFAULT;

	auto world_instance = CreateWorldInstance(world, director->GetResources());

	world_instance->CompileScripts();

	director->SetWorldInstance(world_instance);

	director->MainLoop();

	DestroyWorldInstance(world_instance);
	DestroyWorld(world);
	IDirector::DestroyDirector(director);

	_CrtDumpMemoryLeaks();

	return 0;
}