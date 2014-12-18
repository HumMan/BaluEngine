#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

class TClassInstanceAdornment : public  TBoundaryBoxAdornment
{
	TBaluInstanceDef* class_instance;
public:
	TBaluInstanceDef* GetSpriteInstance(){ return class_instance; }
	TClassInstanceAdornment(TBaluInstanceDef* class_instance);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
	bool IsCollideWithAdornment(TVec2 world_cursor_location);
	bool IsCollideWithObject(TVec2 world_cursor_location);
};