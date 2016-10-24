#include "abstractEditor.h"

TAbstractEditor::TAbstractEditor(IBaluWorldInstance* world_instance)
{
	editor_global_pos = TVec2(0, 0);
	current_local_editor = nullptr;
	this->world_instance = world_instance;
	active_tool = nullptr;
	editor_global_pos = TVec2(0, 0);
	//world_instance->AddMouseEventListener(this);
}

TAbstractEditor::~TAbstractEditor()
{
	//world_instance->RemoveMouseEventListener(this);
}

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