#pragma once

#include <list>
#include <baluLib.h>

#include "DrawingHelper.h"
#include "abstractEditor.h"

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

class TAdornment
{
private:
	enum class TState
	{
		None,
		PointMove,
	} state;
	int point_under_cursor;
	TVec2 old_cursor_pos;

	void Collide(TVec2 cursor_pos);
	void OnMouseMove(TVec2 cursor_pos);
	void OnMouseDown();
	void OnMouseUp();

protected:
	TWorldObjectDef* decorated_object;
	std::vector<TControlPoint> control_points;
public:
	TAdornment();
	virtual void OnMouseDown(TMouseEventArgs e, TVec2 wolrd_cursor_location);
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 wolrd_cursor_location);
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 wolrd_cursor_location);
	virtual bool IsCursorCaptured(){ return true; }
	virtual bool IsCollide(TVec2 point) = 0;
	virtual void OnControlMove(int changed_control, TVec2 old_pos, TVec2 new_pos) = 0;

	virtual void Render(TDrawingHelper* drawing_helper);
};

class TJointAdornment : public TAdornment
{
public:
};

class TBoundaryBoxAdornment : public TAdornment
{
protected:
	TOBB<float, 2> boundary;
public:
	TBoundaryBoxAdornment();
	TBoundaryBoxAdornment(TOBB<float, 2> boundary);
	TBoundaryBoxAdornment(TVec2 pos);
	void OnControlMove(int changed_control, TVec2 old_pos, TVec2 new_pos);
	virtual void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)=0;
	virtual void Render(TDrawingHelper* drawing_helper);
	void UpdatePointsPos();
	bool IsCollide(TVec2 point);
};