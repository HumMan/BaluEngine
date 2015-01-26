
#include "spriteEditor.h"

#include "spriteEditorAdornments.h"

#include "../SpritePolygonEditor/spritePolygonEditor.h"

#include "../abstractEditor.h"

TSpriteEditor::TSpriteEditor() : tools_registry(&scene)
{
}

void TSpriteEditor::Initialize(TBaluSpriteDef* obj)
{
	scene.Initialize(obj);

	for (const std::unique_ptr<TBaluSpritePolygonDef>& v : obj->polygons)
	{
		auto new_box = new TSpritePolygonAdornment(v.get());
		scene.boundaries.emplace_back(std::unique_ptr<TSpritePolygonAdornment>(new_box));
	}


}

void TSpriteEditor::Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos)
{
	this->editor_global_pos = editor_global_pos;
	Initialize(dynamic_cast<TBaluSpriteDef*>(obj));
}

bool TSpriteEditor::CanSetSelectedAsWork()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->CanSetSelectedAsWork();
	}else
		return scene.boundary_under_cursor!=nullptr;
}
void TSpriteEditor::SetSelectedAsWork()
{
	assert(scene.boundary_under_cursor != nullptr);
	if (scene.boundary_under_cursor != nullptr)
	{
		delete current_local_editor;

		current_local_editor = new TSpritePolygonEditor();

		current_local_editor->parent_editors = parent_editors;
		current_local_editor->parent_editors.push_back(this);

		auto sprite_polygon = (dynamic_cast<TSpritePolygonAdornment*>(scene.boundary_under_cursor))->GetSprite();

		current_local_editor->Initialize(sprite_polygon, sprite_polygon->transform.position);

		current_local_editor->OnSelectionChanged.connect(OnSelectionChanged);

		OnSelectionChanged((TWorldObjectDef*) this->scene.sprite, (TWorldObjectDef*)sprite_polygon);
	}
}

bool TSpriteEditor::CanEndSelectedAsWork()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->CanEndSelectedAsWork();
	}
	else
		return parent_editors.size()>0;
}
bool TSpriteEditor::EndSelectedAsWork()
{
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

const std::vector<TToolWithDescription>& TSpriteEditor::GetAvailableTools()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->GetAvailableTools();
	}else
		return tools_registry.GetTools();
}
void TSpriteEditor::SetActiveTool(TEditorTool* tool)
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->SetActiveTool(tool);
	}
	else
	active_tool = tool;
}


void TSpriteEditor::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
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
void TSpriteEditor::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
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
void TSpriteEditor::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
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


void TSpriteEditor::Render(TDrawingHelper* drawing_helper)
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