#pragma once

#include "RenderCommand.h"

#include <WorldObjects\Material\IMaterial.h>

#include <Interfaces\ExportMacro.h>

#include <vector>

class TBaluRender;

namespace EngineInterface
{

	class BALUENGINEDLL_API TRender
	{
		TBaluRender* render;
	public:
		TRender(TBaluRender* internal_render);
		~TRender();
		void Render(std::vector<TRenderCommand>& render_commands, std::vector<IGUIVisual*>& gui, EngineInterface::IViewport* viewport);
		void EnableScissor(bool enable);
		void SetScissorRect(TScreen screen, TView view);
		TBaluRender* GetInternalRender()
		{
			return render;
		}
	};
}