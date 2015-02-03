#pragma once

#include "exportMacro.h"

class NVGcontext;

BALUENGINEDLL_API void nanovg_init();
BALUENGINEDLL_API NVGcontext* GetContext();
//void render_test();

BALUENGINEDLL_API void begin_frame();
BALUENGINEDLL_API void end_frame();