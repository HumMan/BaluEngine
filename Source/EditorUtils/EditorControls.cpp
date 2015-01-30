#include "EditorControls.h"


TEditorObjectControls::TEditorObjectControls()
{
	control_under_cursor = -1;
	state = TState::None; 
}

int TEditorObjectControls::GetNearestControl(TVec2 cursor_pos, float& distance)const
{
	const float point_select_threshold = 0.3;
	float nearest_point_dist = 0;
	float nearest_point_id = -1;
	for (int i = 0; i < control_points.size(); i++)
	{
		float dist = control_points[i]->GetDistance(cursor_pos);
		if (dist < nearest_point_dist || nearest_point_id == -1)
		{
			nearest_point_id = i;
			nearest_point_dist = dist;
		}
	}
	if (nearest_point_id != -1)
	{
		return nearest_point_id;
	}
	return -1;
}

int TEditorObjectControls::AddControl(TEditorControl* control)
{
	control_points.push_back(control);
	return control_points.size() - 1;
}

void TEditorObjectControls::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (state == TState::None)
	{
		if (control_under_cursor != -1)
		{
			state = TState::ControlMove;
			start_move_control_pos = control_points[control_under_cursor]->GetPosition();
			start_move_cursor_pos = world_cursor_location;
		}
	}
}
void TEditorObjectControls::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (state == TState::None)
	{
		float dist=0;
		control_under_cursor = GetNearestControl(world_cursor_location, dist);
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
			TVec2 new_pos = start_move_control_pos + (world_cursor_location - start_move_control_pos);
			//control_points[control_under_cursor]->SetPosition(new_pos);
			OnControlMove(control_under_cursor, new_pos);
		}
	}
}
void TEditorObjectControls::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (state == TState::None)
	{
	}
	else if (state == TState::ControlMove)
	{
		state = TState::None;
	}
}
bool TEditorObjectControls::IsCursorCaptured()
{
	return state != TState::None;
}

void TEditorObjectControls::OnControlMove(int changed_control, TVec2 new_pos)
{

}

//void TEditorObjectControls::Render(TDrawingHelper* drawing_helper)
//{
//	for (TEditorControl* v : control_points)
//	{
//		bool need_hightlight = control_under_cursor != -1 && v == control_points[control_under_cursor];
//		
//		if (need_hightlight)
//			drawing_helper->SetSelectedPointColor();
//		v->Render(drawing_helper);
//		if (need_hightlight)
//			drawing_helper->UnsetColor();
//	}
//}