#pragma once

#include "abstractEditor.h"
#include "BoundaryEditor.h"

class TPhysBodyEditor:public TAbstractEditor
{
	//TBoundaryEditor boundary_editor;
	std::vector<std::unique_ptr<TBoundaryBoxAdornment>> boundaries;
	std::vector<std::unique_ptr<TJointAdornment>> joints;

	TEditorTool* active_tool;
public:
	TPhysBodyEditor();
	void SetActiveTool(TEditorTool* use_tool);
	void UnsetAcitveTool();

	void AddBoundary(TBoundaryBoxAdornment* box);
	void AddJoint(TJointAdornment* joint);

	void Initialize(TWorldObjectDef* obj);
	void Initialize(TBaluPhysBodyDef* obj);

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	void EndSelectedAsWork();

	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);

	void Render(TDrawingHelper* drawing_helper);
};

//class TEditorPhysShape
//{
//public:
//	void CanMove();
//	void CanResize();
//	void CanRotate();
//	void OnMove();
//	void OnResize();
//	void OnRotate();
//	void Clone();
//	void Draw();
//
//	bool CanEdit();
//	TAbstractEditor* Edit();
//
//	TOBB<float, 2> bounding_box;
//};
//
//class TPhysBodyEditor : public TAbstractEditor
//{
//
//};
