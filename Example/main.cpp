
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

void ViewportResize(TVec2i old_size, TVec2i new_size)
{
	TVec2 k = TVec2((float)new_size[0], (float)new_size[1]) / TVec2((float)old_size[0], (float)old_size[1]);
	auto old_vieport_size = main_viewport->GetSize();
	auto new_vieport_size = old_vieport_size.ComponentMul(k);
	main_viewport->SetSize(new_vieport_size);
}

void RenderWorld(IBaluWorldInstance* world, TRender* render)
{
	*screen = TScreen(director->GetScreenSize());

	std::vector<TRenderCommand> render_commands;
	std::vector<TCustomDrawCommand> custom_draw_commands;
	auto viewport_aabb = main_viewport->GetAABB();
	scene_instance->QueryAABB(viewport_aabb, render_commands, custom_draw_commands);

	for (auto& v : custom_draw_commands)
	{
		v.screen = screen;
		v.view = &main_viewport_view;
		v.viewport = &viewport_aabb;
	}

	//render->EnableScissor(true);
	//render->SetScissorRect(*screen, main_viewport_view);
	render->Render(render_commands, custom_draw_commands, main_viewport);
	//render->EnableScissor(false);
}

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

	demo_world->GetCallbacksActiveType().active_type = TCallbacksActiveType::EDITOR;

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
	director->SetRenderWorldCallback(RenderWorld);
	director->SetViewportResizeCallback(ViewportResize);
	director->SetSymulatePhysics(false);
	director->MainLoop();

	return 0;
}