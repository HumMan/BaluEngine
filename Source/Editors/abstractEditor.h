#pragma once

#include <vector>
#include <map>
#include <list>

#include <baluLib.h>

#include "../baluEditorDefs.h"

class TAbstractEditor
{
public:
	std::vector<TAbstractEditor*> parent_editors;

	TAbstractEditor* current_local_editor;

	void MouseMove();
	void MouseDown();
	void MouseUp();

	//void Edit(TAbstractEditorObject* obj);

	//std::map<std::string, TAbstractEditorObject*> CanCreateObjects();
};

class TBaluRender;

void DrawSprite(TBaluRender* render, TBaluSpriteDef* sprite);

void DrawLine(TBaluRender* render, TVec2 p0, TVec2 p1);

void DrawPoint(TBaluRender* render, TVec2 p);

void DrawSpriteContour(TBaluRender* render, TBaluSpriteDef* sprite);

void ActivateMaterial(TBaluRender* render, TBaluMaterialDef* material);

void DeactivateMaterial(TBaluRender* render, TBaluMaterialDef* material);

void DrawBoundary(TOBB<float, 2> boundary, TBaluRender* render);

class TBoundaryObjectBehaivor
{
public:
	enum class TControlType
	{
		Pivot,
		Resize,
		Rotate
	};
	class TControlPoint
	{
	public:
		TControlType type;
		int x_resize;
		int y_resize;
		TVec2 pos;
		TControlPoint(){}
		TControlPoint(TControlType type, int x_resize, int y_resize, TVec2 pos)
		{
			this->type = type;
			this->x_resize = x_resize;
			this->y_resize = y_resize;
			this->pos = pos;
		}
	};
	enum class TState
	{
		None,
		PointMove,
		ObjectMove
	} state;

	TOBB<float,2> boundary;
	//TVec2 pivot_offset;

	std::vector<TControlPoint> control_points;
	bool IsCursorCaptured();
	
	int point_under_cursor;
	bool object_under_cursor;

	TVec2 old_cursor_pos;

	TBoundaryObjectBehaivor()
	{
		point_under_cursor = -1;
		object_under_cursor = false;
		state = TState::None;

		boundary = TOBB<float, 2>(TVec2(0, 0), TMatrix2::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(4, 2)));

		control_points.emplace_back(TControlType::Pivot,0,0,boundary.GetPos());

		control_points.emplace_back(TControlType::Resize, 1, 1, boundary.GetPos());
		control_points.emplace_back(TControlType::Resize, 1, 0, boundary.GetPos());
		control_points.emplace_back(TControlType::Resize, 1, -1, boundary.GetPos());
		control_points.emplace_back(TControlType::Resize, 0, 1, boundary.GetPos());
		
		control_points.emplace_back(TControlType::Resize, 0, -1, boundary.GetPos());
		control_points.emplace_back(TControlType::Resize, -1, 1, boundary.GetPos());
		control_points.emplace_back(TControlType::Resize, -1, 0, boundary.GetPos());
		control_points.emplace_back(TControlType::Resize, -1, -1, boundary.GetPos());

		control_points.emplace_back(TControlType::Rotate, 1, 0, boundary.GetPos());

