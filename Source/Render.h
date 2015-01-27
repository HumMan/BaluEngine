#pragma once

#include "RenderCommand.h"

#include "exportMacro.h"

#include <vector>

class TBaluRender;

class BALUENGINEDLL_API TRender
{
	TBaluRender* render;
public:
	TRender(TBaluRender* internal_render);

	void Render(std::vector<TRenderCommand>& render_commands, std::vector<TCustomDrawCommand>& custom_draw_commands);
};