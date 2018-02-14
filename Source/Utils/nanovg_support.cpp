#include "nanovg_support.h"

#define NANOVG_GLEW

#include <stdio.h>
#ifdef NANOVG_GLEW
#include <GL/glew.h>
#endif

#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

NVGcontext* vg = NULL;

void nanovg_init()
{
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		printf("Could not init glew in nanovg_init.\n");
	}
	else
	{
		if (GLEW_VERSION_2_0)
		{
			vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
		}
		if (vg == NULL) {
			printf("Could not init nanovg.\n");
		}
		else
		{
			int r = nvgCreateFont(vg, "icons", "assets/fonts/entypo.ttf");
			r = nvgCreateFont(vg, "sans", "assets/fonts/Roboto-Regular.ttf");
		}
	}
}

void nanovg_deinit()
{
	if (vg != nullptr)
	{
		nvgDeleteGL2(vg);
	}
}

NVGcontext* GetNanoVGContext()
{
	return vg;
}

void begin_frame(TVec2i screen_size)
{
	nvgBeginFrame(vg, screen_size[0], screen_size[1], 1);
}

void end_frame()
{
	nvgEndFrame(vg);
}