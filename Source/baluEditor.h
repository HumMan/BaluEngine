#pragma once

#include "exportMacro.h"

#include "baluEditorDefs.h"
#include "Editors\Tools.h"


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

	typedef void(*ObjectCreatedCallbackRefType)(void* calle, TWorldObjectDef* new_object);
	ObjectCreatedCallbackRefType ObjectCreatedCallbackRef;
	void* ObjectCreatedCallbackRef_calle;

	void OnSelectionChangedEvent(TWorldObjectDef* old_selection, TWorldObjectDef* new_selection);
public:
	void AddSelectionChangedCallback(void* calle, SelectionChangedCallbackRefType MyCallback);
	void RemoveSelectionChangedCallback(SelectionChangedCallbackRefType MyCallback);

	void AddPropertiesChangedCallback(void* calle, PropertiesChangedCallbackRefType MyCallback);
	void RemovePropertiesChangedCallback(PropertiesChangedCallbackRefType MyCallback);

	void AddObjectCreatedCallback(void* calle, ObjectCreatedCallbackRefType MyCallback);
	void RemoveObjectCreatedCallback(ObjectCreatedCallbackRefType MyCallback);


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
	void CreateScene();
	void CreateClass();
	void CreatePhysBody();
	void CreateSprite();
	void CreateMaterial();

	void SetWorld(TBaluWorldDef* world);
	TBaluWorldDef* GetWorld();

	void Edit(TWorldObjectDef* obj_to_edit);
	void SetActiveTool(TEditorTool* tool);
	const std::vector<TToolWithDescription>& GetAvailableTools();

	bool CanSetSelectedAsWork();
	void SetSelectedAsWork();

	bool CanEndSelectedAsWork();
	void EndSelectedAsWork();

	bool ToolNeedObjectSelect(std::vector<TWorldObjectDef*>& selection_list);
	void SetToolSelectedObject(std::string obj_name);

	void SaveWorldTo(std::string path);
	void LoadWorldFrom(std::string path);
};