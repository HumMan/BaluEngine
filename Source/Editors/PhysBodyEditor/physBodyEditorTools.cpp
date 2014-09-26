#include "physBodyEditorTools.h"

#include "physBodyEditor.h"

#include "physBodyEditorAdornments.h"

class TCreateFixtureTool : public TPhysEditorTools
{

};

class TCreatePolygonTool : public TCreateFixtureTool
{
protected:
	TPhysBodyEditorScene* phys_body_editor_scene;
public:
	TCreatePolygonTool(TPhysBodyEditorScene* phys_body_editor_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};

class TCreateCircleTool : public TCreatePolygonTool
{

public:
	TCreateCircleTool(TPhysBodyEditorScene* phys_body_editor_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
};

class TCreateJointTool :public  TPhysEditorTools
{

};

class TCreateDistanceJointTool :public TCreateJointTool
{
public:
	TCreateDistanceJointTool(TPhysBodyEditorScene* phys_body_editor_scene);
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
	TModifyTool(TPhysBodyEditorScene* phys_body_editor_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};


TCreatePolygonTool::TCreatePolygonTool(TPhysBodyEditorScene* phys_body_editor_scene)
{
	this->phys_body_editor_scene = phys_body_editor_scene;
}

void TCreatePolygonTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	auto new_shape = new TBaluPolygonShapeDef();
	new_shape->pos = world_cursor_location;
	new_shape->b2shape.SetAsBox(1, 1);
	phys_body_editor_scene->phys_body->fixtures.push_back(std::unique_ptr<TBaluShapeDef>(new_shape));
	
	auto new_box = new TPolygonShapeAdornment(new_shape);
	phys_body_editor_scene->boundaries.push_back(std::unique_ptr<TBoundaryBoxAdornment>(new_box));
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


TCreateCircleTool::TCreateCircleTool(TPhysBodyEditorScene* phys_body_editor_scene) :TCreatePolygonTool(phys_body_editor_scene)
{
}

void TCreateCircleTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	auto new_shape = new TBaluCircleShapeDef();
	new_shape->pos = world_cursor_location;
	new_shape->b2shape.m_radius = 1;
	phys_body_editor_scene->phys_body->fixtures.push_back(std::unique_ptr<TBaluShapeDef>(new_shape));

	auto new_box = new TCircleShapeAdornment(new_shape);
	phys_body_editor_scene->boundaries.push_back(std::unique_ptr<TBoundaryBoxAdornment>(new_box));
}

TPhysBodyEditorToolsRegistry::TPhysBodyEditorToolsRegistry(TPhysBodyEditorScene* phys_body_editor_scene)
{
	this->phys_body_editor_scene = phys_body_editor_scene;
	tools.emplace_back(new TCreatePolygonTool(phys_body_editor_scene), "Polygon");
	tools.emplace_back(new TCreateCircleTool(phys_body_editor_scene), "Circle");
	tools.emplace_back(new TCreateDistanceJointTool(phys_body_editor_scene), "DistanceJoint");
	tools.emplace_back(new TModifyTool(phys_body_editor_scene), "Modify");
}

TPhysBodyEditorToolsRegistry::TPhysBodyEditorToolsRegistry(TPhysBodyEditorToolsRegistry&& o)
{
	tools = std::move(o.tools);
	phys_body_editor_scene = std::move(o.phys_body_editor_scene);
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

TCreateDistanceJointTool::TCreateDistanceJointTool(TPhysBodyEditorScene* phys_body_editor_scene)
{
	this->phys_body_editor_scene = phys_body_editor_scene;
}

void TCreateDistanceJointTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	//auto new_box = new TPolygonShapeAdornment(world_cursor_location);
	//phys_body_editor->AddBoundary(new_box);
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

TModifyTool::TModifyTool(TPhysBodyEditorScene* phys_body_editor_scene)
{
	this->phys_body_editor_scene = phys_body_editor_scene;
	boundary_under_cursor = nullptr;
}

void TModifyTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : phys_body_editor_scene->boundaries)
	{
		box->IsCollide(world_cursor_location);
		box->OnMouseDown(e, world_cursor_location);
	}
}

void TModifyTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : phys_body_editor_scene->boundaries)
	{
		//box->IsCollide(world_cursor_location);
		box->OnMouseMove(e, world_cursor_location);
	}
}
void TModifyTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	for (const std::unique_ptr<TBoundaryBoxAdornment>& box : phys_body_editor_scene->boundaries)
	{
		//box->IsCollide(world_cursor_location);
		box->OnMouseUp(e, world_cursor_location);
	}
}

void TModifyTool::Render(TDrawingHelper* drawing_helper)
{
}