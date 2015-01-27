#pragma once

#include <vector>
#include <map>
#include <list>
#include <memory>

#include <baluLib.h>

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
	virtual void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
	virtual void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location) = 0;
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