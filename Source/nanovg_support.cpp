#include "nanovg_support.h"

#define NANOVG_GLEW

#include <stdio.h>
#ifdef NANOVG_GLEW
#  include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

NVGcontext* vg = NULL;

void nanovg_init()
{
#ifdef DEMO_MSAA
	vg = nvgCreateGL2(NVG_STENCIL_STROKES | NVG_DEBUG);
#else
	vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#endif
	if (vg == NULL) {
		printf("Could not init nanovg.\n");
		return;
	}

	int r = nvgCreateFont(vg, "icons", "../fonts/entypo.ttf");

	r = nvgCreateFont(vg, "sans", "../fonts/Roboto-Regular.ttf");

	r = nvgCreateFont(vg, "sans-bold", "../fonts/Roboto-Bold.ttf");

}

void nanovg_deinit()
{
	nvgDeleteGL2(vg);
}

NVGcontext* GetContext()
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