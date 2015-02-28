#include "abstractEditor.h"

void OnMouseMove(TCallbackData* data, TMouseEventArgs e, TVec2 world_cursor_location)
{
	TAbstractEditor* ed = (TAbstractEditor*)data->GetUserData();
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

void OnMouseDown(TCallbackData* data, TMouseEventArgs e, TVec2 world_cursor_location)
{
	TAbstractEditor* ed = (TAbstractEditor*)data->GetUserData();
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

void OnMouseUp(TCallbackData* data, TMouseEventArgs e, TVec2 world_cursor_location)
{
	TAbstractEditor* ed = (TAbstractEditor*)data->GetUserData();
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
	world->OnMouseMove(CallbackWithData<MouseUpDownCallback>(OnMouseMove, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
	world->OnMouseDown(CallbackWithData<MouseUpDownCallback>(OnMouseDown, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
	world->OnMouseUp(CallbackWithData<MouseUpDownCallback>(OnMouseUp, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
}

void TAbstractEditor::DeinitializeControls()
{

}

void TAbstractEditor::SetActiveTool(IEditorTool* tool)
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->SetActiveTool(tool);
	}
	else
		active_tool = tool;
}