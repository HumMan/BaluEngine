
#pragma once

class NVGcontext;

namespace EngineInterface
{
	class IBaluScene;
	class IViewport;
	class TView;
	class TScreen;
}

#include <Common/ICommon.h>
namespace EngineInterface
{
	class TDrawingHelper
	{
		NVGcontext* context;
		TDrawingHelperContext drawing_context;
	public:
		TDrawingHelper(TDrawingHelperContext context);

		TDrawingHelperContext GetContext()
		{
			return drawing_context;
		}

		void RenderPointAdornment(TVec2 p, TBaluTransformWithScale trans = TBaluTransformWithScale());
		void RenderPointHighlightAdornment(TVec2 p, TBaluTransformWithScale trans = TBaluTransformWithScale());

		//
		void RenderBoxCountour(TOBB2 box, float width);
		void RenderSelectionBox(TOBB2 box);
		void RenderLinesLoop(const std::vector<TVec2>& vertices, TBaluTransformWithScale trans = TBaluTransformWithScale());
		void RenderLine(const TVec2& p0, const TVec2& p1, TBaluTransformWithScale trans = TBaluTransformWithScale());
	};
}
