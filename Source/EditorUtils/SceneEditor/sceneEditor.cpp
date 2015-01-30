#include "sceneEditor.h"

#include "sceneEditorTools.h"

#include "sceneEditorAdornments.h"

//#include "../ClassEditor/classEditor.h"

#include "../../EngineInterfaces/ISceneInstance.h"

TSceneEditor::TSceneEditor() :tools_registry(&scene)
{
	active_tool = nullptr;
}


void SceneEditorAdornmentCustomDraw(IBaluSpritePolygonInstance* instance, NVGcontext* vg)
{
	TSceneEditor* editor = instance->GetSprite()->GetClass()->GetProperties()->GetPointer("editor");
	editor->GetActiveTool()->OnDraw(instance, vg);
}

void SceneEditorAdornmentMouseMove(IBaluSpritePolygonInstance* instance)
{
	TSceneEditor* editor = instance->GetSprite()->GetClass()->GetProperties()->GetPointer("editor");
	TClassInstanceAdornment* adornment = instance->GetSprite()->GetClass()->GetProperties()->GetPointer("adornment");
	editor->GetActiveTool()->OnMouseMove(adornment);
}

void SceneEditorMouseMove(IBaluSceneInstance* instance)
{
	TSceneEditor* editor = instance->GetSprite()->GetClass()->GetProperties()->GetPointer("editor");
	editor->GetActiveTool()->OnGlobalMouseMove();
}

EngineInterface::IBaluClass* CreateEditorClasses(TSceneEditor* editor, IBaluWorld* world)
{
	auto adornment_class = world->CreateClass("SceneEditorAdornment");
	auto adornment_sprite = world->CreateSprite("SceneEditorAdornment_custom_draw_sprite");
	adornment_sprite->GetPolygone()->OnCustomDraw(SceneEditorAdornmentCustomDraw);
	adornment_sprite->GetPolygone()->OnMouseMove();
	adornment_sprite->GetPolygone()->OnMouseEnter();
	adornment_sprite->GetPolygone()->OnMouseLeave();
	adornment_sprite->GetPolygone()->OnMouseDown();
	adornment_sprite->GetPolygone()->OnMouseUp();
	adornment_class->AddSprite(adornment_sprite);

	return adornment_class;
}

void TSceneEditor::Initialize(IBaluWorld* world, IBaluScene* obj)
{
	auto adornment_class = CreateEditorClasses(this, world);

	obj->OnMouseMove(SceneEditorMouseMove);

	scene.Initialize(obj);
	for (int i = 0; i < obj->GetInstancesCount();i++)
	{
		auto v = obj->GetInstance(i);
		auto new_box = new TClassInstanceAdornment(v);
		scene.boundaries.emplace_back(std::unique_ptr<TClassInstanceAdornment>(new_box));
	}
}

void TSceneEditor::Initialize(IBaluWorld* world, IBaluScene* obj, TVec2 editor_global_pos)
{
	this->editor_global_pos = editor_global_pos;
	Initialize(world, obj);
}

bool TSceneEditor::CanSetSelectedAsWork()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->CanSetSelectedAsWork();
	}
	else
		return scene.boundary_under_cursor != nullptr;
}

void TSceneEditor::SetSelectedAsWork()
{
	//assert(scene.boundary_under_cursor != nullptr);
	//if (scene.boundary_under_cursor != nullptr)
	//{
	//	delete current_local_editor;
	//	{
	//		auto class_adornment = dynamic_cast<TClassInstanceAdornment*>(scene.boundary_under_cursor);
	//		if (class_adornment != nullptr)
	//		{
	//			current_local_editor = new TClassEditor();

	//			current_local_editor->parent_editors = parent_editors;
	//			current_local_editor->parent_editors.push_back(this);

	//			auto sprite_instance = class_adornment->GetSpriteInstance();

	//			current_local_editor->Initialize(sprite_instance->instance_class, sprite_instance->instance_transform.position);
	//		}
	//	}
	//}
}

bool TSceneEditor::CanEndSelectedAsWork()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->CanEndSelectedAsWork();
	}
	else
		return parent_editors.size()>0;
}
bool TSceneEditor::EndSelectedAsWork()
{
	assert(current_local_editor != nullptr);
	if (current_local_editor != nullptr)
	{
		if (current_local_editor->EndSelectedAsWork())
		{
			delete current_local_editor;
			current_local_editor = nullptr;
		}
		return false;
	}
	else
	{
		return true;
	}
}

const std::vector<TToolWithDescription>& TSceneEditor::GetAvailableTools()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->GetAvailableTools();
	}
	else
		return tools_registry.GetTools();
}

void TSceneEditor::SetActiveTool(TEditorTool* tool)
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->SetActiveTool(tool);
	}
	else
		active_tool = tool;
}

void TSceneEditor::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (current_local_editor != nullptr)
	{
		//current_local_editor->OnMouseDown(e, world_cursor_location);
	}
	else
	{
		if (active_tool != nullptr)
			active_tool->OnMouseDown(e, world_cursor_location);
	}
}

void TSceneEditor::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (current_local_editor != nullptr)
	{
		//current_local_editor->OnMouseMove(e, world_cursor_location);
	}
	else
	{
		if (active_tool != nullptr)
			active_tool->OnMouseMove(e, world_cursor_location);
	}
}

void TSceneEditor::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (current_local_editor != nullptr)
	{
		//current_local_editor->OnMouseUp(e, world_cursor_location);
	}
	else
	{
		if (active_tool != nullptr)
			active_tool->OnMouseUp(e, world_cursor_location);
	}
}

//void TSceneEditor::Render(TDrawingHelper* drawing_helper)
//{
//	if (current_local_editor != nullptr)
//	{
//		drawing_helper->SetGlobalAlpha(0.5);
//		drawing_helper->SetGlobalAlphaColor();
//		for (const std::unique_ptr<TBoundaryBoxAdornment>& box : scene.boundaries)
//		{
//			if (box.get() != scene.boundary_under_cursor)
//				box->Render(drawing_helper);
//		}
//		drawing_helper->UnsetGlobalAlpha();
//
//		current_local_editor->Render(drawing_helper);
//	}
//	else
//	{
//		for (const std::unique_ptr<TBoundaryBoxAdornment>& box : scene.boundaries)
//		{
//			box->Render(drawing_helper);
//		}
//	}
//}

