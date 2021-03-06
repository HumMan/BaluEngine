
#include "sceneEditorTools.h"

#include "sceneEditorScene.h"

#include <Editor/DrawingHelper.h>

#include <WorldInstance/Objects/Scene/ISceneInstance.h>

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
	if (e.button != TMouseButton::Left)
		return;
	if (active_tool_class != nullptr)
	{
		auto transform = TBaluTransform(scene_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location), TRot(0));

		auto new_source_scene_instance = scene_editor_scene->source_scene->CreateInstance(active_tool_class);
		new_source_scene_instance->SetTransform(transform);

		auto new_class_instance = SceneObjectInstanceFactory::Create(
			new_source_scene_instance->GetFactoryName(), 
			new_source_scene_instance, 
			dynamic_cast<TBaluSceneInstance*>(scene_editor_scene->editor_scene_instance));

		scene_editor_scene->selected_instance = new_class_instance;

		scene_editor_scene->boundary_box->SetBoundary(new_class_instance->GetOBB());
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
		auto new_scale = scene_editor_scene->selected_instance->GetScale().ComponentMul(scale);
		scene_editor_scene->selected_instance->GetSource()->SetScale(new_scale);
	}
	void BoxMove(TVec2 old_pos, TVec2 new_pos)
	{
		auto trans = scene_editor_scene->selected_instance->GetTransform();
		trans.position = new_pos;
		scene_editor_scene->selected_instance->GetSource()->SetTransform(trans);
	}
	void BoxRotate(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
	{
		auto trans = scene_editor_scene->selected_instance->GetTransform();
		trans.angle = TRot(new_box);
		scene_editor_scene->selected_instance->GetSource()->SetTransform(trans);
	}

	void OnMouseDown(TMouseEventArgs e)
	{
		if (e.button != TMouseButton::Left)
			return;
		if (scene_editor_scene->boundary_box->enable)
		{
			scene_editor_scene->boundary_box->OnMouseDown(e, scene_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		}
		if (!scene_editor_scene->boundary_box->IsCursorCaptured())
		{
			if (scene_editor_scene->hightlighted_instance != nullptr)
			{
				scene_editor_scene->selected_instance = scene_editor_scene->hightlighted_instance;
				scene_editor_scene->boundary_box->OnChange = this;
				scene_editor_scene->boundary_box->enable = true;
				scene_editor_scene->boundary_box->SetBoundary(scene_editor_scene->selected_instance->GetOBB());

				scene_editor_scene->selection_listeners->EmitOnSelectionChange(dynamic_cast<IProperties*>(scene_editor_scene->selected_instance));
			}
			else
			{
				scene_editor_scene->boundary_box->enable = false;
				scene_editor_scene->selected_instance = nullptr;

				scene_editor_scene->selection_listeners->EmitOnSelectionChange(dynamic_cast<IProperties*>(scene_editor_scene->selected_instance));
			}
		}
	}
	void OnMouseMove(TMouseEventArgs e)
	{
		if (scene_editor_scene->boundary_box->enable)
		{
			scene_editor_scene->boundary_box->OnMouseMove(e, scene_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		}
		if (!scene_editor_scene->boundary_box->IsCursorCaptured())
		{
			auto world_cursor_location = scene_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(TVec2i(e.location[0], e.location[1]));
			TSceneObjectInstance* instance_collision(nullptr);
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
		if (e.button != TMouseButton::Left)
			return;
		if (scene_editor_scene->boundary_box->enable)
		{
			scene_editor_scene->boundary_box->OnMouseUp(e, scene_editor_scene->drawing_helper->GetContext().FromScreenPixelsToScene(e.location));
		}
		if (!scene_editor_scene->boundary_box->IsCursorCaptured())
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