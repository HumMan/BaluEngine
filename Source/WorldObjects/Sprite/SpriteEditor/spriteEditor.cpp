
#include "spriteEditor.h"

TSpriteEditor::TSpriteEditor(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluSprite* edited_sprite, IBaluWorldInstance* world_instance) 
	:TAbstractEditor(world_instance), tools_registry(&scene)
{
	auto scene_instance = world_instance->RunScene();
	world_instance->GetComposer()->AddToRender(scene_instance, drawing_context.viewport);

	drawing_helper = std::make_unique<TDrawingHelper>(drawing_context);
	scene.Initialize(world, edited_sprite, scene_instance, drawing_helper.get());
	//for (int i = 0; i < obj->GetInstancesCount();i++)
	//{
	//auto v = obj->GetInstance(i);
	//auto new_box = new TClassInstanceAdornment(v);
	//scene.boundaries.emplace_back(std::unique_ptr<TClassInstanceAdornment>(new_box));
	//}
}

IBaluSceneInstance* TSpriteEditor::GetEditorSceneInstance()
{
	return scene.editor_scene_instance;
}

TSpriteEditor::~TSpriteEditor()
{
	scene.Deinitialize();
	drawing_helper.reset();
}

bool TSpriteEditor::CanSetSelectedAsWork()
{
	return false;
	//if (current_local_editor != nullptr)
	//{
	//	return current_local_editor->CanSetSelectedAsWork();
	//}
	//else
	//	return scene.boundary_under_cursor != nullptr;
}

void TSpriteEditor::SetSelectedAsWork()
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

const std::vector<TToolWithDescription>& TSpriteEditor::GetAvailableTools()
{
	if (current_local_editor != nullptr)
	{
		return current_local_editor->GetAvailableTools();
	}
	else
		return tools_registry.GetTools();
}