#include "sceneEditorScene.h"
#include "../../EditorGUI/EditableBox/OBBGuiInstance.h"

#include <WorldInstance/Objects/Scene/ISceneInstance.h>

void TSceneEditorScene::Initialize(IBaluWorld* world, IBaluScene* source_scene, IBaluSceneInstance* editor_scene_instance, TDrawingHelper* drawing_helper, TSelectionChangeListeners* selection_listeners)
{
	this->selection_listeners = selection_listeners;
	this->source_scene = source_scene;
	this->editor_scene_instance = editor_scene_instance;
	this->drawing_helper = drawing_helper;

	boundary_box_contour = new TOBBContour(dynamic_cast<TBaluSceneInstance*>(editor_scene_instance));
	boundary_box = new TBoundaryBoxAdornment(dynamic_cast<TBaluSceneInstance*>(editor_scene_instance));
	boundary_box->enable = false;
}

void TSceneEditorScene::Deinitialize()
{
	source_scene = nullptr;
	drawing_helper = nullptr;
}