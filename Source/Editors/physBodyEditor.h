#pragma once

#include "abstractEditor.h"
#include "BoundaryEditor.h"

class TPhysBodyEditor:public TAbstractEditor
{
	TBoundaryEditor boundary_editor;

public:
	void Initialize(TWorldObjectDef* obj);
	void Initialize(TBaluPhysBodyDef* obj);

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	void EndSelectedAsWork();

	void OnMouseDown(TMouseEventArgs e);
	void OnMouseMove(TMouseEventArgs e);
	void OnMouseUp(TMouseEventArgs e);
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
