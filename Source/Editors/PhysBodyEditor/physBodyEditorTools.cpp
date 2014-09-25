#include "physBodyEditorTools.h"

#include "physBodyEditor.h"


class TCreateFixtureTool : public TPhysEditorTools
{

};

class TCreatePolygonTool : public TCreateFixtureTool
{
protected:
	TPhysBodyEditor* phys_body_editor;
public:
	TCreatePolygonTool(TPhysBodyEditor* phys_body_editor);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};

class TCreateCircleTool : public TCreatePolygonTool
{

public:
	TCreateCircleTool(TPhysBodyEditor* phys_body_editor);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
};

class TCreateJointTool :public  TPhysEditorTools
{

};

class TCreateDistanceJointTool :public TCreateJointTool
{
public:
	TCreateDistanceJointTool(TPhysBodyEditor* phys_body_editor);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};

class TCreatePrismaticJointTool :public TCreateJointTool
{

};

class TModifyTool : public TPhysEditorTools
{
	TBoundaryBoxAdornment* boundary_under_cursor;
public:
	TModifyTool(TPhysBodyEditor* phys_body_editor);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};


TCreatePolygonTool::TCreatePolygonTool(TPhysBodyEditor* phys_body_editor)
{
	this->phys_body_editor = phys_body_editor;
}

void TCreatePolygonTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	auto new_box = new TPolygonShapeAdornment(world_cursor_location);
	phys_body_editor->AddBoundary(new_box);
}

void TCreatePolygonTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreatePolygonTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreatePolygonTool::Render(TDrawingHelper* drawing_helper)
{

}


TCreateCircleTool::TCreateCircleTool(TPhysBodyEditor* phys_body_editor) :TCreatePolygonTool(phys_body_editor)
{
}

void TCreateCircleTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	auto new_box = new TPolygonShapeAdornment(world_cursor_location);
	phys_body_editor->AddBoundary(new_box);
}


TPolygonShapeAdornment::TPolygonShapeAdornment(TVec2 pos) :TBoundaryBoxAdornment(pos)
{
}

void TPolygonShapeAdornment::OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
{

}

void TPolygonShapeAdornment::Render(TDrawingHelper* drawing_helper)
{
	TBoundaryBoxAdornment::Render(drawing_helper);
}

TPhysBodyEditorToolsRegistry::TPhysBodyEditorToolsRegistry(TPhysBodyEditor* phys_body_editor)
{
	this->phys_body_editor = phys_body_editor;
	tools.emplace_back(new TCreatePolygonTool(phys_body_editor), "Polygon");
	tools.emplace_back(new TCreateCircleTool(phys_body_editor), "Circle");
	tools.emplace_back(new TCreateDistanceJointTool(phys_body_editor), "DistanceJoint");
	tools.emplace_back(new TModifyTool(phys_body_editor), "Modify");
}

const std::vector<TToolWithDescription>& TPhysBodyEditorToolsRegistry::GetTools()
{
	return tools;
}

TPhysBodyEditorToolsRegistry::~TPhysBodyEditorToolsRegistry()
{
}

TToolWithDescription::~TToolWithDescription()
{

}

TCreateDistanceJointTool::TCreateDistanceJointTool(TPhysBodyEditor* phys_body_editor)
{
	this->phys_body_editor = phys_body_editor;
}

void TCreateDistanceJointTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	auto new_box = new TPolygonShapeAdornment(world_cursor_location);
	phys_body_editor->AddBoundary(new_box);
}

void TCreateDistanceJointTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateDistanceJointTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateDistanceJointTool::Render(TDrawingHelper* drawing_helper)
{

}

TModifyTool::TModifyTool(TPhysBodyEditor* phys_body_editor)
{
	this->phys_body_editor = phys_body_editor;
	boundary_under_cursor = nullptr;
}

void TModifyTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : phys_body_editor->boundaries)
	{
		box->IsCollide(world_cursor_location);
		box->OnMouseDown(e, world_cursor_location);
	}
}

void TModifyTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : phys_body_editor->boundaries)
	{
		//box->IsCollide(world_cursor_location);
		box->OnMouseMove(e, world_cursor_location);
	}
}
void TModifyTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : phys_body_editor->boundaries)
	{
		//box->IsCollide(world_cursor_location);
		box->OnMouseUp(e, world_cursor_location);
	}
}
void TModifyTool::Render(TDrawingHelper* drawing_helper)
{
}