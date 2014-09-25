#pragma once

#include "EditorControls.h"
//
//enum class TControlType
//{
//	Pivot,
//	Resize,
//	Rotate
//};
//
//class TControlPoint
//{
//public:
//	TControlType type;
//	int x_resize;
//	int y_resize;
//	TVec2 pos;
//	TControlPoint(){}
//	TControlPoint(TControlType type, int x_resize, int y_resize, TVec2 pos)
//	{
//		this->type = type;
//		this->x_resize = x_resize;
//		this->y_resize = y_resize;
//		this->pos = pos;
//	}
//};
//
//class TAdornment
//{
//protected:
//	enum class TState
//	{
//		None,
//		PointMove,
//	} state;
//	int point_under_cursor;
//	TVec2 old_cursor_pos;
//
//	void Collide(TVec2 cursor_pos);
//	void OnMouseMove(TVec2 cursor_pos);
//	void OnMouseDown();
//	void OnMouseUp();
//
//protected:
//	TWorldObjectDef* decorated_object;
//	std::vector<TControlPoint> control_points;
//public:
//	TAdornment();
//	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
//	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
//	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
//	virtual bool IsCursorCaptured() = 0;
//	virtual bool IsCollide(TVec2 point) = 0;
//	virtual void OnControlMove(int changed_control, TVec2 old_pos, TVec2 new_pos) = 0;
//
//	virtual void Render(TDrawingHelper* drawing_helper);
//};

class TJointAdornment : public TEditorObjectControls
{
protected:
public:
};

enum class TControlType
	{
		Pivot,
		Resize,
		Rotate
	};

class TBoundaryBoxControlPoint: public TEditorControlPoint
{
public:
	TControlType type;
	int x_resize;
	int y_resize;
	TBoundaryBoxControlPoint(){}
	TBoundaryBoxControlPoint(TControlType type, int x_resize, int y_resize, TVec2 pos)
	{
		SetPosition(pos);
		this->type = type;
		this->x_resize = x_resize;
		this->y_resize = y_resize;
	}
};

class TBoundaryBoxAdornment : public TEditorObjectControls
{
private:
	TOBB<float, 2> start_edit_boundary;
	TOBB<float, 2> boundary;
	bool box_under_cursor;
	int point_under_cursor;
	std::vector<TBoundaryBoxControlPoint> controls;
public:
	TBoundaryBoxAdornment();
	TBoundaryBoxAdornment(TOBB<float, 2> boundary);
	TBoundaryBoxAdornment(TVec2 pos);
	void OnControlMove(int changed_control, TVec2 new_pos);

	virtual bool OnStartBoxMove(int changed_box_control, TVec2 new_pos);
	virtual void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)=0;

	void Render(TDrawingHelper* drawing_helper);
	void UpdatePointsPos();
	bool IsCollide(TVec2 point);

	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual bool IsCursorCaptured();
};