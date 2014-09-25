#pragma once

#include <vector>
#include <map>
#include <list>

#include <baluLib.h>

#include "../baluEditorDefs.h"

class TDrawingHelper;

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

class TEditorTool
{
public:
	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void Render(TDrawingHelper* drawing_helper) = 0;
	virtual ~TEditorTool(){}
};

class TToolWithDescription
{
public:
	std::unique_ptr<TEditorTool> tool;
	std::string name, image, tooltip;
	TToolWithDescription(TEditorTool* tool, std::string name)
	{
		this->tool.reset(tool);
		this->name = name;			 
	}
	TToolWithDescription(TToolWithDescription&& o)
	{
		tool = std::move(o.tool);
		name = std::move(o.name);
	}
	~TToolWithDescription();
};

class TAbstractEditor
{
protected:
	std::vector<TAbstractEditor*> parent_editors;
	TAbstractEditor* current_local_editor;
	TEditorTool* active_tool;
public:
	
	virtual void Initialize(TWorldObjectDef* obj) = 0;

	virtual bool CanSetSelectedAsWork() = 0;
	virtual void SetSelectedAsWork() = 0;

	virtual bool CanEndSelectedAsWork() = 0;
	virtual void EndSelectedAsWork() = 0;

	//std::map<std::string, TAbstractEditorObject*> CanCreateObjects();

	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location) = 0;

	virtual void Render(TDrawingHelper* drawing_helper) = 0;
	virtual const std::vector<TToolWithDescription>& GetAvailableTools()=0;
	virtual void SetActiveTool(TEditorTool* tool)=0;
};



