#include "classEditorScene.h"

#include "../../../EditorGUI/EditableBox/OBBGuiInstance.h"

#include "../../Scene/ISceneInstance.h"


void TClassEditorScene::Initialize(IBaluWorld* world, IBaluClass* source_class, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper)
{
	this->source_class = source_class;
	this->editor_scene_instance = source_scene_instance;
	this->drawing_helper = drawing_helper;

	boundary_box_contour = new TOBBContour(dynamic_cast<TBaluSceneInstance*>(editor_scene_instance));
	boundary_box = new TBoundaryBoxAdornment(dynamic_cast<TBaluSceneInstance*>(editor_scene_instance));
	boundary_box->enable = false;
}

void TClassEditorScene::Deinitialize()
{
	this->editor_scene_instance->DestroyInstance(dynamic_cast<TSceneObjectInstance*>(this->editor_scene_class_instance));
	source_class = nullptr;
	drawing_helper = nullptr;
	boundary_box_contour = nullptr;
	boundary_box = nullptr;
}