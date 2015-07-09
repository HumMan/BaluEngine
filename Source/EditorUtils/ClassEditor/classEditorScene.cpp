#include "classEditorScene.h"

void TClassEditorScene::Initialize(IBaluWorld* world, IBaluClass* source_class, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper)
{
	this->source_class = source_class;
	this->editor_scene_instance = source_scene_instance;
	this->drawing_helper = drawing_helper;

	adornment_instance = std::make_unique<TClassSpriteAdornment>(editor_scene_instance, (IVisualAdornment*)&boundary_box, drawing_helper);
	boundary_box_contour = std::make_unique<TOBBContour>(editor_scene_instance, drawing_helper);

	this->editor_scene_class_instance = dynamic_cast<IBaluInstance*>(editor_scene_instance->CreateInstance(dynamic_cast<TSceneObject*>(source_class), TBaluTransform(), TVec2(1, 1)));

	boundary_box.enable = false;
}

void TClassEditorScene::Deinitialize()
{
	source_class = nullptr;
	drawing_helper = nullptr;
	adornment_instance.reset();
	boundary_box_contour.reset();
}