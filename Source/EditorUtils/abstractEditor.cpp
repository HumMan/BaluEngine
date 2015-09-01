#include "abstractEditor.h"

void TAbstractEditor::EmitOnSelectionChange(EngineInterface::IProperties* new_selection)
{
	for (auto& v : this->selection_listeners)
		v->OnSelectionChange(new_selection);
}

void TAbstractEditor::AddSelectionChangeListener(ISelectionChangeListener* listener)
{
	assert(std::find(this->selection_listeners.begin(), this->selection_listeners.end(), listener) == this->selection_listeners.end());
	this->selection_listeners.push_back(listener);
}

void TAbstractEditor::RemoveSelectionChangeListener(ISelectionChangeListener* listener)
{
	assert(std::find(this->selection_listeners.begin(), this->selection_listeners.end(), listener) != this->selection_listeners.end());
	this->selection_listeners.erase(std::find(this->selection_listeners.begin(), this->selection_listeners.end(), listener));
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