#pragma once

#include <baluLib.h>

enum class TPointAdornmentType
{
	Move,
	Resize,
	ResizeOneDim,
	Scale,
	ScaleOneDim,
	Rotate
};

class TDrawingHelper;

class TEditorControl
{
public:
	virtual float GetDistance(TVec2 pos) = 0;
	//virtual void Render(TDrawingHelper* drawing_helper)=0;
	virtual void SetPosition(TVec2 position) = 0;
	virtual TVec2 GetPosition() = 0;
	virtual void UpdateView(TDrawingHelper* helper) = 0;
};

class TPointAdornment : public TEditorControl
{
public:
	TVec2 pos;
	TPointAdornmentType type;
	int x_resize;
	int y_resize;

	float GetDistance(TVec2 pos);
	void SetPosition(TVec2 position);
	TVec2 GetPosition();
	void UpdateView(TDrawingHelper* helper);
};

class TOBBAdornment : public TEditorControl
{
public:
	TOBB2 box;

	float GetDistance(TVec2 pos);
	void SetPosition(TVec2 position);
	TVec2 GetPosition();
	void UpdateView(TDrawingHelper* helper);
};
