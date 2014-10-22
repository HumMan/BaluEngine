#include "materialEditor.h"

#include "../../baluEditorDefs.h"
#include "materialEditorTools.h"

#include "materialEditorAdornments.h"

TMaterialEditor::TMaterialEditor() :tools_registry(&scene)
{
	active_tool = nullptr;
}

void TMaterialEditor::Initialize(TBaluMaterialDef* obj)
{
	scene.Initialize(obj);
}

void TMaterialEditor::UnsetAcitveTool()
{
	active_tool = nullptr;
}

bool TMaterialEditor::CanSetSelectedAsWork()
{
	return true;
}

void TMaterialEditor::SetSelectedAsWork()
{

}

bool TMaterialEditor::CanEndSelectedAsWork()
{
	return true;
}
void TMaterialEditor::EndSelectedAsWork()
{

}

void TMaterialEditor::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool!=nullptr)
		active_tool->OnMouseDown(e, world_cursor_location);
}

void TMaterialEditor::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool != nullptr)
		active_tool->OnMouseMove(e, world_cursor_location);
}

void TMaterialEditor::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool != nullptr)
		active_tool->OnMouseUp(e, world_cursor_location);
}

void TMaterialEditor::Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos)
{
	this->editor_global_pos = editor_global_pos;
	Initialize(dynamic_cast<TBaluMaterialDef*>(obj));
}

void TMaterialEditor::Render(TDrawingHelper* drawing_helper)
{
	TBaluMaterialDef background_mat;
	TOBB<float, 2> backgroud_boundary(TVec2(0,0),TMatrix2::GetIdentity(),TAABB<float,2>(TVec2(0),TVec2(10)));
	background_mat.image_path = "Textures/checker.png";
	drawing_helper->ActivateMaterial(&background_mat);
	drawing_helper->DrawBoundary(backgroud_boundary, true);
	drawing_helper->DeactivateMaterial(&background_mat);

	drawing_helper->ActivateMaterial(scene.material);
	drawing_helper->DrawBoundary(scene.preview_boundary, true);
	drawing_helper->DeactivateMaterial(scene.material);
}

const std::vector<TToolWithDescription>& TMaterialEditor::GetAvailableTools()
{
	return tools_registry.GetTools();
}

void TMaterialEditor::SetActiveTool(TEditorTool* tool)
{
	active_tool = tool;
}