#pragma once

#include "exportMacro.h"

#include "baluEditorDefs.h"
#include "exportMacro.h"
#include "Editors\abstractEditor.h"
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

	typedef void(*SelectionChangedCallbackRefType)(void* calle, TWorldObjectDef* old_selection, TWorldObjectDef* new_selection);
	SelectionChangedCallbackRefType SelectionChangedCallbackRef;
	void* SelectionChangedCallbackRef_calle;

	typedef void(*PropertiesChangedCallbackRefType)(void* calle, TWorldObjectDef* changed_object);
	PropertiesChangedCallbackRefType PropertiesChangedCallbackRef;
	void* PropertiesChangedCallbackRef_calle;
public:
	void AddSelectionChangedCallback(void* calle, SelectionChangedCallbackRefType MyCallback);
	void RemoveSelectionChangedCallback(SelectionChangedCallbackRefType MyCallback);

	void AddPropertiesChangedCallback(void* calle, PropertiesChangedCallbackRefType MyCallback);
	void RemovePropertiesChangedCallback(PropertiesChangedCallbackRefType MyCallback);

	TBaluEditor(int hWnd, TVec2i use_size);
	~TBaluEditor();
	void Render();

	TVec2 DirScreenToWorld(const TVec2& v);
	TVec2 ScreenToWorld(const TVec2& v);
	TVec2 ScreenToWorld(const TVec2i& screen);
	TVec2 DirScreenToWorld(const TVec2i& screen);
	TVec2 WorldToScreen(const TVec2& v);

	void OnMouseDown(TMouseEventArgs e);
	void OnMouseMove(TMouseEventArgs e);
	void OnMouseUp(TMouseEventArgs e);

	void SetViewport(TVec2i use_size);

	void OnMouseWheel(float delta);

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