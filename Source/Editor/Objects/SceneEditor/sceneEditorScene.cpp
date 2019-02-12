#include "sceneEditorScene.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;

void TSceneEditorScene::Initialize(WorldDef::IWorld* world, WorldDef::IScene* source_scene,
	TDrawingHelper* drawing_helper, TSelectionChangeListeners* selection_listeners)
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