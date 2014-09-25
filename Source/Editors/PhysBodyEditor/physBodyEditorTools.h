#pragma once

#include "../BoundaryEditor.h"

class TPhysBodyEditor;

class TPhysEditorTools : public TEditorTool
{
protected:
	TPhysBodyEditor* phys_body_editor;
};


class TPolygonShapeAdornment : public  TBoundaryBoxAdornment
{

public:
	TBaluPolygonShapeDef* polygon;

	TPolygonShapeAdornment(TVec2 pos);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
};

