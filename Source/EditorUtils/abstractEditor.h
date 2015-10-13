#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include <World\IProperties.h>
#include <World\IWorldInstance.h>

#include <EditorUtils\IAbstractEditor.h>

using namespace EngineInterface;

class TAbstractEditor : 
	public IAbstractEditor, 
	public TMouseEventListener, 
	public TSelectionChangeListeners
{
private:
	IBaluWorldInstance* world_instance;

protected:
	std::vector<TAbstractEditor*> parent_editors;
	TAbstractEditor* current_local_editor;
	IEditorTool* active_tool;
	TVec2 editor_global_pos;

	void OnMouseMove(TMouseEventArgs e);
	void OnMouseDown(TMouseEventArgs e);
	void OnMouseUp(TMouseEventArgs e);

public:

	TAbstractEditor(IBaluWorldInstance* world_instance);
	virtual ~TAbstractEditor();

	virtual void SetActiveTool(IEditorTool* tool);
	IEditorTool* GetActiveTool()
	{
		return active_tool;
	}
};



