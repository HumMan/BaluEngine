#include "OBBGuiInstance.h"

#include "..\EditorUtils\DrawingHelper.h"

void TPointAdornment::Render(TDrawingHelper* helper)const
{
	helper->RenderPointAdornment(this->pos);
}

void TOBBAdornment::Render(TDrawingHelper* helper)const
{
	helper->RenderBoxCountour(this->box,4);
}


void TBoundaryBoxAdornment::OnControlMove(int changed_control, TVec2 new_pos)
{
	TPointAdornment p = controls[changed_control];
	TVec2 diff = new_pos - p.GetPosition();
	auto old_boundary = boundary;
	switch (controls[changed_control].type)
	{
	case TPointAdornmentType::Move:
		boundary.SetPos(new_pos);
		UpdatePointsPos();
		OnChange->BoxMove(old_boundary.pos, boundary.pos);
		break;
	case TPointAdornmentType::Resize:
	{
		TAABB<float, 2> source_b = start_edit_boundary.GetLocalAABB();
		TAABB<float, 2> old_b = boundary.GetLocalAABB();

		TVec2 local_diff = boundary.GetOrient().TransMul(diff);

		auto scale = boundary.GetOrient().TransMul(new_pos - boundary.GetPos()) / boundary.GetOrient().TransMul(p.GetPosition() - boundary.GetPos());

		if (p.x_resize == -1)
			local_diff[0] = -local_diff[0];
		if (p.x_resize == 0)
		{
			local_diff[0] = 0;
			scale[0] = 1;
		}
		if (p.x_resize == 1)
			local_diff[0] = local_diff[0];

		if (p.y_resize == -1)
			local_diff[1] = -local_diff[1];
		if (p.y_resize == 0)
		{
			local_diff[1] = 0;
			scale[1] = 1;
		}
		if (p.y_resize == 1)
			local_diff[1] = local_diff[1];

		//old_b.Extend(local_diff);
		old_b.border[0] *= scale;
		old_b.border[1] *= scale;
		boundary.SetAABB(old_b);

		UpdatePointsPos();
		OnChange->BoxResize(old_boundary, boundary, scale);
	}
	break;
	case TPointAdornmentType::Rotate:
	{
		TVec2 rot_pos = boundary.GetPos();
		TVec2 xb = (new_pos - rot_pos).GetNormalized();
		boundary.SetOrient(TMatrix2(xb, xb.Cross()));
		UpdatePointsPos();
		OnChange->BoxRotate(old_boundary, boundary);
	}
	break;
	default:
		assert(false);
		break;
	}
}

bool TBoundaryBoxAdornment::IsCollide(TVec2 point)
{
	TVec2 cursor_pos = point;
	const float point_select_threshold = 0.3;
	float nearest_point_dist = 0;
	float nearest_point_id = GetNearestControl(point, nearest_point_dist);
	bool obj_collide = boundary.PointCollide(cursor_pos);
	if (nearest_point_id != -1 && nearest_point_dist < point_select_threshold)
	{
		box_under_cursor = false;
		point_under_cursor = nearest_point_id;
	}
	else if (obj_collide)
	{
		box_under_cursor = true;
		point_under_cursor = -1;
	}
	else
	{
		box_under_cursor = false;
		point_under_cursor = -1;
	}

	return box_under_cursor || point_under_cursor != -1;
	//return boundary.Contain(point);
}

void TBoundaryBoxAdornment::UpdatePointsPos()
{
	for (TPointAdornment& p : controls)
	{
		switch (p.type)
		{
		case TPointAdornmentType::Move:
			p.SetPosition(boundary.GetPos());
			break;
		case TPointAdornmentType::Resize:
		{
			TAABB<float, 2> aabb = boundary.GetLocalAABB();
			TMatrix<float, 2> or = boundary.GetOrient();
			TVec2 pos = boundary.GetPos();
			TVec2 new_pos = p.GetPosition();
			if (p.x_resize == -1)
				new_pos[0] = aabb[0][0];
			if (p.x_resize == 0)
				new_pos[0] = 0;
			if (p.x_resize == 1)
				new_pos[0] = aabb[1][0];

			if (p.y_resize == -1)
				new_pos[1] = aabb[0][1];
			if (p.y_resize == 0)
				new_pos[1] = 0;
			if (p.y_resize == 1)
				new_pos[1] = aabb[1][1];

			p.SetPosition(or*new_pos + pos);
		}
		break;
		case TPointAdornmentType::Rotate:
		{
			TAABB<float, 2> aabb = boundary.GetLocalAABB();
			TMatrix<float, 2> or = boundary.GetOrient();
			TVec2 pos = boundary.GetPos();
			TVec2 new_pos = p.GetPosition();

			if (p.x_resize == -1)
				new_pos[0] = aabb[0][0] - 0.2;
			if (p.x_resize == 0)
				new_pos[0] = 0;
			if (p.x_resize == 1)
				new_pos[0] = aabb[1][0] + 0.2;

			if (p.y_resize == -1)
				new_pos[1] = aabb[0][1] - 0.2;
			if (p.y_resize == 0)
				new_pos[1] = 0;
			if (p.y_resize == 1)
				new_pos[1] = aabb[1][1] + 0.2;

			p.SetPosition(or*new_pos + pos);
		}
		break;
		default:
			break;
		}
	}
}

