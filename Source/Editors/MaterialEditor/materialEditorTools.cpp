#include "materialEditorTools.h"

#include "materialEditor.h"

#include "materialEditorAdornments.h"


class TMaterialModifyTool : public TMaterialEditorTools
{
	TBoundaryBoxAdornment* boundary_under_cursor;
public:
	TMaterialModifyTool(TMaterialEditorScene* material_editor_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};

TMaterialModifyTool::TMaterialModifyTool(TMaterialEditorScene* material_editor_scene)
{
	this->material_editor_scene = material_editor_scene;
	boundary_under_cursor = nullptr;
}

void TMaterialModifyTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
}

void TMaterialModifyTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
}
void TMaterialModifyTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
}

void TMaterialModifyTool::Render(TDrawingHelper* drawing_helper)
{
}


TMaterialEditorToolsRegistry::TMaterialEditorToolsRegistry(TMaterialEditorScene* material_editor_scene)
{
	this->material_editor_scene = material_editor_scene;
}

TMaterialEditorToolsRegistry::TMaterialEditorToolsRegistry(TMaterialEditorToolsRegistry&& o)
{
	tools = std::move(o.tools);
	material_editor_scene = std::move(o.material_editor_scene);
}

const std::vector<TToolWithDescription>& TMaterialEditorToolsRegistry::GetTools()
{
	return tools;
}

TMaterialEditorToolsRegistry::~TMaterialEditorToolsRegistry()
{
}