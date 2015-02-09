
#include "sceneEditorTools.h"

#include "sceneEditorScene.h"

#include "sceneEditorAdornments.h"

#include "../DrawingHelper.h"

class TCreateClassInstanceTool : public IEditorTool
{
protected:
	TSceneEditorScene* scene_editor_scene;
	//TBaluClass* active_tool_class;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::Class;
	}
	//void SetSelectedObject(TWorldObjectDef* obj)
	//{
	//	active_tool_class = dynamic_cast<TBaluClass*>(obj);
	//}
	TCreateClassInstanceTool(TSceneEditorScene* scene_editor_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
	void CancelOperation()
	{

	}
};

TCreateClassInstanceTool::TCreateClassInstanceTool(TSceneEditorScene* scene_editor_scene)
{
	this->scene_editor_scene = scene_editor_scene;
	//active_tool_class = nullptr;
}

void TCreateClassInstanceTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	//if (active_tool_class != nullptr)
	{
		IBaluClass* pl;
		scene_editor_scene->source_scene_instance->GetWorld()->GetSource()->TryFindClass("player", pl);

		auto transform = TBaluTransform(scene_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location),TRot(0));
		auto world = scene_editor_scene->source_scene_instance->CreateInstance(pl, transform);
		auto new_class_instance = scene_editor_scene->source_scene_instance->CreateInstance(pl, transform);

		//new_class_instance->instance_transform.position = world_cursor_location;
		//new_class_instance->instance_transform.angle.Set(0);
		//new_class_instance->instance_class = active_tool_class;
		//scene_editor_scene->balu_scene->instances.push_back(std::unique_ptr<TBaluInstanceDef>(new_class_instance));

		//auto new_box = new TClassInstanceAdornment(new_class_instance);
		scene_editor_scene->boundary_box.SetBoundary(TOBB2(transform.position, transform.GetOrientation(), TAABB2(TVec2(0, 0), TVec2(1, 1))));
		//scene_editor_scene->boundaries.push_back(std::unique_ptr<TClassInstanceAdornment>(new_box));
	}
}

void TCreateClassInstanceTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateClassInstanceTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateClassInstanceTool::Render(TDrawingHelper* drawing_helper)
{

}

TSceneEditorToolsRegistry::TSceneEditorToolsRegistry(TSceneEditorScene* scene)
{
	this->scene = scene;
	tools.emplace_back(new TCreateClassInstanceTool(scene), "Instance");
	//tools.emplace_back(new TBoundaryBoxesModifyTool(scene), "Modify");
}
TSceneEditorToolsRegistry::TSceneEditorToolsRegistry(TSceneEditorToolsRegistry&& o)
{
	tools = std::move(o.tools);
	scene = std::move(o.scene);
}
const std::vector<TToolWithDescription>& TSceneEditorToolsRegistry::GetTools()
{
	return tools;
}
TSceneEditorToolsRegistry::~TSceneEditorToolsRegistry()
{

}