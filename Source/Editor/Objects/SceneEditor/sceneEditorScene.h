#pragma once

#include <vector>
#include <memory>

#include <WorldDef/Objects/Scene/IScene.h>
#include <WorldInstance/Objects/Scene/ISceneInstance.h>
#include <WorldDef/IWorld.h>

using namespace EngineInterface;

#include "../../EditorGui/EditableBox/OBBGuiInstance.h"
#include "../../EditorGui/BoxContour/BoxGuiInstance.h"

#include <Editor/abstractEditor.h>

class TSceneEditorScene
{
public:
	IBaluScene* source_scene;

	IBaluSceneInstance* editor_scene_instance;
	TSceneObjectInstance* selected_instance;
	
	TDrawingHelper* drawing_helper;

	//tools controls
	TBoundaryBoxAdornment* boundary_box;
	TOBBContour* boundary_box_contour;

	TSceneObjectInstance* hightlighted_instance;

	TSelectionChangeListeners* selection_listeners;
public:
	void Initialize(IBaluWorld* world, IBaluScene* source_scene, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper, TSelectionChangeListeners* selection_listeners);
	void Deinitialize();
};
