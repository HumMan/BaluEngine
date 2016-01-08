#include "IDirector.h"

#include <SDL.h>

#include "IWorldInstance.h"

#include "Render.h"

#include "nanovg.h"

#include <baluRender.h>

#include <easylogging++.h>
INITIALIZE_EASYLOGGINGPP

using namespace EngineInterface;

namespace EngineInterface
{
	class TGameInternal
	{
	public:

		bool create_window;

		std::unique_ptr<TBaluRender> internal_render;
		std::unique_ptr<TRender> render;
		std::unique_ptr<TResources> resources;

		std::string base_path;

		SDL_Window *mainwindow; /* Our window handle */

		SDL_GLContext maincontext; /* Our opengl context handle */

		TBaluWorldInstance* world_instance;

		std::string assets_dir;

		bool physics_sym;
	};

	class TBaluEngineInternal
	{
	public:
		std::unique_ptr<TBaluRender> render;
	};
}

void TDirector::Render()
{
	if (p->world_instance != nullptr)
		p->world_instance->GetComposer()->Render(p->render.get());
}

void TDirector::Step(float step)
{
	try
	{
		if (p->world_instance == nullptr)
			return;
		if (p->physics_sym)
		{
			//p->world_instance->OnPrePhysStep();
			p->world_instance->PhysStep(step);

		}
		p->world_instance->UpdateTransform();

		Render();

		if (p->physics_sym)
		{
			//p->world_instance->OnProcessCollisions();
		}

		p->world_instance->OnStep(step);

	}
	catch (std::exception ex)
	{
	}
}

void TDirector::SetWorldInstance(TBaluWorldInstance* world_instance)
{
	p->world_instance = world_instance;
}

void TDirector::SetWorldInstance(EngineInterface::IBaluWorldInstance* world_instance)
{
	SetWorldInstance(dynamic_cast<TBaluWorldInstance*>(world_instance));
}

EngineInterface::IBaluWorldInstance* TDirector::GetWorldInstance()
{
	return p->world_instance;
}

void TDirector::SetSymulatePhysics(bool enable)
{
	p->physics_sym = enable;
}

int TDirector::Initialize(bool create_window)
{
	p->create_window = create_window;
	p->base_path = SDL_GetBasePath();
	p->physics_sym = true;

	if (create_window)
	{
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
	}

	p->internal_render.reset(new TBaluRender(TVec2i(512, 512)));

	p->render.reset(new TRender(p->internal_render.get()));

	p->resources.reset(new TResources(p->internal_render.get(), p->assets_dir));

}

std::string TDirector::GetAssetsDir()
{
	//return SDL_GetBasePath();
	return p->assets_dir;
}

TVec2i TDirector::GetScreenSize()
{
	return p->internal_render->Get.Viewport();
}

void TDirector::SetScreenSize(TVec2i new_size)
{
	auto old_screen_size = p->internal_render->Get.Viewport();
	p->internal_render->Set.Viewport(new_size);
	//if (p->world_instance!=nullptr)
	//	p->world_instance->ViewportResize(this, old_screen_size, new_size);
}

void TDirector::SetViewport(TVec2i use_size)
{
	p->internal_render->Set.Viewport(use_size);
}

TResources* TDirector::GetResources()
{
	return p->resources.get();
}

void TDirector::Initialize(void* handle)
{
	LOG(INFO) << "Initializing director\n";

	p->base_path = SDL_GetBasePath();
	p->physics_sym = true;
	p->internal_render.reset(new TBaluRender((int)handle, TVec2i(512, 512)));

	p->render.reset(new TRender(p->internal_render.get()));

	p->resources.reset(new TResources(p->internal_render.get(), p->assets_dir));

	LOG(INFO) << "Initializing director success\n";
}
void TDirector::BeginFrame()
{
	p->internal_render->BeginScene();
	p->internal_render->Set.ClearColor(0.2, 0.3, 0.3);
	p->internal_render->Clear(true, true);
}
void TDirector::EndFrame()
{
	p->internal_render->EndScene();
}

void TDirector::MainLoop()
{
	assert(p->create_window);
	bool quit = false;
	SDL_Event event;

	auto last_tick = SDL_GetTicks();

	SDL_GL_SetSwapInterval(1);

	while (!quit)
	{
		//SDL_Delay(10);
		auto curr_tick = SDL_GetTicks();
		float step = (curr_tick - last_tick) / 1000.0;
		last_tick = curr_tick;
		p->internal_render->Set.ClearColor(0.2, 0.3, 0.3);
		p->internal_render->Clear(true, true);
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);

		//if (keystate[SDL_SCANCODE_LEFT])
		//	p->world_instance->KeyDown(TKey::Left);
		//if (keystate[SDL_SCANCODE_RIGHT])
		//	p->world_instance->KeyDown(TKey::Right);
		//if (keystate[SDL_SCANCODE_UP])
		//	p->world_instance->KeyDown(TKey::Up);
		//if (keystate[SDL_SCANCODE_DOWN])
		//	p->world_instance->KeyDown(TKey::Down);

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
			//else if (event.type == SDL_MOUSEMOTION)
			//{
			//	char b[100];
			//	sprintf_s(b, "Mouse %i %i", event.motion.x, event.motion.y);
			//	SDL_SetWindowTitle(p->mainwindow, b);
			//	p->world_instance->MouseMove(TMouseEventArgs(TMouseButton::Left, TVec2i(event.motion.x, event.motion.y)));
			//}
			//else if (event.type == SDL_MOUSEBUTTONDOWN)
			//{
			//	p->world_instance->MouseDown(TMouseEventArgs(TMouseButton::Left, TVec2i(event.button.x, event.button.y)));
			//}
			//else if (event.type == SDL_MOUSEBUTTONUP)
			//{
			//	p->world_instance->MouseUp(TMouseEventArgs(TMouseButton::Left, TVec2i(event.button.x, event.button.y)));
			//}
			//else if (event.type == SDL_MOUSEWHEEL)
			//{
			//	p->world_instance->MouseVerticalWheel(event.wheel.y);
			//}
			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					SetScreenSize(TVec2i(event.window.data1, event.window.data2));
				}
			}
		}
	}

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(p->maincontext);
	SDL_DestroyWindow(p->mainwindow);
	SDL_Quit();
}

TDirector::TDirector(std::string assets_dir)
{
	p = std::make_unique<TGameInternal>();
	p->assets_dir = assets_dir;
}

TDirector::~TDirector()
{
}