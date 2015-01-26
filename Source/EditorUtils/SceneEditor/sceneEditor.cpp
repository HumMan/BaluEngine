#include "sceneEditor.h"

#include "../../baluEditorDefs.h"
#include "sceneEditorTools.h"

#include "sceneEditorAdornments.h"

#include "../ClassEditor/classEditor.h"

TSceneEditor::TSceneEditor() :tools_registry(&scene)
{
	active_tool = nullptr;
}

void TSceneEditor::Initialize(TBaluSceneDef* obj)
{
	scene.Initialize(obj);
	for (const std::unique_ptr<TBaluInstanceDef>& v : obj->instances)
	{
		auto new_box = new TClassInstanceAdornment(v.get());
		scene.boundaries.emplace_back(std::unique_ptr<TClassInstanceAdornment>(new_box));
	}
}

void TSceneEditor::Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos)
{
	this->editor_global_pos = editor_global_pos;
	Initialize(dynamic_cast<TBaluSceneDef*>(obj));
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
	assert(scene.boundary_under_cursor != nullptr);
	if (scene.boundary_under_cursor != nullptr)
	{
		delete current_local_editor;
		{
			auto class_adornment = dynamic_cast<TClassInstanceAdornment*>(scene.boundary_under_cursor);
			if (class_adornment != nullptr)
			{
				current_local_editor = new TClassEditor();

				current_local_editor->parent_editors = parent_editors;
				current_local_editor->parent_editors.push_back(this);

				auto sprite_instance = class_adornment->GetSpriteInstance();

				current_local_editor->Initialize(sprite_instance->instance_class, sprite_instance->instance_transform.position);
			}
		}
	}
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
		current_local_editor->OnMouseDown(e, world_cursor_location);
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
		current_local_editor->OnMouseMove(e, world_cursor_location);
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
		current_local_editor->OnMouseUp(e, world_cursor_location);
	}
	else
	{
		if (active_tool != nullptr)
			active_tool->OnMouseUp(e, world_cursor_location);
	}
}

void TSceneEditor::Render(TDrawingHelper* drawing_helper)
{
	if (current_local_editor != nullptr)
	{
		drawing_helper->SetGlobalAlpha(0.5);
		drawing_helper->SetGlobalAlphaColor();
		for (const std::unique_ptr<TBoundaryBoxAdornment>& box : scene.boundaries)
		{
			if (box.get() != scene.boundary_under_cursor)
				box->Render(drawing_helper);
		}
		drawing_helper->UnsetGlobalAlpha();

		current_local_editor->Render(drawing_helper);
	}
	else
	{
		for (const std::unique_ptr<TBoundaryBoxAdornment>& box : scene.boundaries)
		{
			box->Render(drawing_helper);
		}
	}
}

