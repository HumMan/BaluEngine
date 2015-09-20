#include "abstractEditor.h"


void TAbstractEditor::OnMouseMove(TMouseEventArgs e)
{
	if (current_local_editor != nullptr)
	{
	}
	else
	{
		auto tool = GetActiveTool();
		if (tool != nullptr)
			tool->OnMouseMove(e);
	}
}

void TAbstractEditor::OnMouseDown(TMouseEventArgs e)
{
	if (current_local_editor != nullptr)
	{
	}
	else
	{
		auto tool = GetActiveTool();
		if (tool != nullptr)
			tool->OnMouseDown(e);
	}
}

void TAbstractEditor::OnMouseUp(TMouseEventArgs e)
{
	if (current_local_editor != nullptr)
	{
	}
	else
	{
		auto tool = GetActiveTool();
		if (tool != nullptr)
			tool->OnMouseUp(e);
	}
}

void TAbstractEditor::InitializeControls(IBaluWorldInstance* world)
{
	this->world = world;
	world->AddMouseEventListener(this);
}

void TAbstractEditor::DeinitializeControls()
{
	world->RemoveMouseEventListener(this);
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