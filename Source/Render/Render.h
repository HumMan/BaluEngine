#pragma once

#include "RenderCommand.h"

#include <Interfaces/ExportMacro.h>

#include <vector>

#include <Common/ICommon.h>

namespace BaluRender
{
	class TBaluRender;
}
using namespace BaluRender;

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
