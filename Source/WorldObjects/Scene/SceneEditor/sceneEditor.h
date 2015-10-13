#pragma once

#include <EditorUtils/abstractEditor.h>

#include "sceneEditorScene.h"
#include "sceneEditorTools.h"

#include "../IScene.h"
#include <World/IWorld.h>

using namespace EngineInterface;

#include <EditorUtils/DrawingHelper.h>

class TSceneEditor :public TAbstractEditor
{

	TSceneEditorScene scene;
	TSceneEditorToolsRegistry tools_registry;
	std::unique_ptr<TDrawingHelper> drawing_helper;
public:
	TSceneEditor(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluScene* edited_scene, IBaluWorldInstance* world_instance);
	~TSceneEditor();

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	bool EndSelectedAsWork();
	IBaluSceneInstance* GetEditorSceneInstance();
	const std::vector<TToolWithDescription>& GetAvailableTools();
};