#include "classEditor.h"

#include "../../ClassInstance.h"
#include "../../SceneInstance.h"

TClassEditor::TClassEditor() :tools_registry(&scene)
{
	active_tool = nullptr;
}

void TClassEditor::Initialize(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluClass* edited_class, IBaluSceneInstance* editor_scene_instance)
{
	InitializeControls(editor_scene_instance->GetWorld());

	drawing_helper = std::make_unique<TDrawingHelper>(drawing_context);
	scene.Initialize(world, edited_class, editor_scene_instance, drawing_helper.get());

	//int sprites_count = edited_class->GetSpritesCount();

	scene.editor_scene_class_instance = new TBaluInstance(dynamic_cast<TBaluClass*>(edited_class), TBaluTransform(), TVec2(1, 1), dynamic_cast<TBaluSceneInstance*>(editor_scene_instance));

	for (int i = 0; i < scene.editor_scene_class_instance->GetSpritesCount(); i++)
	{
		auto sprite_instance = scene.editor_scene_class_instance->GetSprite(i);
		auto sprite_source = edited_class->GetSprite(i);

		sprite_instance->SetTag(sprite_source);
	}
}

bool TClassEditor::CanSetSelectedAsWork()
{
	return false;
	//if (current_local_editor != nullptr)
	//{
	//	return current_local_editor->CanSetSelectedAsWork();
	//}
	//else
	//	return scene.boundary_under_cursor != nullptr;
}

void TClassEditor::SetSelectedAsWork()
{
	//assert(scene.boundary_under_cursor != nullptr);
	//if (scene.boundary_under_cursor != nullptr)
	//{
	//	delete current_local_editor;
	//	{
	//		auto sprite_adornment = dynamic_cast<TClassSpriteAdornment*>(scene.boundary_under_cursor);
	//		if (sprite_adornment != nullptr)
	//		{
	//			current_local_editor = new TSpriteEditor();

	//			current_local_editor->parent_editors = parent_editors;
	//			current_local_editor->parent_editors.push_back(this);

	//			auto sprite_instance = sprite_adornment->GetSpriteInstance();

	//			current_local_editor->Initialize(sprite_instance->sprite, sprite_instance->transform.position);

	//			current_local_editor->OnSelectionChanged.connect(OnSelectionChanged);

	//			OnSelectionChanged(nullptr, (TWorldObjectDef*)sprite_adornment->GetSpriteInstance());
	//		}
	//	}
	//	{
	//		auto phys_body_adornment = dynamic_cast<TClassPhysBodyAdornment*>(scene.boundary_under_cursor);
	//		if (phys_body_adornment != nullptr)
	//		{
	//			current_local_editor = new TPhysBodyEditor();

	//			current_local_editor->parent_editors = parent_editors;
	//			current_local_editor->parent_editors.push_back(this);

	//			auto phys_body_instance = phys_body_adornment->GetPhysBodyInstance();

	//			current_local_editor->Initialize(phys_body_instance->body, phys_body_instance->transform.position);

	//			current_local_editor->OnSelectionChanged.connect(OnSelectionChanged);

	//			OnSelectionChanged(nullptr, (TWorldObjectDef*)phys_body_adornment->GetPhysBodyInstance());
	//		}
	//	}
	//}
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