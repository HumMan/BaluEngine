#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

#include "spritePolygonEditorScene.h"
#include "spritePolygonEditorTools.h"

class TSpritePolygonEditor :public TAbstractEditor
{
	//TSpritePolygonEditorScene scene;
	TBaluSpritePolygonDef* sprite;
	enum class CurrState
	{
		CanSubdivide,
		CanMoveSelected,
		MovingSelected,
		None
	} curr_state;

	std::vector<int> selected_points;

	int point_under_cursor;

	int nearest_point = -1;
	float nearest_point_dist = 0;

	int nearest_line = -1;
	float nearest_line_dist = 0;

	TVec2 cursor_pos;

	TVec2 old_cursor_pos;
	//TBaluWorldDef* world;

	std::vector<TToolWithDescription> tools;
public:
	TSpritePolygonEditor();
	//void StartEdit(TBaluSpriteDef* use_sprite);
	//void EndEdit();

	void Initialize(TBaluSpritePolygonDef* obj);
	void SetAsBox(TVec2 size);


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