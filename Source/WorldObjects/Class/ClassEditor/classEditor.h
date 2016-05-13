#pragma once

#include <EditorUtils/abstractEditor.h>

#include "classEditorScene.h"
#include "classEditorTools.h"

#include <World/IWorld.h>

using namespace EngineInterface;

#include <EditorUtils/DrawingHelper.h>

class TClassEditor :public TAbstractEditor
{

	TClassEditorScene scene;
	TClassEditorToolsRegistry tools_registry;
	std::unique_ptr<TDrawingHelper> drawing_helper;
public:
	TClassEditor(TDrawingHelperContext drawing_context, IBaluWorld* world, IBaluClass* edited_class, IBaluWorldInstance* world_instance);
	~TClassEditor();

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	bool EndSelectedAsWork();
	IBaluSceneInstance* GetEditorSceneInstance();
	const std::vector<TToolWithDescription>& GetAvailableTools();
};
