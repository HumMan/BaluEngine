#pragma once

#include <EditorUtils\abstractEditor.h>

#include "materialEditorScene.h"
#include "materialEditorTools.h"

#include <WorldObjects/Scene/IScene.h>
#include <World\IWorld.h>

using namespace EngineInterface;

#include <EditorUtils\DrawingHelper.h>

class TMaterialEditor:public TAbstractEditor
{
public:
	
	TMaterialEditorScene scene;
	TMaterialEditorToolsRegistry tools_registry;
	std::unique_ptr<TDrawingHelper> drawing_helper;
public:
	TMaterialEditor(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluMaterial* edited_material, IBaluWorldInstance* world_instance);
	~TMaterialEditor();
	void UnsetAcitveTool();

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	bool EndSelectedAsWork();
	IBaluSceneInstance* GetEditorSceneInstance();
	const std::vector<TToolWithDescription>& GetAvailableTools();
};