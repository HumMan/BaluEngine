#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

#include "spriteEditorScene.h"
#include "spriteEditorTools.h"

#include "../../EngineInterfaces/IScene.h"
#include "../../EngineInterfaces/IWorld.h"

using namespace EngineInterface;

#include "../DrawingHelper.h"

class TSpriteEditor :public TAbstractEditor
{

	TSpriteEditorScene scene;
	TSpriteEditorToolsRegistry tools_registry;
	std::unique_ptr<TDrawingHelper> drawing_helper;
public:
	TSpriteEditor();
	//void StartEdit(TBaluSpriteDef* use_sprite);
	//void EndEdit();

	void Initialize(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluSprite* edited_sprite, IBaluSceneInstance* editor_scene_instance);
	void Deinitialize()
	{
	}

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	bool EndSelectedAsWork();

	const std::vector<TToolWithDescription>& GetAvailableTools();
	//void SetActiveTool(TEditorTool* tool);
};