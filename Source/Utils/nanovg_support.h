#pragma once

//#include <Interfaces/ExportMacro.h>

#include <baluLib.h>
using namespace BaluLib;

class NVGcontext;

 void nanovg_init();
 void nanovg_deinit();
 NVGcontext* GetNanoVGContext();
//void render_test();

 void begin_frame(TVec2i screen_size);
 void end_frame();
