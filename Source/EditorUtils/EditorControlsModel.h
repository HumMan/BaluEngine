#pragma once

#include <baluLib.h>

enum class TPointAdornmentType
{
	Move,
	Resize,
	//ResizeOneDim,
	Scale,
	//ScaleOneDim,
	Rotate
};

class TDrawingHelper;

class TEditorControl
{
public:
	virtual float GetDistance(TVec2 pos)const = 0;
	//virtual void Render(TDrawingHelper* drawing_helper)=0;
	virtual void SetPosition(TVec2 position) = 0;
	virtual TVec2 GetPosition()const = 0;
	virtual void Render(TDrawingHelper* helper)const = 0;
};

class TPointAdornment : public TEditorControl
{
public:
	TPointAdornmentType type;
	int x_resize;
	int y_resize;
	TVec2 pos;

	TPointAdornment(TPointAdornmentType type, int x_resize, int y_resize, TVec2 pos)
	{
		this->type = type;
		this->x_resize = x_resize;
		this->y_resize = y_resize;
		this->pos = pos;
	}
	float GetDistance(TVec2 pos)const;
	void SetPosition(TVec2 position);
	TVec2 GetPosition()const;
	void Render(TDrawingHelper* helper)const;
};

class TOBBAdornment : public TEditorControl
{
public:
	TOBB2 box;

	float GetDistance(TVec2 pos)const;
	void SetPosition(TVec2 position);
	TVec2 GetPosition()const;
	void Render(TDrawingHelper* helper)const;
};
