#pragma once

#include "RenderCommand.h"

#include <Interfaces/ExportMacro.h>

#include <vector>


#include "WorldDef/Interface.h"

namespace BaluRender
{
	class TBaluRender;
}

namespace BaluEngine
{
	namespace WorldInstance
	{
		namespace Internal
		{

			class TRender
			{
				BaluRender::TBaluRender* render;
			public:
				TRender(BaluRender::TBaluRender* internal_render);
				~TRender();
				void Render(std::vector<TRenderCommand>& render_commands, std::vector<IGUIVisual*>& gui, BaluEngine::WorldDef::IViewport* viewport);
				void EnableScissor(bool enable);
				void SetScissorRect(TScreen screen, TView view);
				BaluRender::TBaluRender* GetInternalRender()
				{
					return render;
				}
			};
		}
	}
}
