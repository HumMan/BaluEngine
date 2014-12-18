#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

class TPolygonShapeAdornment : public  TBoundaryBoxAdornment
{
	TBaluPolygonShapeDef* polygon_world_object;
public:
	
	TPolygonShapeAdornment(TBaluPolygonShapeDef* polygon_world_object);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
	bool IsCollideWithAdornment(TVec2 world_cursor_location);
	bool IsCollideWithObject(TVec2 world_cursor_location);
};

class TCircleShapeAdornment : public  TBoundaryBoxAdornment
{
	TBaluCircleShapeDef* circle_world_object;
public:

	TCircleShapeAdornment(TBaluCircleShapeDef* circle_world_object);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
	bool IsCollideWithAdornment(TVec2 world_cursor_location);
	bool IsCollideWithObject(TVec2 world_cursor_location);
};