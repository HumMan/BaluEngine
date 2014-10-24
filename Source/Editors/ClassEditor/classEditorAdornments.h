#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

class TClassSpriteAdornment : public  TBoundaryBoxAdornment
{
	TBaluSpriteInstanceDef* sprite_instance;
public:
	TBaluSpriteInstanceDef* GetSpriteInstance(){ return sprite_instance; }
	TClassSpriteAdornment(TBaluSpriteInstanceDef* sprite_instance);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
	bool IsCollideWithAdornment(TVec2 world_cursor_location);
	bool IsCollideWithObject(TVec2 world_cursor_location);
};

class TClassPhysBodyAdornment : public  TBoundaryBoxAdornment
{
	TBaluBodyInstanceDef* body_instance;
public:
	TBaluBodyInstanceDef* GetSprite(){ return body_instance; }
	TClassPhysBodyAdornment(TBaluBodyInstanceDef* body_instance);
	void OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box);
	void Render(TDrawingHelper* drawing_helper);
	bool IsCollideWithAdornment(TVec2 world_cursor_location);
	bool IsCollideWithObject(TVec2 world_cursor_location);
};