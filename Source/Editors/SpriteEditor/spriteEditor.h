#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

#include "spriteEditorScene.h"
#include "spriteEditorTools.h"

class TSpriteEditor :public TAbstractEditor
{

	TSpriteEditorScene scene;
	TSpriteEditorRegistry tools_registry;
public:
	TSpriteEditor();
	//void StartEdit(TBaluSpriteDef* use_sprite);
	//void EndEdit();

	void Initialize(TBaluSpriteDef* obj);
	void SetAsBox(TVec2 size);


	//override:
	void Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos);

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