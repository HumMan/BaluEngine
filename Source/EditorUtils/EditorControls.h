#pragma once

#include <baluLib.h>

#include "EditorControlsModel.h"

class TEditorObjectControls
{
private:
	

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

	//virtual void Render(TDrawingHelper* drawing_helper);
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
	//void Render(TDrawingHelper* drawing_helper)
	//{
	//	drawing_helper->DrawPoint(position);
	//}
	void SetPosition(TVec2 position)
	{
		this->position = position;
	}
	TVec2 GetPosition()
	{
		return position;
	}
};