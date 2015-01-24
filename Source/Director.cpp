#include "Director.h"

#include <SDL.h>

#include "WorldInstance.h"

#include "Render.h"

#include "nanovg.h"

#include <baluRender.h>

class TBaluEngineRender
{
public:
	static TResources* CreateResources(TBaluRender* render)
	{
		return new TResources(render);
	}
};


class TGameInternal
{
public:
	std::unique_ptr<TBaluRender> internal_render;
	std::unique_ptr<TRender> render;
	std::unique_ptr<TResources> resources;

	std::string base_path;

	SDL_Window *mainwindow; /* Our window handle */

	SDL_GLContext maincontext; /* Our opengl context handle */

	TBaluWorldInstance* world_instance;

	RenderWorldCallback render_world_callback;
};

class TBaluEngineInternal
{
public:
	std::unique_ptr<TBaluRender> render;
};

void TDirector::Step(float step)
{
	p->world_instance->OnPrePhysStep();
	p->world_instance->PhysStep(step);

	p->world_instance->UpdateTransform();

	p->render_world_callback(p->world_instance, p->render.get());

	p->world_instance->OnProcessCollisions();

	p->world_instance->OnStep(step);

	g_camera.m_height = 512;
	g_camera.m_width = 512;
	g_camera.m_extent = 10;
	g_camera.m_zoom = 1;

	p->world_instance->DebugDraw();
}

void TDirector::SetWorldInstance(TBaluWorldInstance* world_instance)
{
	p->world_instance = world_instance;
}

void TDirector::SetWorldInstance(EngineInterface::IBaluWorldInstance* world_instance)
{
	SetWorldInstance(dynamic_cast<TBaluWorldInstance*>(world_instance));
}

void TDirector::SetRenderWorldCallback(RenderWorldCallback callback)
{
	p->render_world_callback = callback;
}

int TDirector::Initialize()
{

	p->base_path = SDL_GetBasePath();


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

	p->mainwindow = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!p->mainwindow)
	{ /* Die if creation failed */

		SDL_Quit();
		return 1;
	}

	/* Create our opengl context and attach it to our window */

	p->maincontext = SDL_GL_CreateContext(p->mainwindow);

	auto err = SDL_GetError();
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	//SDL_GL_SetSwapInterval(1);

	

	p->internal_render.reset(new TBaluRender(TVec2i(512, 512)));

	p->render.reset(new TRender(p->internal_render.get()));

	p->resources.reset(TBaluEngineRender::CreateResources(p->internal_render.get()));

}

TResources* TDirector::GetResources()
{
	return p->resources.get();
}

void TDirector::MainLoop()
{
	bool quit = false;
	SDL_Event event;

	auto last_tick = SDL_GetTicks();

	while (!quit)
	{
		auto curr_tick = SDL_GetTicks();
		float step = (curr_tick - last_tick) / 1000.0;
		last_tick = curr_tick;
		p->internal_render->Set.ClearColor(0.2, 0.3, 0.3);
		p->internal_render->Clear(true, true);
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);

		//if (keystate[SDL_SCANCODE_LEFT])
		//	demo_world_instance->OnKeyDown(TKey::Left);
		//if (keystate[SDL_SCANCODE_RIGHT])
		//	demo_world_instance->OnKeyDown(TKey::Right);
		//if (keystate[SDL_SCANCODE_UP])
		//	demo_world_instance->OnKeyDown(TKey::Up);
		//if (keystate[SDL_SCANCODE_DOWN])
		//	demo_world_instance->OnKeyDown(TKey::Down);

		Step(step);

		SDL_GL_SwapWindow(p->mainwindow);
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
				SDL_SetWindowTitle(p->mainwindow, "keydown");
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				char b[100];
				sprintf_s(b, "Mouse %i %i", event.motion.x, event.motion.y);
				SDL_SetWindowTitle(p->mainwindow, b);
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
					p->internal_render->Set.Viewport(TVec2i(event.window.data1, event.window.data2));
			}
		}
	}

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(p->maincontext);
	SDL_DestroyWindow(p->mainwindow);
	SDL_Quit();
}

TDirector::TDirector()
{
	p = std::make_unique<TGameInternal>();
}

TDirector::~TDirector()
{

}