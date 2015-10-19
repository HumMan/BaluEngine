#include "classEditor.h"

#include "../IClassInstance.h"
#include "../../Scene/ISceneInstance.h"

TClassEditor::TClassEditor(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluClass* edited_class, IBaluWorldInstance* world_instance)
	: TAbstractEditor(world_instance), tools_registry(&scene)
{
	auto scene_instance = world_instance->RunScene();
	world_instance->GetComposer()->AddToRender(scene_instance, drawing_context.viewport);

	drawing_helper = std::make_unique<TDrawingHelper>(drawing_context);
	scene.Initialize(world, edited_class, scene_instance, drawing_helper.get());

	scene.transformed_class.reset(new TBaluTransformedClass(dynamic_cast<TBaluClass*>(edited_class)));
	scene.transformed_class->SetTransform(TBaluTransform());
	scene.transformed_class->SetScale(TVec2(1, 1));

	scene.editor_scene_class_instance = new TBaluTransformedClassInstance(scene.transformed_class.get(), dynamic_cast<TBaluSceneInstance*>(scene_instance));
}

IBaluSceneInstance* TClassEditor::GetEditorSceneInstance()
{
	return scene.editor_scene_instance;
}

TClassEditor::~TClassEditor()
{
	scene.Deinitialize();
	drawing_helper.reset();
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