#pragma once

#include <baluEngine.h>

#include "baluEditorDefs.h"
#include "baluEngineApi.h"
//class TAbstractEditorObject
//{
//
//};
//
//
//class TTextEditor : public TAbstractEditor
//{
//
//};

class TBaluEditorInternal;
class BALUENGINEDLL_API TBaluEditor
{
private:
	std::unique_ptr<TBaluEditorInternal> p;
public:
	TBaluEditor(HWND hWnd, TVec2i use_size);
	~TBaluEditor();
	void Render();

	TVec2 ScreenToWorld(const TVec2& v);
	TVec2 WorldToScreen(const TVec2& v);

	void SetViewport(TVec2i use_size);
	void OnMouseMove(TVec2i use_client_mouse_pos);
	void OnMouseClick(TVec2i use_client_mouse_pos);
	void OnMouseDown();
	void OnMouseUp();
	void OnMiddleDown();
	void OnMiddleUp();
	void OnMouseScroll(float delta);

	//
	void NewScene();
	void NewClass();
	void NewPhysBody();
	void NewSprite();
	void NewMaterial();

	void SetWorld(TBaluWorldDef* world);

	void Edit(TBaluSceneDef* scene);
	void Edit(TBaluShapeDef* phys_shape);
};