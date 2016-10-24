#include "materialEditorScene.h"

void TMaterialEditorScene::Initialize(IBaluWorld* world, IBaluMaterial* source_material, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper)
{
	this->editor_scene_instance = editor_scene_instance;
	this->source_material = source_material;
	this->editor_scene_class_instance = nullptr;
}

void TMaterialEditorScene::Deinitialize()
{
}