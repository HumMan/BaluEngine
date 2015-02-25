
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

		auto new_source_scene_instance = scene_editor_scene->source_scene->CreateInstance(pl);
		new_source_scene_instance->SetTransform(transform);
		scene_editor_scene->selected_instance_source = new_source_scene_instance;

		auto new_class_instance = scene_editor_scene->source_scene_instance->CreateInstance(pl, transform, TVec2(1,1));
		scene_editor_scene->selected_instance = new_class_instance;
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

class TModifyClassInstanceTool : public IEditorTool, public TBoundaryBoxChangeListener
{
protected:
	TSceneEditorScene* scene_editor_scene;
	//TBaluClass* active_tool_class;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::None;
	}
	//void SetSelectedObject(TWorldObjectDef* obj)
	//{
	//	active_tool_class = dynamic_cast<TBaluClass*>(obj);
	//}
	TModifyClassInstanceTool(TSceneEditorScene* scene_editor_scene)
	{
		this->scene_editor_scene = scene_editor_scene;
	}

	void BoxResize(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
	{

	}
	void BoxMove(TVec2 old_pos, TVec2 new_pos)
	{
		auto trans = scene_editor_scene->selected_instance->GetTransform();
		trans.position = new_pos;
		scene_editor_scene->selected_instance->SetTransform(trans);
	}
	void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
	{
		auto trans = scene_editor_scene->selected_instance->GetTransform();
		trans.angle = TRot(new_box);
		scene_editor_scene->selected_instance->SetTransform(trans);
	}

	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
	{
		if (scene_editor_scene->boundary_box.enable)
		{
			scene_editor_scene->boundary_box.OnMouseDown(e, scene_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
		}
		if (!scene_editor_scene->boundary_box.IsCursorCaptured())
		{
			if (scene_editor_scene->hightlighted_instance != nullptr)
			{
				scene_editor_scene->selected_instance = scene_editor_scene->hightlighted_instance;
				auto transform = scene_editor_scene->selected_instance->GetTransform();
				scene_editor_scene->boundary_box.OnChange = this;
				scene_editor_scene->boundary_box.enable = true;
				scene_editor_scene->boundary_box.SetBoundary(TOBB2(transform.position, transform.GetOrientation(), scene_editor_scene->selected_instance->GetClass()->GetAABB()));
			}
			else
			{
				scene_editor_scene->boundary_box.enable = false;
				scene_editor_scene->selected_instance = nullptr;
			}
		}
	}
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
	{
		if (scene_editor_scene->boundary_box.enable)
		{
			scene_editor_scene->boundary_box.OnMouseMove(e, scene_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
		}
		if (!scene_editor_scene->boundary_box.IsCursorCaptured())
		{
			world_cursor_location = scene_editor_scene->drawing_helper->FromScreenPixelsToScene(TVec2i(world_cursor_location[0], world_cursor_location[1]));
			IBaluInstance* instance_collision(nullptr);
			if (scene_editor_scene->source_scene_instance->PointCollide(world_cursor_location, instance_collision))
			{
				auto transform = instance_collision->GetTransform();
				//scene_editor_scene->boundary_box.SetBoundary(TOBB2(transform.position, transform.GetOrientation(), TAABB2(TVec2(0, 0), TVec2(1, 1))));
				auto box = instance_collision->GetClass()->GetAABB();

				scene_editor_scene->boundary_box_contour->SetEnable(true);
				scene_editor_scene->boundary_box_contour->SetBox(TOBB2(transform.position, transform.GetOrientation(), box));
				scene_editor_scene->hightlighted_instance = instance_collision;
			}
			else
			{
				scene_editor_scene->boundary_box_contour->SetEnable(false);
				scene_editor_scene->hightlighted_instance = nullptr;
			}
		}
		
	}
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
	{
		if (scene_editor_scene->boundary_box.enable)
		{
			scene_editor_scene->boundary_box.OnMouseUp(e, scene_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
		}
		if (!scene_editor_scene->boundary_box.IsCursorCaptured())
		{
		}
	}
	void CancelOperation()
	{

	}
};

TSceneEditorToolsRegistry::TSceneEditorToolsRegistry(TSceneEditorScene* scene)
{
	this->scene = scene;
	tools.emplace_back(new TCreateClassInstanceTool(scene), "Instance");
	tools.emplace_back(new TModifyClassInstanceTool(scene), "Modify");
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