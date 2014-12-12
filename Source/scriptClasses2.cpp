#include "scriptClasses2.h"

#include <SDL.h>

class TBaluEngineInternal
{
public:
	std::unique_ptr<TBaluRender> render;

	b2World* phys_world;
};

void Finalize()
{

}
void Display()
{

}

int SDLTest()
{
	SDL_Window *mainwindow; /* Our window handle */

	SDL_GLContext maincontext; /* Our opengl context handle */

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{ /* Initialize SDL's Video subsystem */

		return 1;
	}
	/* Request opengl 4.4 context. */
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	/* Turn on double buffering with a 24bit Z buffer.
	* You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/* Create our window centered at 512x512 resolution */

	mainwindow = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!mainwindow)
	{ /* Die if creation failed */

		SDL_Quit();
		return 1;
	}

	/* Create our opengl context and attach it to our window */

	maincontext = SDL_GL_CreateContext(mainwindow);
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(1);
	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		Display();
		SDL_GL_SwapWindow(mainwindow);
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				quit = true;

			}
		}
	}

	Finalize();
	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}


TBaluEngine::TBaluEngine(int hWnd, TVec2i use_size)
{
	p.reset(new TBaluEngineInternal());
	p->render.reset(new TBaluRender(hWnd, use_size));
	p->phys_world = NULL;
}
TBaluEngine::~TBaluEngine()
{
	delete p->phys_world;
}

void TBaluEngine::SetViewport(TVec2i use_size)
{
	p->render->Set.Viewport(use_size);
}

void TBaluEngine::OnMouseLeftUp()
{
	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEUP, LEFT);
}

void TBaluEngine::OnMouseLeftDown()
{
	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEDOWN, LEFT);
}

void TBaluEngine::OnMouseRightUp()
{
	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEUP, RIGHT);
}

void TBaluEngine::OnMouseRightDown()
{
	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEDOWN, RIGHT);
}

void TBaluEngine::OnMouseMiddleUp()
{
	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEUP, MIDDLE);
}

void TBaluEngine::OnMouseMiddleDown()
{
	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEDOWN, MIDDLE);
}

void TBaluEngine::OnMouseMove(TVec2i use_client_mouse_pos)
{
}

void TBaluEngine::OnMouseScroll(float delta)
{
	delta /= 120.f;
	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEWHEEL, *(int*)&delta);
}