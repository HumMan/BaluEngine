#pragma once

#include <vector>
#include <memory>

#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "sceneEditorAdornments.h"

#include "../BoundaryEditor.h"



class TSceneEditorScene// : public TBoundaryBoxScene
{
private:
	std::unique_ptr<TClassInstanceAdornment> adornment_instance;
	
public:
	IBaluScene* source_scene;
	IBaluSceneInstance* source_scene_instance;
	//IBaluSceneInstance* editor_temp_scene_instance;
	IBaluInstance* selected_instance;
	IBaluSceneClassInstance* selected_instance_source;
	TBoundaryBoxAdornment boundary_box;
	TDrawingHelper* drawing_helper;

	//std::vector<std::unique_ptr<TBoundaryBoxAdornment>> boundaries;
	//std::vector<TBoundaryBoxAdornment*> selected_boundaries; //TODO
	//TBoundaryBoxAdornment* boundary_under_cursor;
public:
	void Initialize(IBaluWorld* world, IBaluScene* source_scene, IBaluSceneInstance* source_scene_instance, TDrawingHelper* drawing_helper);
};