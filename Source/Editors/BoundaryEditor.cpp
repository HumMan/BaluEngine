#include "BoundaryEditor.h"

void TBoundaryBoxAdornment::OnControlMove(int changed_control, TVec2 new_pos)
{
	TBoundaryBoxControlPoint p = controls[changed_control];
	TVec2 diff = new_pos - p.GetPosition();
	auto old_boundary = boundary;
	switch (controls[changed_control].type)
	{
	case TControlType::Pivot:
		boundary.SetPos(new_pos);
		UpdatePointsPos();
		break;
	case TControlType::Resize:
	{
		TAABB<float, 2> source_b = start_edit_boundary.GetLocalAABB();
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
		assert(false);
		break;
	}
	OnBoxChange(old_boundary, boundary);
}

void TBoundaryBoxAdornment::Render(TDrawingHelper* drawing_helper)
{
	if (box_under_cursor)
	{
		TEditorObjectControls::Render(drawing_helper);
		drawing_helper->SetSelectedBoundaryColor();
		drawing_helper->DrawBoundary(boundary,false);
		drawing_helper->UnsetColor();
	}
}

bool TBoundaryBoxAdornment::IsCollide(TVec2 point)
{
	TVec2 cursor_pos = point;
	const float point_select_threshold = 0.3;
	float nearest_point_dist = 0;
	float nearest_point_id = GetNearestControl(point, nearest_point_dist);
	bool obj_collide = boundary.Contain(cursor_pos);
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
	for (TBoundaryBoxControlPoint& p : controls)
	{
		switch (p.type)
		{
		case TControlType::Pivot:
			p.SetPosition(boundary.GetPos());
			break;
		case TControlType::Resize:
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
		case TControlType::Rotate:
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

std::vector<TBoundaryBoxControlPoint> InitControlPointsByBoundary(TOBB<float, 2> boundary)
{
	std::vector<TBoundaryBoxControlPoint> control_points;
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

TBoundaryBoxAdornment::TBoundaryBoxAdornment()
{

	boundary = TOBB<float, 2>(TVec2(0, 0), TMatrix2::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(4, 2)));

	controls = InitControlPointsByBoundary(boundary);
	for (TBoundaryBoxControlPoint& p : controls)
		AddControl(&p);

	UpdatePointsPos();
}
TBoundaryBoxAdornment::TBoundaryBoxAdornment(TOBB<float, 2> boundary)
{
	this->boundary = boundary;

	controls = InitControlPointsByBoundary(boundary);
	for (TBoundaryBoxControlPoint& p : controls)
		AddControl(&p);

	UpdatePointsPos();
}
TBoundaryBoxAdornment::TBoundaryBoxAdornment(TVec2 pos)
{

	boundary = TOBB<float, 2>(pos, TMatrix2::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(4, 2)));

	controls = InitControlPointsByBoundary(boundary);
	for (TBoundaryBoxControlPoint& p : controls)
		AddControl(&p);

	UpdatePointsPos();
}

bool TBoundaryBoxAdornment::OnStartBoxMove(int changed_box_control, TVec2 new_pos)
{
	return true;
}
void TBoundaryBoxAdornment::OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
{

}

void TBoundaryBoxAdornment::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	TEditorObjectControls::OnMouseDown(e, world_cursor_location);
}
void TBoundaryBoxAdornment::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	box_under_cursor = boundary.Contain(world_cursor_location);
	TEditorObjectControls::OnMouseMove(e, world_cursor_location);
	
}
void TBoundaryBoxAdornment::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	TEditorObjectControls::OnMouseUp(e, world_cursor_location);
}
bool TBoundaryBoxAdornment::IsCursorCaptured()
{
	return TEditorObjectControls::IsCursorCaptured();
}


void TBoundaryBoxesModifyTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : boundary_box_scene->boundaries)
	{
		box->IsCollide(world_cursor_location);
		if (box->IsCollideWithAdornment(world_cursor_location))
			box->OnMouseDown(e, world_cursor_location);
	}
}

void TBoundaryBoxesModifyTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : boundary_box_scene->boundaries)
	{
		//box->IsCollide(world_cursor_location);
		box->OnMouseMove(e, world_cursor_location);
	}
}
void TBoundaryBoxesModifyTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : boundary_box_scene->boundaries)
	{
		//box->IsCollide(world_cursor_location);
		box->OnMouseUp(e, world_cursor_location);
	}
}

void TBoundaryBoxesModifyTool::Render(TDrawingHelper* drawing_helper)
{
}