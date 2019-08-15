#pragma once

#include "../WorldInstance/Interface.h"

class NVGcontext;

namespace BaluEngine
{
	namespace WorldInstance
	{
		class TScreen;
		class TView;

		struct TDrawingHelperContext
		{
			TScreen* screen;
			TView* view;
			WorldDef::IViewport* viewport;
			TDrawingHelperContext()
			{
				screen = nullptr;
				view = nullptr;
				viewport = nullptr;
			}
			BaluLib::TVec2 FromScreenPixelsToScene(BaluLib::TVec2i screen_pixels);
			BaluLib::TVec2i FromSceneToScreenPixels(BaluLib::TVec2 scene_coordinates);
		};

		namespace Internal
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

				void RenderPointAdornment(BaluLib::TVec2 p, WorldDef::TTransformWithScale trans = WorldDef::TTransformWithScale());
				void RenderPointHighlightAdornment(BaluLib::TVec2 p, WorldDef::TTransformWithScale trans = WorldDef::TTransformWithScale());

				//
				void RenderBoxCountour(BaluLib::TOBB2 box, float width);
				void RenderSelectionBox(BaluLib::TOBB2 box);
				void RenderLinesLoop(const std::vector<BaluLib::TVec2>& vertices, WorldDef::TTransformWithScale trans = WorldDef::TTransformWithScale());
				void RenderLine(const BaluLib::TVec2& p0, const BaluLib::TVec2& p1, WorldDef::TTransformWithScale trans = WorldDef::TTransformWithScale());
			};
		}
	}
}
