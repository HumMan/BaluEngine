#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include "..\EngineInterfaces\IProperties.h"
#include "..\EngineInterfaces\IWorldInstance.h"

#include <EditorUtils\IAbstractEditor.h>

using namespace EngineInterface;


class TAbstractEditor : 
	public EngineInterface::IAbstractEditor, 
	public TMouseEventListener, 
	public EngineInterface::TSelectionChangeListeners
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

	void OnMouseMove(TMouseEventArgs e);
	void OnMouseDown(TMouseEventArgs e);
	void OnMouseUp(TMouseEventArgs e);

public:

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

	virtual const std::vector<TToolWithDescription>& GetAvailableTools()=0;
	virtual void SetActiveTool(IEditorTool* tool);
	IEditorTool* GetActiveTool()
	{
		return active_tool;
	}
	~TAbstractEditor()
	{}
};



