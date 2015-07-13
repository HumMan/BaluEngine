#pragma once

#include <vector>
#include <memory>

#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "../../SpecialClasses/OBBGuiInstance.h"
#include "../../SpecialClasses/BoxGuiInstance.h"

class TSceneEditorScene
{
private:
	//std::unique_ptr<TClassInstanceAdornment> adornment_instance;
	
	
public:
	IBaluScene* source_scene;

	IBaluSceneInstance* editor_scene_instance;
	TSceneObjectInstance* selected_instance;
	//IBaluSceneClassInstance* selected_instance_source;
	
	TDrawingHelper* drawing_helper;

	//tools controls
	TBoundaryBoxAdornment* boundary_box;
	TOBBContour* boundary_box_contour;

	TSceneObjectInstance* hightlighted_instance;

	//std::vector<std::unique_ptr<TBoundaryBoxAdornment>> boundaries;
	//std::vector<TBoundaryBoxAdornment*> selected_boundaries; //TODO
	//TBoundaryBoxAdornment* boundary_under_cursor;
public:
	void Initialize(IBaluWorld* world, IBaluScene* source_scene, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper);
	void Deinitialize();
};