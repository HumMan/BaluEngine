#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

class TSpritePolygonAdornment : public  TBoundaryBoxAdornment
{
	TBaluSpritePolygonDef* sprite_polygon_def;
public:
	TBaluSpritePolygonDef* GetSprite(){ return sprite_polygon_def; }
	TSpritePolygonAdornment(TBaluSpritePolygonDef* sprite_polygon_def);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
	bool IsCollideWithAdornment(TVec2 world_cursor_location);
	bool IsCollideWithObject(TVec2 world_cursor_location);
};