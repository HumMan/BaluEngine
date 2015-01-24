#pragma once

#include "../../BaluLib/Source/Math/vec.h"

#include <vector>

#include "exportMacro.h"

namespace EngineInterface
{

	class BALUENGINEDLL_API TFrame
	{
	public:
		TVec2 left_bottom;
		TVec2 right_top;
		TFrame(TVec2 left_bottom, TVec2 right_top);
	};

	class TAnimDesc
	{
	public:
		virtual TFrame GetFrame(int index) = 0;
	};

	class BALUENGINEDLL_API TSpecificFrame : public TAnimDesc
	{
		TVec2 left_bottom;
		TVec2 right_top;
	public:
		TSpecificFrame(TVec2 left_bottom, TVec2 right_top);
		TFrame GetFrame(int index);
	};

	class BALUENGINEDLL_API TGridFrames : public TAnimDesc
	{
		TVec2 left_bottom;
		TVec2 width_height;
		int cell_count_x;
		int cell_count_y;
	public:
		TGridFrames(TVec2 left_bottom, TVec2 width_height, int cell_count_x, int cell_count_y);
		TFrame GetFrame(int index);
	};

	class BALUENGINEDLL_API TFramesRange
	{
		int start;
		int end;
	public:
		TFramesRange(int start, int end);
	};

	class BALUENGINEDLL_API TAnimationFrames
	{
	public:
		TAnimDesc* desc;
		std::vector<int> frames;
		TAnimationFrames(TAnimDesc* desc, std::vector<int> frames);
		TAnimationFrames(TAnimDesc* desc, int frame);
	};

	class BALUENGINEDLL_API TAnimLine
	{
	public:
		std::string line_name;
		std::vector<TAnimationFrames> frames;
	};
}

BALUENGINEDLL_API std::vector<int> FramesRange(int start, int end);