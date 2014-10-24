
#include "classEditorTools.h"

#include "classEditor.h"

#include "classEditorAdornments.h"

class TCreateClassSpriteTool : public TEditorTool
{
protected:
	TClassEditorScene* class_editor_scene;
	TBaluSpriteDef* active_tool_sprite;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::Sprite;
	}
	void SetSelectedObject(TWorldObjectDef* obj)
	{
		active_tool_sprite = dynamic_cast<TBaluSpriteDef*>(obj);
	}
	TCreateClassSpriteTool(TClassEditorScene* class_editor_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};

class TCreateClassPhysBodyTool : public TEditorTool
{
protected:
	TClassEditorScene* class_editor_scene;
	TBaluPhysBodyDef* active_tool_sprite;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::PhysBody;
	}
	void SetSelectedObject(TWorldObjectDef* obj)
	{
		active_tool_sprite = dynamic_cast<TBaluPhysBodyDef*>(obj);
	}
	TCreateClassPhysBodyTool(TClassEditorScene* class_editor_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};

TCreateClassSpriteTool::TCreateClassSpriteTool(TClassEditorScene* class_editor_scene)
{
	this->class_editor_scene = class_editor_scene;
	active_tool_sprite = nullptr;
}

void TCreateClassSpriteTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool_sprite != nullptr)
	{
		auto new_sprite_instance = new TBaluSpriteInstanceDef();

		new_sprite_instance->transform.position = world_cursor_location;
		new_sprite_instance->transform.angle.Set(0);
		new_sprite_instance->sprite = active_tool_sprite;
		class_editor_scene->balu_class->sprites.push_back(std::unique_ptr<TBaluSpriteInstanceDef>(new_sprite_instance));

		auto new_box = new TClassSpriteAdornment(new_sprite_instance);
		class_editor_scene->boundaries.push_back(std::unique_ptr<TClassSpriteAdornment>(new_box));
	}
}

void TCreateClassSpriteTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateClassSpriteTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateClassSpriteTool::Render(TDrawingHelper* drawing_helper)
{

}

TCreateClassPhysBodyTool::TCreateClassPhysBodyTool(TClassEditorScene* class_editor_scene)
{
	this->class_editor_scene = class_editor_scene;
	active_tool_sprite = nullptr;
}

void TCreateClassPhysBodyTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	if (active_tool_sprite != nullptr)
	{
		auto new_phys_body_instance = new TBaluBodyInstanceDef();

		new_phys_body_instance->transform.position = world_cursor_location;
		new_phys_body_instance->transform.angle.Set(0);
		new_phys_body_instance->body = active_tool_sprite;
		class_editor_scene->balu_class->bodies.push_back(std::unique_ptr<TBaluBodyInstanceDef>(new_phys_body_instance));

		auto new_box = new TClassPhysBodyAdornment(new_phys_body_instance);
		class_editor_scene->boundaries.push_back(std::unique_ptr<TClassPhysBodyAdornment>(new_box));
	}
}

void TCreateClassPhysBodyTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateClassPhysBodyTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateClassPhysBodyTool::Render(TDrawingHelper* drawing_helper)
{

}

TClassEditorToolsRegistry::TClassEditorToolsRegistry(TClassEditorScene* scene)
{
	this->scene = scene;
	tools.emplace_back(new TCreateClassSpriteTool(scene), "Sprite");
	tools.emplace_back(new TCreateClassPhysBodyTool(scene), "Body");
	tools.emplace_back(new TBoundaryBoxesModifyTool(scene), "Modify");
}
TClassEditorToolsRegistry::TClassEditorToolsRegistry(TClassEditorToolsRegistry&& o)
{
	tools = std::move(o.tools);
	scene = std::move(o.scene);
}
const std::vector<TToolWithDescription>& TClassEditorToolsRegistry::GetTools()
{
	return tools;
}
TClassEditorToolsRegistry::~TClassEditorToolsRegistry()
{

}