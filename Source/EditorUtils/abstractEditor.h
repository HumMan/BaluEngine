#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include "Tools.h"

#include <boost/signals2.hpp>
#include <boost/bind.hpp>

#include "..\EngineInterfaces\IProperties.h"

using namespace EngineInterface;

class TAbstractEditor
{
public:
	std::vector<TAbstractEditor*> parent_editors;
	TAbstractEditor* current_local_editor;
	TEditorTool* active_tool;
	TVec2 editor_global_pos;
public:

	boost::signals2::signal<void(IProperties* old_selection, IProperties* new_selection)> OnSelectionChanged;

	TAbstractEditor()
	{
		editor_global_pos = TVec2(0, 0);
	}

	virtual bool CanSetSelectedAsWork() = 0;
	virtual void SetSelectedAsWork() = 0;

	virtual bool CanEndSelectedAsWork() = 0;
	virtual bool EndSelectedAsWork() = 0;

	//std::map<std::string, TAbstractEditorObject*> CanCreateObjects();

	virtual const std::vector<TToolWithDescription>& GetAvailableTools()=0;
	virtual void SetActiveTool(TEditorTool* tool)=0;
};



