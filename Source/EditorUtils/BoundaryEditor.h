#pragma once

#include "EditorControlsModel.h"

#include "../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

class TBoundaryBoxChangeListener
{
public:
	virtual void BoxResize(TOBB<float, 2> old_box, TOBB<float, 2> new_box) = 0;
	virtual void BoxMove(TVec2 old_pos, TVec2 new_pos) = 0;
	virtual void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box) = 0;
};

class TBoundaryBoxAdornment : public IVisualAdornment
{
private:
	TOBB<float, 2> start_edit_boundary;
	bool box_under_cursor;
	int point_under_cursor;

	TOBBAdornment boundary;
	std::vector<TPointAdornment> controls;

	void OnControlMove(int changed_control, TVec2 new_pos);

	bool OnStartBoxMove(int changed_box_control, TVec2 new_pos);

	//void Render(TDrawingHelper* drawing_helper);
	void UpdatePointsPos();
	bool IsCollide(TVec2 point);

	enum class TState
	{
		None,
		ControlMove,
	} state;

	int control_under_cursor;
	TVec2 start_move_cursor_pos;
	TVec2 start_move_control_pos;
	int GetNearestControl(TVec2 cursor_pos, float& distance)const;

	
public:

	bool enable;

	std::vector<TEditorControl*> Render();

	TBoundaryBoxChangeListener* OnChange;

	TBoundaryBoxAdornment();
	TBoundaryBoxAdornment(TOBB<float, 2> boundary);
	TBoundaryBoxAdornment(TVec2 pos);

	void SetBoundary(TOBB2 box);
	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual bool IsCursorCaptured();
};