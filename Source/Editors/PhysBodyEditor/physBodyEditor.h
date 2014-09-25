#pragma once

#include "../abstractEditor.h"
#include "../BoundaryEditor.h"

class TPhysBodyEditor;

class TPhysBodyEditorToolsRegistry//: public TEditorToolsRegistry
{
	std::vector<TToolWithDescription> tools;
	TPhysBodyEditor* phys_body_editor;
public:
	TPhysBodyEditorToolsRegistry(TPhysBodyEditor* phys_body_editor);
	TPhysBodyEditorToolsRegistry(TPhysBodyEditorToolsRegistry&& o) 
	{
		tools = std::move(o.tools);
		phys_body_editor = std::move(o.phys_body_editor);
	}
	const std::vector<TToolWithDescription>& GetTools();
	~TPhysBodyEditorToolsRegistry();
};

class TPhysBodyEditor:public TAbstractEditor
{
public:
	//TBoundaryEditor boundary_editor;
	std::vector<std::unique_ptr<TBoundaryBoxAdornment>> boundaries;
	std::vector<std::unique_ptr<TJointAdornment>> joints;

	

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

//class TEditorPhysShape
//{
//public:
//	void CanMove();
//	void CanResize();
//	void CanRotate();
//	void OnMove();
//	void OnResize();
//	void OnRotate();
//	void Clone();
//	void Draw();
//
//	bool CanEdit();
//	TAbstractEditor* Edit();
//
//	TOBB<float, 2> bounding_box;
//};
//
//class TPhysBodyEditor : public TAbstractEditor
//{
//
//};
