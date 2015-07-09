#include "sceneEditor.h"

//#include "../../EngineInterfaces/ISceneInstance.h"

TSceneEditor::TSceneEditor() :tools_registry(&scene)
{
	active_tool = nullptr;
	current_local_editor = nullptr;
}

void TSceneEditor::Initialize(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluScene* edited_scene, IBaluSceneInstance* editor_scene_instance)
{
	InitializeControls(world);

	drawing_helper = std::make_unique<TDrawingHelper>(drawing_context);
	scene.Initialize(world, edited_scene, editor_scene_instance, drawing_helper.get());

	for (int i = 0; i < edited_scene->GetInstancesCount(); i++)
	{
		auto source_instance = edited_scene->GetInstance(i);
		auto instance = editor_scene_instance->CreateInstance(source_instance->GetClass(), source_instance->GetTransform(), source_instance->GetScale());
		//TODO uncomment
		//instance->SetTag(source_instance);

		//instance->GetProperties()->SetSceneClassInstance("editor_source_instance", source_instance);
	}
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
