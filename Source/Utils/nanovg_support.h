#pragma once

#include <Interfaces\ExportMacro.h>

#include <baluLib.h>
using namespace BaluLib;

class NVGcontext;

BALUENGINEDLL_API void nanovg_init();
BALUENGINEDLL_API void nanovg_deinit();
BALUENGINEDLL_API NVGcontext* GetNanoVGContext();
//void render_test();

BALUENGINEDLL_API void begin_frame(TVec2i screen_size);
BALUENGINEDLL_API void end_frame();