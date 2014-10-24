
#include "classEditorTools.h"

#include "classEditor.h"

#include "classEditorAdornments.h"

class TCreateClassSpriteTool : public TEditorTool
{
protected:
	TClassEditorScene* class_editor_scene;
public:
	TWorldObjectType NeedObjectSelect()
	{
		return TWorldObjectType::Sprite;
	}
	TCreateClassSpriteTool(TClassEditorScene* class_editor_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};

TCreateClassSpriteTool::TCreateClassSpriteTool(TClassEditorScene* class_editor_scene)
{
	this->class_editor_scene = class_editor_scene;
}

void TCreateClassSpriteTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	//auto new_sprite_polygon = new TBaluSpritePolygonDef();
	//new_sprite_polygon->transform.position = world_cursor_location;
	//new_sprite_polygon->transform.angle.Set(0);
	//new_sprite_polygon->polygon_vertices.resize(8);
	//for (int i = 0; i < 8; i++)
	//{
	//	new_sprite_polygon->polygon_vertices[i] = TVec2(1, 1).GetRotated(DegToRad(45.0f)*i);
	//}

	//class_editor_scene->balu_class->sprites.push_back(std::unique_ptr<TBaluSpritePolygonDef>(new_sprite_polygon));

	//auto new_box = new TSpritePolygonAdornment(new_sprite_polygon);
	//sprite_editor_scene->boundaries.push_back(std::unique_ptr<TSpritePolygonAdornment>(new_box));
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

TClassEditorToolsRegistry::TClassEditorToolsRegistry(TClassEditorScene* scene)
{
	this->scene = scene;
	tools.emplace_back(new TCreateClassSpriteTool(scene), "Sprite");
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