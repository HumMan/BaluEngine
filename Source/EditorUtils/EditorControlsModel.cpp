#include "EditorControlsModel.h"

#include "DrawingHelper.h"

float TPointAdornment::GetDistance(TVec2 pos)const
{
	return this->pos.Distance(pos);
}

void TPointAdornment::SetPosition(TVec2 position)
{
	this->pos = pos;
}

TVec2 TPointAdornment::GetPosition()const
{
	return this->pos;
}

void TPointAdornment::Render(TDrawingHelper* helper)const
{
	helper->Render(this);
}

float TOBBAdornment::GetDistance(TVec2 pos)const
{
	TPointCollisionInfo<float, 2> collision;
	this->box.PointCollide(pos, collision);
	return collision.distance;
}
void TOBBAdornment::SetPosition(TVec2 position)
{
	this->box.pos = position;
}
TVec2 TOBBAdornment::GetPosition()const
{
	return box.pos;
}
void TOBBAdornment::Render(TDrawingHelper* helper)const
{
	helper->Render(this);
}

