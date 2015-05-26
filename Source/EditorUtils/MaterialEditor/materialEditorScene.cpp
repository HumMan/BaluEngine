#include "materialEditorScene.h"

void TMaterialEditorScene::Initialize(IBaluWorld* world, IBaluMaterial* source_material, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper)
{
	this->editor_scene_instance = editor_scene_instance;

	adornment_instance = std::make_unique<TMaterialInstanceAdornment>(world, editor_scene_instance, source_material);
}

void TMaterialEditorScene::Deinitialize()
{
	adornment_instance.reset();
}