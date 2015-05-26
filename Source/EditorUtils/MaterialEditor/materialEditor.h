#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

#include "materialEditorScene.h"
#include "materialEditorTools.h"

#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "../DrawingHelper.h"

class TMaterialEditor:public TAbstractEditor
{
public:
	
	TMaterialEditorScene scene;
	TMaterialEditorToolsRegistry tools_registry;
	std::unique_ptr<TDrawingHelper> drawing_helper;
public:
	TMaterialEditor();
	void UnsetAcitveTool();

	void Initialize(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluMaterial* edited_material, IBaluSceneInstance* editor_scene_instance);
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