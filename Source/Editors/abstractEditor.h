#pragma once

#include "Tools.h"

#include <boost/signals2.hpp>
#include <boost/bind.hpp>

class TAbstractEditor
{
public:
	std::vector<TAbstractEditor*> parent_editors;
	TAbstractEditor* current_local_editor;
	TEditorTool* active_tool;
	TVec2 editor_global_pos;
public:

	boost::signals2::signal<void(TWorldObjectDef* old_selection, TWorldObjectDef* new_selectio)> OnSelectionChanged;

	TAbstractEditor()
	{
		editor_global_pos = TVec2(0, 0);
	}
	virtual void Initialize(TWorldObjectDef* obj, TVec2 editor_global_pos) = 0;

	virtual bool CanSetSelectedAsWork() = 0;
	virtual void SetSelectedAsWork() = 0;

	virtual bool CanEndSelectedAsWork() = 0;
	virtual bool EndSelectedAsWork() = 0;

	//std::map<std::string, TAbstractEditorObject*> CanCreateObjects();

	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location) = 0;

	virtual void Render(TDrawingHelper* drawing_helper) = 0;
	virtual const std::vector<TToolWithDescription>& GetAvailableTools()=0;
	virtual void SetActiveTool(TEditorTool* tool)=0;
};



