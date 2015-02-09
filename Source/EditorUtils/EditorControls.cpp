#include "EditorControls.h"


TEditorObjectControls::TEditorObjectControls()
{
	
}



void TEditorObjectControls::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	
}
void TEditorObjectControls::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	
}
void TEditorObjectControls::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	
}
bool TEditorObjectControls::IsCursorCaptured()
{
	
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