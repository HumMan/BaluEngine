#include "abstractEditor.h"

void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location, void* user_data)
{
	TAbstractEditor* ed = (TAbstractEditor*)user_data;
	if (ed->current_local_editor != nullptr)
	{
	}
	else
	{
		auto tool = ed->GetActiveTool();
		if (tool != nullptr)
			tool->OnMouseMove(e, world_cursor_location);
	}
}

void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location, void* user_data)
{
	TAbstractEditor* ed = (TAbstractEditor*)user_data;
	if (ed->current_local_editor != nullptr)
	{
	}
	else
	{
		auto tool = ed->GetActiveTool();
		if (tool != nullptr)
			tool->OnMouseDown(e, world_cursor_location);
	}
}

void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location, void* user_data)
{
	TAbstractEditor* ed = (TAbstractEditor*)user_data;
	if (ed->current_local_editor != nullptr)
	{
	}
	else
	{
		auto tool = ed->GetActiveTool();
		if (tool != nullptr)
			tool->OnMouseUp(e, world_cursor_location);
	}
}

void TAbstractEditor::InitializeControls(IBaluWorld* world)
{
	world->OnMouseMove(OnMouseMove, this);
	world->OnMouseDown(OnMouseDown, this);
	world->OnMouseUp(OnMouseUp, this);
}

void TAbstractEditor::DeinitializeControls()
{

}