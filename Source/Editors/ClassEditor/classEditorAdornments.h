#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

class TClassSpriteAdornment : public  TBoundaryBoxAdornment
{
	TBaluClass* balu_class;
	int sprite_id;
public:
	//TBaluSpritePolygonDef* GetSprite(){ return sprite_polygon_def; }
	TClassSpriteAdornment(TBaluSpritePolygonDef* sprite_polygon_def);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
	bool IsCollideWithAdornment(TVec2 world_cursor_location);
	bool IsCollideWithObject(TVec2 world_cursor_location);
};

class TClassPhysBodyAdornment : public  TBoundaryBoxAdornment
{
	TBaluPhysBodyDef* sprite_polygon_def;
public:
	//TBaluSpritePolygonDef* GetSprite(){ return sprite_polygon_def; }
	TClassPhysBodyAdornment(TBaluSpritePolygonDef* sprite_polygon_def);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
	bool IsCollideWithAdornment(TVec2 world_cursor_location);
	bool IsCollideWithObject(TVec2 world_cursor_location);
};