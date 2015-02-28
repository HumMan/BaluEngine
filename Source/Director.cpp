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
	VieportResizeCallback vieport_resize_callback;

	bool physics_sym;
};

class TBaluEngineInternal
{
public:
	std::unique_ptr<TBaluRender> render;
};

void TDirector::Step(float step)
{
	if (p->physics_sym)
	{
		p->world_instance->OnPrePhysStep();
		p->world_instance->PhysStep(step);

	}
	p->world_instance->UpdateTransform();

	p->render_world_callback(p->world_instance, p->render.get());

	if (p->physics_sym)
	{
		p->world_instance->OnProcessCollisions();
	}

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

void TDirector::SetVieportResizeCallback(VieportResizeCallback callback)
{
	p->vieport_resize_callback = callback;
}

void TDirector::SetSymulatePhysics(bool enable)
{
	p->physics_sym = enable;
}

int TDirector::Initialize()
{

	p->base_path = SDL_GetBasePath();

	p->physics_sym = true;

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

std::string TDirector::GetBasePath()
{
	return SDL_GetBasePath();
}

TVec2i TDirector::GetScreenSize()
{
	int w, h;
	SDL_GetWindowSize(p->mainwindow, &w, &h);
	return TVec2i(w, h);
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

		if (keystate[SDL_SCANCODE_LEFT])
			p->world_instance->KeyDown(TKey::Left);
		if (keystate[SDL_SCANCODE_RIGHT])
			p->world_instance->KeyDown(TKey::Right);
		if (keystate[SDL_SCANCODE_UP])
			p->world_instance->KeyDown(TKey::Up);
		if (keystate[SDL_SCANCODE_DOWN])
			p->world_instance->KeyDown(TKey::Down);

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
				//p->world_instance->KeyUp();
			}
			else if (event.type == SDL_KEYDOWN)
			{
				SDL_SetWindowTitle(p->mainwindow, "keydown");
				//p->world_instance->KeyDown();
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				char b[100];
				sprintf_s(b, "Mouse %i %i", event.motion.x, event.motion.y);
				SDL_SetWindowTitle(p->mainwindow, b);
				p->world_instance->MouseMove(TMouseEventArgs(TMouseButton::Left, TVec2i(event.motion.x, event.motion.y)), TVec2(event.motion.x, event.motion.y));
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				p->world_instance->MouseDown(TMouseEventArgs(TMouseButton::Left, TVec2i(event.button.x, event.button.y)), TVec2(0, 0));
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				p->world_instance->MouseUp(TMouseEventArgs(TMouseButton::Left, TVec2i(event.button.x, event.button.y)), TVec2(0, 0));
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{
				p->world_instance->MouseVerticalWheel(event.wheel.y);
			}
			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					auto old_screen_size = p->internal_render->Get.Vieport();
					auto new_size = TVec2i(event.window.data1, event.window.data2);
					p->internal_render->Set.Viewport(new_size);
					p->vieport_resize_callback(old_screen_size, new_size);
				}
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