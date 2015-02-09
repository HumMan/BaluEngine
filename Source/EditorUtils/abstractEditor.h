#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include "Tools.h"

#include "..\EngineInterfaces\IProperties.h"
#include "..\EngineInterfaces\IWorld.h"

#include "..\EditorInterfaces.h"

using namespace EngineInterface;

class TEditorSelectionChangedListener
{
public:
	void SelectionChanged(IProperties* old_selection, IProperties* new_selection);
};

class TAbstractEditor: public EngineInterface::IAbstractEditor
{
public:
	std::vector<TAbstractEditor*> parent_editors;
	TAbstractEditor* current_local_editor;
	IEditorTool* active_tool;
	TVec2 editor_global_pos;

	void InitializeControls(IBaluWorld* world);
	void DeinitializeControls();

public:

	TEditorSelectionChangedListener* OnSelectionChanged;

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
	virtual void SetActiveTool(IEditorTool* tool);
	IEditorTool* GetActiveTool()
	{
		return active_tool;
	}
	~TAbstractEditor()
	{}
};



