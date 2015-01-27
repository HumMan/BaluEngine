#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

#include "sceneEditorScene.h"
#include "sceneEditorTools.h"

#include "../../EngineInterfaces/IScene.h"

using namespace EngineInterface;

class TSceneEditor :public TAbstractEditor
{

	TSceneEditorScene scene;
	TSceneEditorToolsRegistry tools_registry;
public:
	TSceneEditor();
	//void StartEdit(TBaluClassDef* use_Class);
	//void EndEdit();

	void Initialize(IBaluScene* obj);

	//override:
	void Initialize(IBaluScene* obj, TVec2 editor_global_pos);

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	bool EndSelectedAsWork();

	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);

	void Render(TDrawingHelper* drawing_helper);
	const std::vector<TToolWithDescription>& GetAvailableTools();
	void SetActiveTool(TEditorTool* tool);
};