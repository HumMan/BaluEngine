#include "RenderCommand.h"

class TBaluRender;

class TRender
{
	TBaluRender* render;
public:
	TRender(TBaluRender* internal_render);

	void Render(std::vector<TRenderCommand>& render_commands);


};