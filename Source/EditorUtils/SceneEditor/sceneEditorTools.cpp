
#include "sceneEditorTools.h"

#include "sceneEditorScene.h"

#include "sceneEditorAdornments.h"

#include "../DrawingHelper.h"

class TCreateClassInstanceTool : public IEditorTool
{
protected:
	TSceneEditorScene* scene_editor_scene;
	IBaluClass* active_tool_class;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::Class;
	}
	void SetSelectedObject(IBaluWorldObject* obj)
	{
		active_tool_class = dynamic_cast<IBaluClass*>(obj);
	}
	TCreateClassInstanceTool(TSceneEditorScene* scene_editor_scene);
	void OnMouseDown(TMouseEventArgs e);
	void OnMouseMove(TMouseEventArgs e);
	void OnMouseUp(TMouseEventArgs e);
	void CancelOperation()
	{
	}
};

TCreateClassInstanceTool::TCreateClassInstanceTool(TSceneEditorScene* scene_editor_scene)
{
	this->scene_editor_scene = scene_editor_scene;
	active_tool_class = nullptr;
}

void TCreateClassInstanceTool::OnMouseDown(TMouseEventArgs e)
{
	if (active_tool_class != nullptr)
	{
		auto transform = TBaluTransform(scene_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location), TRot(0));

		auto new_source_scene_instance = scene_editor_scene->source_scene->CreateInstance(active_tool_class);
		new_source_scene_instance->SetTransform(transform);


		auto new_class_instance = scene_editor_scene->editor_scene_instance->CreateInstance(active_tool_class, transform, TVec2(1, 1));

		scene_editor_scene->selected_instance_source = new_source_scene_instance;
		scene_editor_scene->selected_instance = new_class_instance;

		new_class_instance->SetTag(new_source_scene_instance);

		scene_editor_scene->boundary_box.SetBoundary(TOBB2(transform.position, transform.GetOrientation(), TAABB2(TVec2(0, 0), TVec2(1, 1))));
	}
}

void TCreateClassInstanceTool::OnMouseMove(TMouseEventArgs e)
{

}
void TCreateClassInstanceTool::OnMouseUp(TMouseEventArgs e)
{

}

class TModifyClassInstanceTool : public IEditorTool, public TBoundaryBoxChangeListener
{
protected:
	TSceneEditorScene* scene_editor_scene;
	IBaluClass* active_tool_class;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::None;
	}
	void SetSelectedObject(IBaluWorldObject* obj)
	{
		active_tool_class = dynamic_cast<IBaluClass*>(obj);
	}
	TModifyClassInstanceTool(TSceneEditorScene* scene_editor_scene)
	{
		this->scene_editor_scene = scene_editor_scene;
	}

	void BoxResize(TOBB<float, 2> old_box, TOBB<float, 2> new_box, TVec2 scale)
	{
		//auto scale = new_box.GetLocalAABB().GetSize() / old_box.GetLocalAABB().GetSize();
		auto new_scale = scene_editor_scene->selected_instance->GetScale().ComponentMul(scale);
		scene_editor_scene->selected_instance->SetScale(new_scale);
		((IBaluSceneClassInstance*)(scene_editor_scene->selected_instance->GetTag()))->SetScale(new_scale);
	}
	void BoxMove(TVec2 old_pos, TVec2 new_pos)
	{
		auto trans = scene_editor_scene->selected_instance->GetTransform();
		trans.position = new_pos;
		scene_editor_scene->selected_instance->SetTransform(trans);
		((IBaluSceneClassInstance*)(scene_editor_scene->selected_instance->GetTag()))->SetTransform(trans);
	}
	void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
	{
		auto trans = scene_editor_scene->selected_instance->GetTransform();
		trans.angle = TRot(new_box);
		scene_editor_scene->selected_instance->SetTransform(trans);
		((IBaluSceneClassInstance*)(scene_editor_scene->selected_instance->GetTag()))->SetTransform(trans);
	}

	void OnMouseDown(TMouseEventArgs e)
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
				scene_editor_scene->boundary_box.OnChange = this;
				scene_editor_scene->boundary_box.enable = true;
				scene_editor_scene->boundary_box.SetBoundary(scene_editor_scene->selected_instance->GetOBB());
			}
			else
			{
				scene_editor_scene->boundary_box.enable = false;
				scene_editor_scene->selected_instance = nullptr;
			}
		}
	}
	void OnMouseMove(TMouseEventArgs e)
	{
		if (scene_editor_scene->boundary_box.enable)
		{
			scene_editor_scene->boundary_box.OnMouseMove(e, scene_editor_scene->drawing_helper->FromScreenPixelsToScene(e.location));
		}
		if (!scene_editor_scene->boundary_box.IsCursorCaptured())
		{
			auto world_cursor_location = scene_editor_scene->drawing_helper->FromScreenPixelsToScene(TVec2i(e.location[0], e.location[1]));
			IBaluInstance* instance_collision(nullptr);
			if (scene_editor_scene->editor_scene_instance->PointCollide(world_cursor_location, instance_collision))
			{
				scene_editor_scene->boundary_box_contour->SetEnable(true);
				scene_editor_scene->boundary_box_contour->SetBox(instance_collision->GetOBB());
				scene_editor_scene->hightlighted_instance = instance_collision;
			}
			else
			{
				scene_editor_scene->boundary_box_contour->SetEnable(false);
				scene_editor_scene->hightlighted_instance = nullptr;
			}
		}

	}
	void OnMouseUp(TMouseEventArgs e)
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