#pragma once

#include <Editor/abstractEditor.h>

#include "spriteEditorScene.h"
#include "spriteEditorTools.h"

#include <WorldDef/Objects/Scene/IScene.h>
#include <WorldDef/IWorld.h>

using namespace EngineInterface;

#include <Editor/DrawingHelper.h>

class TSpriteEditor :public TAbstractEditor
{

	TSpriteEditorScene scene;
	TSpriteEditorToolsRegistry tools_registry;
	std::unique_ptr<TDrawingHelper> drawing_helper;
public:
	TSpriteEditor(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluSprite* edited_sprite, IBaluWorldInstance* world_instance);;
	~TSpriteEditor();

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	bool EndSelectedAsWork();
	IBaluSceneInstance* GetEditorSceneInstance();
	const std::vector<TToolWithDescription>& GetAvailableTools();
	//void SetActiveTool(TEditorTool* tool);
};
