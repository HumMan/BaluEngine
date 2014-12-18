#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

#include "materialEditorScene.h"
#include "materialEditorTools.h"

class TMaterialEditor:public TAbstractEditor
{
public:
	
	TMaterialEditorScene scene;
	TMaterialEditorToolsRegistry tools_registry;
public:
	TMaterialEditor();
	void UnsetAcitveTool();

	void Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos);
	void Initialize(TBaluMaterialDef* obj);

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