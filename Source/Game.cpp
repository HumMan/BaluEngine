#include "Game.h"

#include <SDL.h>

#include "WorldInstance.h"

#include "Render.h"

#include "nanovg.h"

class TBaluEngineRender
{
public:
	static TResourses* CreateResources(TBaluRender* render)
	{
		return new TResourses(render);
	}
};


class TGameInternal
{
public:
	TBaluRender* internal_render;
	TRender* render;
	TResourses* resources;
};

class TBaluEngineInternal
{
public:
	std::unique_ptr<TBaluRender> render;
};

void TGame::RenderWorld(TBaluWorldInstance* world, TRender* render)
{
	auto viewport = scene_instance->GetViewport("main");

	std::vector<TBaluSpritePolygonInstance*> polygons;
	scene_instance->QueryAABB(viewport->GetAABB(), polygons);

	std::vector<TRenderCommand> render_commands;
	render_commands.resize(polygons.size());
	for (int i = 0; i < render_commands.size(); i++)
	{
		polygons[i]->Render(render_commands[i]);
	}
	render->Render(render_commands);
}

void TGame::Step(float step)
{

	demo_world_instance->OnPrePhysStep();
	demo_world_instance->PhysStep(step);

	demo_world_instance->UpdateTransform();

	RenderWorld(demo_world_instance, render);

	demo_world_instance->OnProcessCollisions();

	demo_world_instance->OnStep(step);

	g_camera.m_height = 512;
	g_camera.m_width = 512;
	g_camera.m_extent = 10;
	g_camera.m_zoom = 1;

	demo_world_instance->DebugDraw();
}

void TGame::MainLoop()
{

	base_path = SDL_GetBasePath();

	SDL_Window *mainwindow; /* Our window handle */

	SDL_GLContext maincontext; /* Our opengl context handle */

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{ /* Initialize SDL's Video subsystem */

		return 1;
	}
	/* Request opengl 4.4 context. */
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	/* Turn on double buffering with a 24bit Z buffer.
	* You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	/* Create our window centered at 512x512 resolution */

	mainwindow = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!mainwindow)
	{ /* Die if creation failed */

		SDL_Quit();
		return 1;
	}

	/* Create our opengl context and attach it to our window */

	maincontext = SDL_GL_CreateContext(mainwindow);

	auto err = SDL_GetError();
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	//SDL_GL_SetSwapInterval(1);

	bool quit = false;
	SDL_Event event;

	internal_render = new TBaluRender(TVec2i(512, 512));

	render = new TRender(internal_render);

	resources = TBaluEngineRender::CreateResources(internal_render);

	InitDemoWorld();

	auto last_tick = SDL_GetTicks();

	while (!quit)
	{
		auto curr_tick = SDL_GetTicks();
		float step = (curr_tick - last_tick) / 1000.0;
		last_tick = curr_tick;
		internal_render->Set.ClearColor(0.2, 0.3, 0.3);
		internal_render->Clear(true, true);
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_LEFT])
			demo_world_instance->OnKeyDown(TKey::Left);
		if (keystate[SDL_SCANCODE_RIGHT])
			demo_world_instance->OnKeyDown(TKey::Right);
		if (keystate[SDL_SCANCODE_UP])
			demo_world_instance->OnKeyDown(TKey::Up);
		if (keystate[SDL_SCANCODE_DOWN])
			demo_world_instance->OnKeyDown(TKey::Down);

		Step(step);

		SDL_GL_SwapWindow(mainwindow);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYUP)
			{
			}
			else if (event.type == SDL_KEYDOWN)
			{
				SDL_SetWindowTitle(mainwindow, "keydown");
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				char b[100];
				sprintf_s(b, "Mouse %i %i", event.motion.x, event.motion.y);
				SDL_SetWindowTitle(mainwindow, b);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{

			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{

			}
			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					internal_render->Set.Viewport(TVec2i(event.window.data1, event.window.data2));
			}
		}
	}

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}