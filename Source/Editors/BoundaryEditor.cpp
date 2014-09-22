#include "BoundaryEditor.h"


TAdornment::TAdornment()
{
	point_under_cursor = -1;
	state = TState::None;
}

std::vector<TControlPoint> InitControlPointsByBoundary(TOBB<float, 2> boundary)
{
	std::vector<TControlPoint> control_points;
	control_points.emplace_back(TControlType::Pivot, 0, 0, boundary.GetPos());

	control_points.emplace_back(TControlType::Resize, 1, 1, boundary.GetPos());
	control_points.emplace_back(TControlType::Resize, 1, 0, boundary.GetPos());
	control_points.emplace_back(TControlType::Resize, 1, -1, boundary.GetPos());
	control_points.emplace_back(TControlType::Resize, 0, 1, boundary.GetPos());

	control_points.emplace_back(TControlType::Resize, 0, -1, boundary.GetPos());
	control_points.emplace_back(TControlType::Resize, -1, 1, boundary.GetPos());
	control_points.emplace_back(TControlType::Resize, -1, 0, boundary.GetPos());
	control_points.emplace_back(TControlType::Resize, -1, -1, boundary.GetPos());

	control_points.emplace_back(TControlType::Rotate, 1, 0, boundary.GetPos());
	return control_points;
}

void TAdornment::Collide(TVec2 cursor_pos)
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
	//bool obj_collide = boundary.Contain(cursor_pos);
	//if (nearest_point_id != -1 && nearest_point_dist < point_select_threshold)
	//{
	//	object_under_cursor = false;
	//	point_under_cursor = nearest_point_id;
	//}
	//else if (obj_collide)
	//{
	//	object_under_cursor = true;
	//	point_under_cursor = -1;
	//}
	//else
	//{
	//	object_under_cursor = false;
	//	point_under_cursor = -1;
	//}
}
void TAdornment::OnMouseMove(TVec2 cursor_pos)
{

	if (state == TState::None)
	{
		Collide(cursor_pos);
	}
	else if (state == TState::PointMove)
	{
		if (point_under_cursor != -1)
		{		
			OnControlMove(point_under_cursor, control_points[point_under_cursor].pos, control_points[point_under_cursor].pos + (cursor_pos - old_cursor_pos));
		}
	}
	this->old_cursor_pos = cursor_pos;
}
void TAdornment::OnMouseDown()
{
	if (state == TState::None)
	{
		if (point_under_cursor != -1)
		{
			state = TState::PointMove;
		}
	}
}
void TAdornment::OnMouseUp()
{
	if (state == TState::None)
	{
	}
	else if (state == TState::PointMove)
	{
		state = TState::None;
	}
}

void TAdornment::OnMouseMove(TMouseEventArgs e, TVec2 wolrd_cursor_location)
{
	//for (TVisualControl& v : controls)
		OnMouseMove(wolrd_cursor_location);
}
void TAdornment::OnMouseDown(TMouseEventArgs e, TVec2 wolrd_cursor_location)
{
	//for (TVisualControl& v : controls)
		OnMouseDown();
}
void TAdornment::OnMouseUp(TMouseEventArgs e, TVec2 wolrd_cursor_location)
{
	//for (TVisualControl& v : controls)
		OnMouseUp();
}

void TAdornment::Render(TDrawingHelper* drawing_helper)
{
	
	for (TControlPoint& v : control_points)
	{
		switch (v.type)
		{
		case TControlType::Pivot:
			drawing_helper->DrawPoint(v.pos);
			break;
		case TControlType::Resize:
			drawing_helper->DrawPoint(v.pos);
			break;
		case TControlType::Rotate:
			drawing_helper->DrawPoint(v.pos);
			break;
		default:
			break;
		}
	}
	if (point_under_cursor != -1)
	{
		drawing_helper->SetSelectedPointColor();
		drawing_helper->DrawPoint(control_points[point_under_cursor].pos);
		drawing_helper->UnsetColor();
	}
}

void TBoundaryBoxAdornment::OnControlMove(int changed_control, TVec2 old_pos, TVec2 new_pos)
{
	TControlPoint p = control_points[changed_control];
	TVec2 diff = new_pos - old_pos;
	switch (control_points[changed_control].type)
	{
	case TControlType::Pivot:
		boundary.SetPos(new_pos);
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
		TVec2 xb = (new_pos - rot_pos).GetNormalized();
		boundary.SetOrient(TMatrix2(xb, xb.Cross()));
		UpdatePointsPos();
	}
		break;
	default:
		break;
	}
}

void TBoundaryBoxAdornment::Render(TDrawingHelper* drawing_helper)
{
	TAdornment::Render(drawing_helper);

	//if (object_under_cursor)
	//	drawing_helper->SetSelectedBoundaryColor();
	drawing_helper->DrawBoundary(boundary);
	//if (object_under_cursor)
	//	drawing_helper->UnsetColor();
}

bool TBoundaryBoxAdornment::IsCollide(TVec2 point)
{
	return boundary.Contain(point);
}

void TBoundaryBoxAdornment::UpdatePointsPos()
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

			p.pos = or*p.pos + pos;
		}
			break;
		case TControlType::Rotate:
		{
			TAABB<float, 2> aabb = boundary.GetLocalAABB();
			TMatrix<float, 2> or = boundary.GetOrient();
			TVec2 pos = boundary.GetPos();
			if (p.x_resize == -1)
				p.pos[0] = aabb[0][0] - 0.2;
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

TBoundaryBoxAdornment::TBoundaryBoxAdornment()
{

	boundary = TOBB<float, 2>(TVec2(0, 0), TMatrix2::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(4, 2)));

	control_points = InitControlPointsByBoundary(boundary);

	UpdatePointsPos();
}

TBoundaryBoxAdornment::TBoundaryBoxAdornment(TOBB<float, 2> boundary)
{
	this->boundary = boundary;

	control_points = InitControlPointsByBoundary(boundary);

	UpdatePointsPos();
}

TBoundaryBoxAdornment::TBoundaryBoxAdornment(TVec2 pos)
{

	boundary = TOBB<float, 2>(pos, TMatrix2::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(4, 2)));

	control_points = InitControlPointsByBoundary(boundary);

	UpdatePointsPos();
}