std::vector<TPointAdornment> InitControlPointsByBoundary(TOBB<float, 2> boundary)
{
	std::vector<TPointAdornment> control_points;
	control_points.emplace_back(TPointAdornmentType::Move, 0, 0, boundary.GetPos());

	control_points.emplace_back(TPointAdornmentType::Resize, 1, 1, boundary.GetPos());
	control_points.emplace_back(TPointAdornmentType::Resize, 1, 0, boundary.GetPos());
	control_points.emplace_back(TPointAdornmentType::Resize, 1, -1, boundary.GetPos());
	control_points.emplace_back(TPointAdornmentType::Resize, 0, 1, boundary.GetPos());

	control_points.emplace_back(TPointAdornmentType::Resize, 0, -1, boundary.GetPos());
	control_points.emplace_back(TPointAdornmentType::Resize, -1, 1, boundary.GetPos());
	control_points.emplace_back(TPointAdornmentType::Resize, -1, 0, boundary.GetPos());
	control_points.emplace_back(TPointAdornmentType::Resize, -1, -1, boundary.GetPos());

	control_points.emplace_back(TPointAdornmentType::Rotate, 1, 0, boundary.GetPos());
	return control_points;
}

TBoundaryBoxAdornment::TBoundaryBoxAdornment()
{
	control_under_cursor = -1;
	state = TState::None;
	boundary = TOBB<float, 2>(TVec2(0, 0), TMatrix2::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(4, 2)));

	controls = InitControlPointsByBoundary(boundary);

	UpdatePointsPos();

	enable = false;
}

int TBoundaryBoxAdornment::GetNearestControl(TVec2 cursor_pos, float& distance)const
{
	const float point_select_threshold = 0.3;
	float nearest_point_dist = 0;
	int nearest_point_id = -1;
	for (int i = 0; i < controls.size(); i++)
	{
		float dist = controls[i].GetDistance(cursor_pos);
		if (dist < nearest_point_dist || nearest_point_id == -1)
		{
			nearest_point_id = i;
			nearest_point_dist = dist;
		}
	}
	if (nearest_point_id != -1)
	{
		distance = nearest_point_dist;
		if (distance<0.3)
			return nearest_point_id;
	}
	return -1;
}



TBoundaryBoxAdornment::TBoundaryBoxAdornment(TOBB<float, 2> boundary)
{
	control_under_cursor = -1;
	state = TState::None;
	this->boundary = boundary;

	controls = InitControlPointsByBoundary(boundary);

	UpdatePointsPos();
}
TBoundaryBoxAdornment::TBoundaryBoxAdornment(TVec2 pos)
{
	control_under_cursor = -1;
	state = TState::None;
	boundary = TOBB<float, 2>(pos, TMatrix2::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(4, 2)));

	controls = InitControlPointsByBoundary(boundary);

	UpdatePointsPos();
}

void TBoundaryBoxAdornment::SetBoundary(TOBB2 box)
{
	boundary = box;
	UpdatePointsPos();
}

bool TBoundaryBoxAdornment::OnStartBoxMove(int changed_box_control, TVec2 new_pos)
{
	return true;
}

void TBoundaryBoxAdornment::OnMouseDown(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location)
{
	if (!enable)
		return;
	if (state == TState::None)
	{
		if (control_under_cursor != -1)
		{
			state = TState::ControlMove;
			start_move_control_pos = controls[control_under_cursor].GetPosition();
			start_move_cursor_pos = scene_cursor_location;
		}
	}
}

void TBoundaryBoxAdornment::OnMouseMove(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location)
{
	if (!enable)
		return;
	if (state == TState::None)
	{
		float dist = 0;
		control_under_cursor = GetNearestControl(scene_cursor_location, dist);
		//if (dist > 0.1)
		//	control_under_cursor = -1;
		//auto nearest
		//if (nearest_point_id != -1 && nearest_point_dist < point_select_threshold)
		//{
		//	control_under_cursor = control_points[nearest_point_id];
		//}
		//Collide(cursor_pos);
	}
	else if (state == TState::ControlMove)
	{
		if (control_under_cursor != -1)
		{
			TVec2 new_pos = start_move_control_pos + (scene_cursor_location - start_move_control_pos);
			//control_points[control_under_cursor]->SetPosition(new_pos);
			OnControlMove(control_under_cursor, new_pos);
		}
	}
}
void TBoundaryBoxAdornment::OnMouseUp(EngineInterface::TMouseEventArgs e, TVec2 scene_cursor_location)
{
	if (!enable)
		return;
	if (state == TState::None)
	{
	}
	else if (state == TState::ControlMove)
	{
		state = TState::None;
	}
}
bool TBoundaryBoxAdornment::IsCursorCaptured()
{
	return state != TState::None;
}