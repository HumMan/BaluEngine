#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

#include "classEditorScene.h"
#include "classEditorTools.h"

class TClassEditor :public TAbstractEditor
{

	TClassEditorScene scene;
	TClassEditorToolsRegistry tools_registry;
public:
	TClassEditor();
	//void StartEdit(TBaluClassDef* use_Class);
	//void EndEdit();

	void Initialize(TBaluClass* obj);

	//override:
	void Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos);

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