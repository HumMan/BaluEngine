#pragma once

#include <vector>
#include <memory>

#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/ISceneInstance.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "sceneEditorAdornments.h"

class TSceneEditorScene// : public TBoundaryBoxScene
{
	IBaluScene* source_scene;
	//IBaluSceneInstance* editor_temp_scene_instance;

	IBaluInstance* selected_instance;

	std::unique_ptr<TClassInstanceAdornment> adornment_instance;

	//std::vector<std::unique_ptr<TBoundaryBoxAdornment>> boundaries;
	//std::vector<TBoundaryBoxAdornment*> selected_boundaries; //TODO
	//TBoundaryBoxAdornment* boundary_under_cursor;
public:
	void Initialize(IBaluWorld* world, IBaluScene* source_scene, IBaluSceneInstance* source_scene_instance);
};