#include "physBodyEditorTools.h"

#include "BoundaryEditor.h"

#include "physBodyEditor.h"

TCreatePolygonTool::TCreatePolygonTool(TPhysBodyEditor* phys_body_editor)
{
	this->phys_body_editor = phys_body_editor;
}

void TCreatePolygonTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	auto new_box = new TPolygonShapeAdornment(world_cursor_location);
	phys_body_editor->AddBoundary(new_box);
}

void TCreatePolygonTool::OnMouseMove(TMouseEventArgs e, TVec2 wolrd_cursor_location)
{

}
void TCreatePolygonTool::OnMouseUp(TMouseEventArgs e, TVec2 wolrd_cursor_location)
{

}
void TCreatePolygonTool::Render(TDrawingHelper* drawing_helper)
{

}

TPolygonShapeAdornment::TPolygonShapeAdornment(TVec2 pos) :TBoundaryBoxAdornment(pos)
{
}

void TPolygonShapeAdornment::OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
{

}

void TPolygonShapeAdornment::Render(TDrawingHelper* drawing_helper)
{
	TBoundaryBoxAdornment::Render(drawing_helper);
}
