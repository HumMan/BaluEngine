#pragma once

#include <vector>
#include <map>
#include <list>

#include <baluLib.h>

#include "../baluEditorDefs.h"

enum class TMouseButton
{
	Left,
	Right,
	Middle
};

struct TMouseEventArgs
{
	TMouseButton button;
	TVec2i location;
};

class TAbstractEditor
{
protected:
	std::vector<TAbstractEditor*> parent_editors;
	TAbstractEditor* current_local_editor;
public:
	
	virtual void Initialize(TWorldObjectDef* obj) = 0;

	virtual bool CanSetSelectedAsWork() = 0;
	virtual void SetSelectedAsWork() = 0;

	virtual bool CanEndSelectedAsWork() = 0;
	virtual void EndSelectedAsWork() = 0;

	//std::map<std::string, TAbstractEditorObject*> CanCreateObjects();

	virtual void OnMouseDown(TMouseEventArgs e) = 0;
	virtual void OnMouseMove(TMouseEventArgs e) = 0;
	virtual void OnMouseUp(TMouseEventArgs e) = 0;

	void Render(TDrawingHelper* drawing_helper);
};




