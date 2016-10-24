#include "materialEditor.h"


TMaterialEditor::TMaterialEditor(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluMaterial* edited_material, IBaluWorldInstance* world_instance) 
	: TAbstractEditor(world_instance), tools_registry(&scene)
{
	auto scene_instance = world_instance->RunScene();
	world_instance->GetComposer()->AddToRender(scene_instance, drawing_context.viewport);

	drawing_helper = std::unique_ptr<TDrawingHelper>(new TDrawingHelper(drawing_context));
	scene.Initialize(world, edited_material, scene_instance, drawing_helper.get());
}

IBaluSceneInstance* TMaterialEditor::GetEditorSceneInstance()
{
	return scene.editor_scene_instance;
}

TMaterialEditor::~TMaterialEditor()
{
	scene.Deinitialize();
	drawing_helper.reset();
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
