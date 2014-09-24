#include "physBodyEditor.h"

#include "../baluEditorDefs.h"
#include "physBodyEditorTools.h"

TPhysBodyEditor::TPhysBodyEditor() :tools_registry(this)
{
	active_tool = nullptr;
}

void TPhysBodyEditor::Initialize(TBaluPhysBodyDef* obj)
{
	for (const std::unique_ptr<TBaluShapeDef>& v : obj->fixtures)
	{
		if (dynamic_cast<TBaluPolygonShapeDef*>(v.get()) != nullptr)
		{
			auto b = v->GetOBB();
			auto new_box = new TPolygonShapeAdornment(b.GetPos());
			boundaries.emplace_back(std::unique_ptr<TPolygonShapeAdornment>(new_box));
		}
	}
}

void TPhysBodyEditor::SetActiveTool(TEditorTool* use_tool)
{
	active_tool = use_tool;
}

void TPhysBodyEditor::UnsetAcitveTool()
{
	active_tool = nullptr;
}

bool TPhysBodyEditor::CanSetSelectedAsWork()
{
	return true;
}

void TPhysBodyEditor::SetSelectedAsWork()
{

}

bool TPhysBodyEditor::CanEndSelectedAsWork()
{
	return true;
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

void TPhysBodyEditor::Initialize(TWorldObjectDef* obj)
{

}

void TPhysBodyEditor::AddBoundary(TBoundaryBoxAdornment* box)
{
	boundaries.push_back(std::unique_ptr<TBoundaryBoxAdornment>(box));
}
void TPhysBodyEditor::AddJoint(TJointAdornment* joint)
{
	joints.push_back(std::unique_ptr<TJointAdornment>(joint));
}

void TPhysBodyEditor::Render(TDrawingHelper* drawing_helper)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : boundaries)
	{
		box->Render(drawing_helper);
	}
}

const std::vector<TToolWithDescription>& TPhysBodyEditor::GetAvailableTools()
{
	return tools_registry.GetTools();
}