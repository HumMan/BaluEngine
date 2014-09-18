#pragma once

#include <list>
#include <baluLib.h>

#include "DrawingHelper.h"

class TBoundaryObjectBehaivor
{
public:
	enum class TControlType
	{
		Pivot,
		Resize,
		Rotate
	};
	class TControlPoint
	{
	public:
		TControlType type;
		int x_resize;
		int y_resize;
		TVec2 pos;
		TControlPoint(){}
		TControlPoint(TControlType type, int x_resize, int y_resize, TVec2 pos)
		{
			this->type = type;
			this->x_resize = x_resize;
			this->y_resize = y_resize;
			this->pos = pos;
		}
	};
	enum class TState
	{
		None,
		PointMove,
		ObjectMove
	} state;

	TOBB<float, 2> boundary;
	//TVec2 pivot_offset;

	std::vector<TControlPoint> control_points;
	bool IsCursorCaptured();

	int point_under_cursor;
	bool object_under_cursor;

	TVec2 old_cursor_pos;

	TBoundaryObjectBehaivor();
	TBoundaryObjectBehaivor(TOBB<float, 2> boundary);

	void Collide(TVec2 cursor_pos);
	void UpdatePointsPos();
	void OnMouseMove(TVec2 cursor_pos);
	void OnMouseDown();
	void OnMouseUp();

	void Render(TDrawingHelper* drawing_helper);
};

class TBoundaryEditor
{
public:
	std::list<TBoundaryObjectBehaivor> objects;
	bool IsCursorCaptured();
	void OnMouseMove(TVec2 cursor_pos);
	void OnMouseDown();
	void OnMouseUp();
	void Render(TDrawingHelper* drawing_helper);
};