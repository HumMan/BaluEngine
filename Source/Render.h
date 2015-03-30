#pragma once

#include "RenderCommand.h"

#include "EngineInterfaces\IMaterial.h"

#include "exportMacro.h"

#include <vector>

class TBaluRender;

class BALUENGINEDLL_API TRender
{
	TBaluRender* render;
public:
	TRender(TBaluRender* internal_render);
	~TRender();
	void Render(std::vector<TRenderCommand>& render_commands, std::vector<TCustomDrawCommand>& custom_draw_commands, EngineInterface::IViewport* viewport);
	void EnableScissor(bool enable);
	void SetScissorRect(TScreen screen, TView view);
};