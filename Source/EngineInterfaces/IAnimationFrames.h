#pragma once

#include "../../BaluLib/Source/Math/vec.h"

#include <vector>

namespace EngineInterface
{

	class TFrame
	{
	public:
		TVec2 left_bottom;
		TVec2 right_top;
		TFrame(TVec2 left_bottom, TVec2 right_top);
	};
	//
	//class IAnimDesc
	//{
	//
	//};
	//
	//class ISpecificFrame
	//{
	//public:
	//};
	//
	//class IGridFrame
	//{
	//public:
	//};
	//
	//class IAnimDescFactory
	//{
	//public:
	//	virtual ISpecificFrame* CreateSpecificFrame() = 0;
	//	virtual IGridFrame* CreateGridFrame() = 0;
	//};

	class TAnimDesc
	{
	public:
		virtual TFrame GetFrame(int index) = 0;
	};

	class TSpecificFrame : public TAnimDesc
	{
		TVec2 left_bottom;
		TVec2 right_top;
	public:
		TSpecificFrame(TVec2 left_bottom, TVec2 right_top);
		TFrame GetFrame(int index);
	};

	class TGridFrames : public TAnimDesc
	{
		TVec2 left_bottom;
		TVec2 width_height;
		int cell_count_x;
		int cell_count_y;
	public:
		TGridFrames(TVec2 left_bottom, TVec2 width_height, int cell_count_x, int cell_count_y);
		TFrame GetFrame(int index);
	};

	class TFramesRange
	{
		int start;
		int end;
	public:
		TFramesRange(int start, int end);
	};

	class TAnimationFrames
	{
	public:
		TAnimDesc* desc;
		std::vector<int> frames;
		TAnimationFrames(TAnimDesc* desc, std::vector<int> frames);
		TAnimationFrames(TAnimDesc* desc, int frame);
	};

	class TAnimLine
	{
	public:
		std::string line_name;
		std::vector<TAnimationFrames> frames;
	};
}