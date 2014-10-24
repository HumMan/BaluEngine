#include "classEditor.h"

#include "../../baluEditorDefs.h"
#include "classEditorTools.h"

#include "classEditorAdornments.h"

#include "../SpriteEditor/spriteEditor.h"
#include "../PhysBodyEditor/physBodyEditor.h"

TClassEditor::TClassEditor() :tools_registry(&scene)
{
	active_tool = nullptr;
}

void TClassEditor::Initialize(TBaluClass* obj)
{
	scene.Initialize(obj);
	for (const std::unique_ptr<TBaluSpriteInstanceDef>& v : obj->sprites)
	{
		auto new_box = new TClassSpriteAdornment(v.get());
		scene.boundaries.emplace_back(std::unique_ptr<TClassSpriteAdornment>(new_box));
	}
	for (const std::unique_ptr<TBaluBodyInstanceDef>& v : obj->bodies)
	{
		auto new_box = new TClassPhysBodyAdornment(v.get());
		scene.boundaries.emplace_back(std::unique_ptr<TClassPhysBodyAdornment>(new_box));
	}
}

void TClassEditor::Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos)
{
	this->editor_global_pos = editor_global_pos;
	Initialize(dynamic_cast<TBaluClass*>(obj));
}

bool TClassEditor::CanSetSelectedAsWork()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->CanSetSelectedAsWork();
	}
	else
		return scene.boundary_under_cursor != nullptr;
}

void TClassEditor::SetSelectedAsWork()
{
	assert(scene.boundary_under_cursor != nullptr);
	if (scene.boundary_under_cursor != nullptr)
	{
		delete current_local_editor;
		{
			auto sprite_adornment = dynamic_cast<TClassSpriteAdornment*>(scene.boundary_under_cursor);
			if (sprite_adornment != nullptr)
			{
				current_local_editor = new TSpriteEditor();

				current_local_editor->parent_editors = parent_editors;
				current_local_editor->parent_editors.push_back(this);

				auto sprite_instance = sprite_adornment->GetSpriteInstance();

				current_local_editor->Initialize(sprite_instance->sprite, sprite_instance->transform.position);
			}
		}
		{
			auto phys_body_adornment = dynamic_cast<TClassPhysBodyAdornment*>(scene.boundary_under_cursor);
			if (phys_body_adornment != nullptr)
			{
				current_local_editor = new TPhysBodyEditor();

				current_local_editor->parent_editors = parent_editors;
				current_local_editor->parent_editors.push_back(this);

				auto phys_body_instance = phys_body_adornment->GetPhysBodyInstance();

				current_local_editor->Initialize(phys_body_instance->body, phys_body_instance->transform.position);
			}
		}
	}
}

bool TClassEditor::CanEndSelectedAsWork()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->CanEndSelectedAsWork();
	}
	else
		return parent_editors.size()>0;
}
bool TClassEditor::EndSelectedAsWork()
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

const std::vector<TToolWithDescription>& TClassEditor::GetAvailableTools()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->GetAvailableTools();
	}
	else
		return tools_registry.GetTools();
}

void TClassEditor::SetActiveTool(TEditorTool* tool)
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->SetActiveTool(tool);
	}
	else
		active_tool = tool;
}

void TClassEditor::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
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

void TClassEditor::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
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

void TClassEditor::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
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

void TClassEditor::Render(TDrawingHelper* drawing_helper)
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

