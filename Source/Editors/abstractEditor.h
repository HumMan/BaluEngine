#pragma once

#include <vector>
#include <map>
#include <list>

#include <baluLib.h>

#include "../baluEditorDefs.h"

class TAbstractEditor
{
public:
	std::vector<TAbstractEditor*> parent_editors;

	TAbstractEditor* current_local_editor;

	void MouseMove();
	void MouseDown();
	void MouseUp();

	//void Edit(TAbstractEditorObject* obj);

	//std::map<std::string, TAbstractEditorObject*> CanCreateObjects();
};




