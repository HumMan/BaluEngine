#pragma once

#include <vector>
#include <map>
#include <list>
#include <memory>

#include <baluLib.h>

#include "..\EngineInterfaces\IWorld.h"

class TDrawingHelper;


enum class TWorldObjectType
{
	Material,
	Sprite,
	PhysBody,
	Class,
	None
};

class TEditorTool
{
public:
	virtual TWorldObjectType NeedObjectSelect() = 0;
	//virtual void SetSelectedObject(TWorldObjectDef* obj) = 0;
	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location) = 0;

	virtual void CancelOperation() = 0;

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
	~TToolWithDescription()
	{}
};