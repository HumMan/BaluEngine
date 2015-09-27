#pragma once

#include "../abstractEditor.h"

#include "sceneEditorScene.h"
#include "sceneEditorTools.h"

#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "../DrawingHelper.h"

class TSceneEditor :public TAbstractEditor
{

	TSceneEditorScene scene;
	TSceneEditorToolsRegistry tools_registry;
	std::unique_ptr<TDrawingHelper> drawing_helper;
public:
	TSceneEditor();

	void Initialize(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluScene* edited_scene, IBaluSceneInstance* editor_scene_instance);
	void Deinitialize()
	{
		scene.Deinitialize();
		drawing_helper.reset();
		DeinitializeControls();
	}
	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	bool EndSelectedAsWork();

	const std::vector<TToolWithDescription>& GetAvailableTools();
};