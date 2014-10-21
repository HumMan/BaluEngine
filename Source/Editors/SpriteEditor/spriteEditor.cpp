#include "spriteEditor.h"

#include "../abstractEditor.h"

TSpriteEditor::TSpriteEditor() : tools_registry(&scene)
{
}

void TSpriteEditor::Initialize(TWorldObjectDef* obj)
{

}

bool TSpriteEditor::CanSetSelectedAsWork()
{
	return true;
}
void TSpriteEditor::SetSelectedAsWork()
{

}

bool TSpriteEditor::CanEndSelectedAsWork()
{
	return true;
}
void TSpriteEditor::EndSelectedAsWork()
{
}

const std::vector<TToolWithDescription>& TSpriteEditor::GetAvailableTools()
{
	return tools_registry.GetTools();
}
void TSpriteEditor::SetActiveTool(TEditorTool* tool)
{

}


void TSpriteEditor::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool != nullptr)
		active_tool->OnMouseDown(e, world_cursor_location);
}
void TSpriteEditor::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool != nullptr)
		active_tool->OnMouseMove(e, world_cursor_location);
}
void TSpriteEditor::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool != nullptr)
		active_tool->OnMouseUp(e, world_cursor_location);
}


void TSpriteEditor::Render(TDrawingHelper* drawing_helper)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : scene.boundaries)
	{
		box->Render(drawing_helper);
	}
}