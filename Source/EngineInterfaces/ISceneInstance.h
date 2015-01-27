#pragma once

#include "../RenderCommand.h"

namespace EngineInterface
{
	class IBaluSceneInstance
	{
	public:
		virtual IViewport* GetViewport(std::string name)=0;
		virtual void QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<TCustomDrawCommand>& custom_draw) = 0;
	};
}