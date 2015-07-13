#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include "Tools.h"

#include "..\EngineInterfaces\IProperties.h"
#include "..\EngineInterfaces\IWorldInstance.h"

#include "..\EditorInterfaces.h"

#include "..\WorldInstance.h"

using namespace EngineInterface;

class TAbstractEditor: public EngineInterface::IAbstractEditor, public TMouseEventListener
{
private:
	IBaluWorldInstance* world;
protected:
	std::vector<TAbstractEditor*> parent_editors;
	TAbstractEditor* current_local_editor;
	IEditorTool* active_tool;
	TVec2 editor_global_pos;

	void InitializeControls(IBaluWorldInstance* world);
	void DeinitializeControls();

public:
	void OnMouseMove(TMouseEventArgs e);
	void OnMouseDown(TMouseEventArgs e);
	void OnMouseUp(TMouseEventArgs e);

	TAbstractEditor()
	{
		editor_global_pos = TVec2(0, 0);
		current_local_editor = nullptr;
		world = nullptr;
		active_tool = nullptr;
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



