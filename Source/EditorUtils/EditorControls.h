#pragma once

#include <baluLib.h>

#include "DrawingHelper.h"
#include "abstractEditor.h"

class TEditorControl
{
public:
	virtual float GetDistance(TVec2 pos) = 0;
	virtual void Render(TDrawingHelper* drawing_helper)=0;
	virtual void SetPosition(TVec2 position) = 0;
	virtual TVec2 GetPosition() = 0;
};

class TEditorObjectControls
{
private:
	enum class TState
	{
		None,
		ControlMove,
	} state;

	int control_under_cursor;
	TVec2 start_move_cursor_pos;
	TVec2 start_move_control_pos;

	std::vector<TEditorControl*> control_points;
public:
	int GetNearestControl(TVec2 cursor_pos, float& distance)const;
	TEditorObjectControls();
	int AddControl(TEditorControl* control);

	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual bool IsCursorCaptured();

	virtual void OnControlMove(int changed_control, TVec2 new_pos) = 0;

	virtual void Render(TDrawingHelper* drawing_helper);
	virtual bool IsCollideWithAdornment(TVec2 world_cursor_location) = 0;
	virtual bool IsCollideWithObject(TVec2 world_cursor_location) = 0;
};

class TEditorControlPoint : public TEditorControl
{
private:
	TVec2 position;
public:
	float GetDistance(TVec2 position)
	{
		return this->position.Distance(position);
	}
	void Render(TDrawingHelper* drawing_helper)
	{
		drawing_helper->DrawPoint(position);
	}
	void SetPosition(TVec2 position)
	{
		this->position = position;
	}
	TVec2 GetPosition()
	{
		return position;
	}
};