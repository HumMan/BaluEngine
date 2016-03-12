#pragma once

#include <baluLib.h>
#include "../Material/IMaterialInstance.h"
#include "OBBGui.h"

#include <Render/RenderCommand.h>

#include <World\IWorld.h>

using namespace EngineInterface;

class TBoundaryBoxChangeListener
{
public:
	virtual void BoxResize(TOBB<float, 2> old_box, TOBB<float, 2> new_box, TVec2 scale) = 0;
	virtual void BoxMove(TVec2 old_pos, TVec2 new_pos) = 0;
	virtual void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box) = 0;
};

enum class TPointAdornmentType
{
	Move,
	Resize,
	Scale,
	Rotate
};

namespace EngineInterface
{
	class TDrawingHelper;
}

class TPointAdornment : public EngineInterface::IGUIVisual
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
	void Render(EngineInterface::TDrawingHelper* helper)const;
};

class TOBBAdornment : public EngineInterface::IGUIVisual
{
public:
	TOBB2 box;

	float GetDistance(TVec2 pos)const;
	void SetPosition(TVec2 position);
	TVec2 GetPosition()const;
	void Render(EngineInterface::TDrawingHelper* helper)const;
};

class TBoundaryBoxAdornment : public EngineInterface::TSceneObjectInstance, public TOBBGuiDef, public EngineInterface::IGUIVisual
{
private:
	TOBB<float, 2> start_edit_boundary;
	bool box_under_cursor;
	int point_under_cursor;

	std::vector<TPointAdornment> controls;

	void OnControlMove(int changed_control, TVec2 new_pos);

	bool OnStartBoxMove(int changed_box_control, TVec2 new_pos);

	

	void UpdatePointsPos();
	bool IsCollide(TVec2 point);

	enum class TState
	{
		None,
		ControlMove,
	} state;

	int control_under_cursor;
	TVec2 start_move_cursor_pos;
	TVec2 start_move_control_pos;
	int GetNearestControl(TVec2 cursor_pos, float& distance)const;


public:
	virtual void Render(EngineInterface::TDrawingHelper* drawing_helper)const;
	bool enable;

	//std::vector<TEditorControl*> Render();

	TBoundaryBoxChangeListener* OnChange;

	TBoundaryBoxAdornment(TBaluSceneInstance* scene);
	TBoundaryBoxAdornment(TBaluSceneInstance* scene, TOBBGui* source);
	TOBB2 GetOBB()
	{
		return boundary;
	}
	void SetBoundary(TOBB2 box);
	virtual void OnMouseDown(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location);
	virtual void OnMouseMove(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location);
	virtual void OnMouseUp(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location);
	virtual bool IsCursorCaptured();

	bool PointCollide(TVec2 scene_space_point)
	{
		return false;
		//return boundary.PointCollide(scene_space_point);
	}
};