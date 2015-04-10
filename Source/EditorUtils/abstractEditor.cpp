#include "abstractEditor.h"

void OnMouseMove(TCallbackData* data, TMouseEventArgs* e)
{
	TAbstractEditor* ed = (TAbstractEditor*)data->GetUserData();
	if (ed->current_local_editor != nullptr)
	{
	}
	else
	{
		auto tool = ed->GetActiveTool();
		if (tool != nullptr)
			tool->OnMouseMove(*e);
	}
}

void OnMouseDown(TCallbackData* data, TMouseEventArgs* e)
{
	TAbstractEditor* ed = (TAbstractEditor*)data->GetUserData();
	if (ed->current_local_editor != nullptr)
	{
	}
	else
	{
		auto tool = ed->GetActiveTool();
		if (tool != nullptr)
			tool->OnMouseDown(*e);
	}
}

void OnMouseUp(TCallbackData* data, TMouseEventArgs* e)
{
	TAbstractEditor* ed = (TAbstractEditor*)data->GetUserData();
	if (ed->current_local_editor != nullptr)
	{
	}
	else
	{
		auto tool = ed->GetActiveTool();
		if (tool != nullptr)
			tool->OnMouseUp(*e);
	}
}

void TAbstractEditor::InitializeControls(IBaluWorld* world)
{
	this->world = world;
	world->AddOnMouseMove(CallbackWithData<MouseCallback>(OnMouseMove, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
	world->AddOnMouseDown(CallbackWithData<MouseCallback>(OnMouseDown, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
	world->AddOnMouseUp(CallbackWithData<MouseCallback>(OnMouseUp, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
}

void TAbstractEditor::DeinitializeControls()
{
	world->RemoveOnMouseMove(CallbackWithData<MouseCallback>(OnMouseMove, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
	world->RemoveOnMouseDown(CallbackWithData<MouseCallback>(OnMouseDown, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
	world->RemoveOnMouseUp(CallbackWithData<MouseCallback>(OnMouseUp, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
}

void TAbstractEditor::SetActiveTool(IEditorTool* tool)
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->SetActiveTool(tool);
	}
	else
	{
		if (tool == active_tool)
			return;
		if (active_tool != nullptr)
			active_tool->Deactivate();
		active_tool = tool;
		if (tool != nullptr)
			tool->Activate();
	}
}