		UpdatePointsPos();
	}

	void Collide(TVec2 cursor_pos)
	{
		const float point_select_threshold = 0.3;
		float nearest_point_dist = 0;
		float nearest_point_id = -1;
		for (int i = 0; i < control_points.size(); i++)
		{
			float dist = cursor_pos.Distance(control_points[i].pos);
			if (dist < nearest_point_dist || nearest_point_id == -1)
			{
				nearest_point_id = i;
				nearest_point_dist = dist;
			}
		}
		bool obj_collide = boundary.Contain(cursor_pos);
		if (nearest_point_id != -1 && nearest_point_dist < point_select_threshold)
		{
			object_under_cursor = false;
			point_under_cursor = nearest_point_id;
		}
		else if (obj_collide)
		{
			object_under_cursor = true;
			point_under_cursor = -1;
		}
		else
		{
			object_under_cursor = false;
			point_under_cursor = -1;
		}
	}
	void UpdatePointsPos()
	{
		for (TControlPoint& p : control_points)
		{
			switch (p.type)
			{
			case TControlType::Pivot:
				p.pos = boundary.GetPos();
				break;
			case TControlType::Resize:
			{
				TAABB<float, 2> aabb = boundary.GetLocalAABB();
				TMatrix<float, 2> or = boundary.GetOrient();
				TVec2 pos = boundary.GetPos();
				if (p.x_resize == -1)
					p.pos[0] = aabb[0][0];
				if (p.x_resize == 0)
					p.pos[0] = 0;
				if (p.x_resize == 1)
					p.pos[0] = aabb[1][0];

				if (p.y_resize == -1)
					p.pos[1] = aabb[0][1];
				if (p.y_resize == 0)
					p.pos[1] = 0;
				if (p.y_resize == 1)
					p.pos[1] = aabb[1][1];

				p.pos = or*p.pos+pos;
			}
				break;
			case TControlType::Rotate:
			{
				TAABB<float, 2> aabb = boundary.GetLocalAABB();
				TMatrix<float, 2> or = boundary.GetOrient();
				TVec2 pos = boundary.GetPos();
				if (p.x_resize == -1)
					p.pos[0] = aabb[0][0]-0.2;
				if (p.x_resize == 0)
					p.pos[0] = 0;
				if (p.x_resize == 1)
					p.pos[0] = aabb[1][0] + 0.2;

				if (p.y_resize == -1)
					p.pos[1] = aabb[0][1] - 0.2;
				if (p.y_resize == 0)
					p.pos[1] = 0;
				if (p.y_resize == 1)
					p.pos[1] = aabb[1][1] + 0.2;

				p.pos = or*p.pos + pos;
			}
				break;
			default:
				break;
			}
		}
	}
	void OnMouseMove(TVec2 cursor_pos)
	{
		
		if (state == TState::None)
		{
			Collide(cursor_pos);
		}
		else if (state == TState::PointMove)
		{
			if (point_under_cursor != -1)
			{
				TControlPoint p = control_points[point_under_cursor];
				TVec2 diff = cursor_pos - old_cursor_pos;
				switch (p.type)
				{
				case TControlType::Pivot:
					boundary.SetPos(boundary.GetPos() + diff);
					UpdatePointsPos();
					break;
				case TControlType::Resize:
				{
					TAABB<float, 2> old_b = boundary.GetLocalAABB();
					
					TVec2 local_diff = boundary.GetOrient().TransMul(diff);

					if (p.x_resize == -1)
						local_diff[0] = -local_diff[0];
					if (p.x_resize == 0)
						local_diff[0] = 0;
					if (p.x_resize == 1)
						local_diff[0] = local_diff[0];

					if (p.y_resize == -1)
						local_diff[1] = -local_diff[1];
					if (p.y_resize == 0)
						local_diff[1] = 0;
					if (p.y_resize == 1)
						local_diff[1] = local_diff[1];

					old_b.Extend(local_diff);
					boundary.SetAABB(old_b);

					UpdatePointsPos();
				}
					break;
				case TControlType::Rotate:
				{
					TVec2 rot_pos = boundary.GetPos();
					TVec2 xb = (cursor_pos - rot_pos).GetNormalized();
					boundary.SetOrient(TMatrix2(xb, xb.Cross()));
					UpdatePointsPos();
				}
					break;
				default:
					break;
				}
			}
		}
		else if (state == TState::ObjectMove)
		{
			state = TState::None;
		}
		this->old_cursor_pos = cursor_pos;
	}
	void OnMouseDown()
	{
		if (state == TState::None)
		{
			if (point_under_cursor != -1)
			{
				state = TState::PointMove;
			}
			else if (object_under_cursor)
			{
				state = TState::ObjectMove;
			}
		}
	}
	void OnMouseUp()
	{
		if (state == TState::None)
		{
		}
		else if (state == TState::PointMove)
		{
			state = TState::None;
		}
		else if (state == TState::ObjectMove)
		{
			state = TState::None;
		}
	}
	
	void Render(TBaluRender* render);
};

class TBoundaryEditor
{
public:
	std::list<TBoundaryObjectBehaivor> objects;
	bool IsCursorCaptured();
	void OnMouseMove(TVec2 cursor_pos)
	{
		for (TBoundaryObjectBehaivor& v : objects)
			v.OnMouseMove(cursor_pos);
	}
	void OnMouseDown()
	{
		for (TBoundaryObjectBehaivor& v : objects)
			v.OnMouseDown();
	}
	void OnMouseUp()
	{
		for (TBoundaryObjectBehaivor& v : objects)
			v.OnMouseUp();
	}
	void Render(TBaluRender* render)
	{
		for (TBoundaryObjectBehaivor& v : objects)
			v.Render(render);
	}
};

