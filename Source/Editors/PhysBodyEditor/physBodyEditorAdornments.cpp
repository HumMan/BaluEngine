#include "physBodyEditorAdornments.h"

TPolygonShapeAdornment::TPolygonShapeAdornment(TBaluPolygonShapeDef* polygon_world_object) :TBoundaryBoxAdornment(polygon_world_object->pos)
{
	this->polygon_world_object = polygon_world_object;
}

void TPolygonShapeAdornment::OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
{

}

void TPolygonShapeAdornment::Render(TDrawingHelper* drawing_helper)
{
	TBoundaryBoxAdornment::Render(drawing_helper);
	drawing_helper->DrawPolygon(polygon_world_object);
}


TCircleShapeAdornment::TCircleShapeAdornment(TBaluCircleShapeDef* circle_world_object) :TBoundaryBoxAdornment(circle_world_object->pos)
{
	this->circle_world_object = circle_world_object;
}
void TCircleShapeAdornment::OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
{

}
void TCircleShapeAdornment::Render(TDrawingHelper* drawing_helper)
{
	TBoundaryBoxAdornment::Render(drawing_helper);
	drawing_helper->DrawCircle(circle_world_object);
}
