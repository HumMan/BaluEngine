#pragma once

#include <vector>
#include <memory>

#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "../../SpecialClasses/OBBGuiInstance.h"
#include "../../SpecialClasses/BoxGuiInstance.h"

#include "../selectionListener.h"

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