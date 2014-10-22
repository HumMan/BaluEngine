#include "physBodyEditor.h"

#include "../../baluEditorDefs.h"
#include "physBodyEditorTools.h"

#include "physBodyEditorAdornments.h"

TPhysBodyEditor::TPhysBodyEditor() :tools_registry(&scene)
{
	active_tool = nullptr;
}

void TPhysBodyEditor::Initialize(TBaluPhysBodyDef* obj)
{
	scene.Initialize(obj);
	for (const std::unique_ptr<TBaluShapeDef>& v : obj->fixtures)
	{
		if (dynamic_cast<TBaluPolygonShapeDef*>(v.get()) != nullptr)
		{
			auto new_box = new TPolygonShapeAdornment(dynamic_cast<TBaluPolygonShapeDef*>(v.get()));
			scene.boundaries.emplace_back(std::unique_ptr<TPolygonShapeAdornment>(new_box));
		}
		if (dynamic_cast<TBaluCircleShapeDef*>(v.get()) != nullptr)
		{
			auto new_box = new TCircleShapeAdornment(dynamic_cast<TBaluCircleShapeDef*>(v.get()));
			scene.boundaries.emplace_back(std::unique_ptr<TCircleShapeAdornment>(new_box));
		}
	}
}

void TPhysBodyEditor::UnsetAcitveTool()
{
	active_tool = nullptr;
}

bool TPhysBodyEditor::CanSetSelectedAsWork()
{
	return scene.boundary_under_cursor != nullptr;
}

void TPhysBodyEditor::SetSelectedAsWork()
{

}

bool TPhysBodyEditor::CanEndSelectedAsWork()
{
	return parent_editors.size()>0;
}
void TPhysBodyEditor::EndSelectedAsWork()
{

}

void TPhysBodyEditor::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool!=nullptr)
		active_tool->OnMouseDown(e, world_cursor_location);
}

void TPhysBodyEditor::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool != nullptr)
		active_tool->OnMouseMove(e, world_cursor_location);
}

void TPhysBodyEditor::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool != nullptr)
		active_tool->OnMouseUp(e, world_cursor_location);
}

void TPhysBodyEditor::Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos)
{
	this->editor_global_pos = editor_global_pos;
	Initialize(dynamic_cast<TBaluPhysBodyDef*>(obj));
}

void TPhysBodyEditor::AddBoundary(TBoundaryBoxAdornment* box)
{
	scene.boundaries.push_back(std::unique_ptr<TBoundaryBoxAdornment>(box));
}
void TPhysBodyEditor::AddJoint(TJointAdornment* joint)
{
	scene.joints.push_back(std::unique_ptr<TJointAdornment>(joint));
}

void TPhysBodyEditor::Render(TDrawingHelper* drawing_helper)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : scene.boundaries)
	{
		box->Render(drawing_helper);
	}
}

const std::vector<TToolWithDescription>& TPhysBodyEditor::GetAvailableTools()
{
	return tools_registry.GetTools();
}

void TPhysBodyEditor::SetActiveTool(TEditorTool* tool)
{
	active_tool = tool;
}