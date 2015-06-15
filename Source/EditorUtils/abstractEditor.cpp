#include "abstractEditor.h"

void OnMouseMove(void* user_data, TMouseEventArgs* e)
{
	TAbstractEditor* ed = (TAbstractEditor*)user_data;
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

void OnMouseDown(void* user_data, TMouseEventArgs* e)
{
	TAbstractEditor* ed = (TAbstractEditor*)user_data;
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

void OnMouseUp(void* user_data, TMouseEventArgs* e)
{
	TAbstractEditor* ed = (TAbstractEditor*)user_data;
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
	//world->AddOnMouseMove(TSpecialCallback<MouseCallback>(OnMouseMove, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
	//world->AddOnMouseDown(TSpecialCallback<MouseCallback>(OnMouseDown, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
	//world->AddOnMouseUp(TSpecialCallback<MouseCallback>(OnMouseUp, &world->GetCallbacksActiveType(), this, TCallbacksActiveType::EDITOR));
}

void TAbstractEditor::DeinitializeControls()
{
	//world->RemoveOnMouseMove(0);
	//world->RemoveOnMouseDown(0);
	//world->RemoveOnMouseUp(0);
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