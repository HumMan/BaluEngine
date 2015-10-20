#include "nanovg_support.h"

#define NANOVG_GLEW

#include <stdio.h>
#ifdef NANOVG_GLEW
#  include <GL/glew.h>
#endif
//#include <GLFW/glfw3.h>
#include "nanovg.h"
#define NANOVG_GL2_IMPLEMENTATION
#include "nanovg_gl.h"

NVGcontext* vg = NULL;

void nanovg_init()
{

	vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);

	if (vg == NULL) {
		printf("Could not init nanovg.\n");
		throw;
		return;
	}

	//nvgDeleteGL2(vg);

	int r = nvgCreateFont(vg, "icons", "assets/fonts/entypo.ttf");

	r = nvgCreateFont(vg, "sans", "assets/fonts/Roboto-Regular.ttf");

	//r = nvgCreateFont(vg, "sans-bold", "../fonts/Roboto-Bold.ttf");

}

void nanovg_deinit()
{
	nvgDeleteGL2(vg);
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