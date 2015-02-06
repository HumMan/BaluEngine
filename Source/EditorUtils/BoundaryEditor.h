#pragma once

#include "EditorControls.h"

class TBoundaryBoxAdornment : public TEditorObjectControls
{
protected:
	TOBB<float, 2> start_edit_boundary;
	bool box_under_cursor;
	int point_under_cursor;

	TOBBAdornment boundary;
	std::vector<TPointAdornment> controls;
public:
	TBoundaryBoxAdornment();
	TBoundaryBoxAdornment(TOBB<float, 2> boundary);
	TBoundaryBoxAdornment(TVec2 pos);
	void OnControlMove(int changed_control, TVec2 new_pos);

	virtual bool OnStartBoxMove(int changed_box_control, TVec2 new_pos);
	virtual void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)=0;

	//void Render(TDrawingHelper* drawing_helper);
	void UpdatePointsPos();
	bool IsCollide(TVec2 point);

	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	virtual bool IsCursorCaptured();
};

class TBoundaryBoxScene
{
public:
	std::vector<std::unique_ptr<TBoundaryBoxAdornment>> boundaries;
	std::vector<TBoundaryBoxAdornment*> selected_boundaries; //TODO
	TBoundaryBoxAdornment* boundary_under_cursor;
};

class TBoundaryBoxesModifyTool : public IEditorTool
{
protected:
	TBoundaryBoxScene* boundary_box_scene;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::None;
	}
	//TBoundaryBoxesModifyTool(){}
	TBoundaryBoxesModifyTool(TBoundaryBoxScene* boundary_box_scene);
	//void SetScene(TBoundaryBoxScene* boundary_box_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
	~TBoundaryBoxesModifyTool(){}
};
