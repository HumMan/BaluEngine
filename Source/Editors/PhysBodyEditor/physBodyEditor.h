#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

#include "physBodyEditorScene.h"
#include "physBodyEditorTools.h"

class TPhysBodyEditor:public TAbstractEditor
{
public:
	
	TPhysBodyEditorScene scene;
	TPhysBodyEditorToolsRegistry tools_registry;
public:
	TPhysBodyEditor();
	void UnsetAcitveTool();

	void AddBoundary(TBoundaryBoxAdornment* box);
	void AddJoint(TJointAdornment* joint);

	void Initialize(TWorldObjectDef* obj);
	void Initialize(TBaluPhysBodyDef* obj);

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	void EndSelectedAsWork();

	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);

	void Render(TDrawingHelper* drawing_helper);
	const std::vector<TToolWithDescription>& GetAvailableTools();
	void SetActiveTool(TEditorTool* tool);
};