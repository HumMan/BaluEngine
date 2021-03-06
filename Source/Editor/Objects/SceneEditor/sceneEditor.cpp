#include "sceneEditor.h"

#include <WorldInstance/Objects/Scene/ISceneInstance.h>

TSceneEditor::TSceneEditor(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluScene* edited_scene, IBaluWorldInstance* world_instance)
	:TAbstractEditor(world_instance), tools_registry(&scene)
{

	auto scene_instance = world_instance->RunScene(edited_scene);
	world_instance->GetComposer()->AddToRender(scene_instance, drawing_context.viewport);

	drawing_helper = std::unique_ptr<TDrawingHelper>(new TDrawingHelper(drawing_context));
	scene.Initialize(world, edited_scene, scene_instance, drawing_helper.get(), this);

}

IBaluSceneInstance* TSceneEditor::GetEditorSceneInstance()
{
	return scene.editor_scene_instance;
}

TSceneEditor::~TSceneEditor()
{
	scene.Deinitialize();
	drawing_helper.reset();
}

bool TSceneEditor::CanSetSelectedAsWork()
{
	return false;
	//if (current_local_editor != nullptr)
	//{
	//	return current_local_editor->CanSetSelectedAsWork();
	//}
	//else
	//	return scene.boundary_under_cursor != nullptr;
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
