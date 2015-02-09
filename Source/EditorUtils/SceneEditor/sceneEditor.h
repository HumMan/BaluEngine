#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

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
	//void StartEdit(TBaluClassDef* use_Class);
	//void EndEdit();

	void Initialize(TScreen* screen, TView* view, IViewport* viewport, IBaluWorld* world, IBaluScene* source_scene, IBaluSceneInstance* source_scene_instance);

	//override:
	//void Initialize(IBaluWorld* world, IBaluScene* obj, TVec2 editor_global_pos);

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	bool EndSelectedAsWork();

	//void Render(TDrawingHelper* drawing_helper);
	const std::vector<TToolWithDescription>& GetAvailableTools();
};