
#include <baluLib.h>

#include <Common/Director.h>

#include <Render/DrawingHelper.h>

#include <Windows.h>

std::string WideToMultiByte(std::wstring source)
{
	char buf[1000];
	size_t num;
	wcstombs_s(&num, buf, source.c_str(), 1000);
	return std::string(buf);
}

void Run();

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	int num_args;
	LPWSTR* args;
	args = CommandLineToArgvW(GetCommandLine(), &num_args);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Run();

	return 0;
}

void Run()
{
	BaluEngine::WorldInstance::GenerateScriptBindings("external_bindings.h");
}