#include "materialEditor.h"


TMaterialEditor::TMaterialEditor() :tools_registry(&scene)
{
	active_tool = nullptr;
}

void TMaterialEditor::Initialize(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluMaterial* edited_material, IBaluSceneInstance* editor_scene_instance)
{
	InitializeControls(world);

	drawing_helper = std::make_unique<TDrawingHelper>(drawing_context);
	scene.Initialize(world, edited_material, editor_scene_instance, drawing_helper.get());

	//for (int i = 0; i < edited_scene->GetInstancesCount(); i++)
	//{
	//	auto source_instance = edited_scene->GetInstance(i);
	//	auto instance = editor_scene_instance->CreateInstance(source_instance->GetClass(), source_instance->GetTransform(), source_instance->GetScale());
	//	//instance->GetProperties()->SetSceneClassInstance("editor_source_instance", source_instance);
	//}
}

void TMaterialEditor::UnsetAcitveTool()
{
	active_tool = nullptr;
}

bool TMaterialEditor::CanSetSelectedAsWork()
{
	return true;
}

void TMaterialEditor::SetSelectedAsWork()
{

}

bool TMaterialEditor::CanEndSelectedAsWork()
{
	return true;
}
bool TMaterialEditor::EndSelectedAsWork()
{
	return false;
}

const std::vector<TToolWithDescription>& TMaterialEditor::GetAvailableTools()
{
	return tools_registry.GetTools();
}