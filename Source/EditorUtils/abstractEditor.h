#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include "Tools.h"

#include "..\EngineInterfaces\IProperties.h"
#include "..\EngineInterfaces\IWorld.h"

#include "..\EditorInterfaces.h"

using namespace EngineInterface;

class TAbstractEditor: public EngineInterface::IAbstractEditor
{
	friend void OnMouseMove(TCallbackData* data, TMouseEventArgs e);
	friend void OnMouseDown(TCallbackData* data, TMouseEventArgs e);
	friend void OnMouseUp(TCallbackData* data, TMouseEventArgs e);
private:
	IBaluWorld* world;
protected:
	std::vector<TAbstractEditor*> parent_editors;
	TAbstractEditor* current_local_editor;
	IEditorTool* active_tool;
	TVec2 editor_global_pos;

	void InitializeControls(IBaluWorld* world);
	void DeinitializeControls();

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



