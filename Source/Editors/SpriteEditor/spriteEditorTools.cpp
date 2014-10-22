
#include "spriteEditorTools.h"

#include "spriteEditor.h"

#include "spriteEditorAdornments.h"

class TCreateSpritePolygonTool : public TEditorTool
{
protected:
	TSpriteEditorScene* sprite_editor_scene;
public:
	TCreateSpritePolygonTool(TSpriteEditorScene* sprite_editor_scene);
	void OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location);
	void Render(TDrawingHelper* drawing_helper);
};

TCreateSpritePolygonTool::TCreateSpritePolygonTool(TSpriteEditorScene* sprite_editor_scene)
{
	this->sprite_editor_scene = sprite_editor_scene;
}

void TCreateSpritePolygonTool::OnMouseDown(TMouseEventArgs e, TVec2 world_cursor_location)
{
	auto new_sprite_polygon = new TBaluSpritePolygonDef();
	new_sprite_polygon->transform.position = world_cursor_location;
	new_sprite_polygon->transform.angle.Set(0);
	new_sprite_polygon->polygon_vertices.resize(8);
	for (int i = 0; i < 8; i++)
	{
		new_sprite_polygon->polygon_vertices[i] = TVec2(1, 1).GetRotated(DegToRad(45.0f)*i);
	}

	sprite_editor_scene->sprite->polygons.push_back(std::unique_ptr<TBaluSpritePolygonDef>(new_sprite_polygon));

	auto new_box = new TSpritePolygonAdornment(new_sprite_polygon);
	sprite_editor_scene->boundaries.push_back(std::unique_ptr<TSpritePolygonAdornment>(new_box));
}

void TCreateSpritePolygonTool::OnMouseMove(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateSpritePolygonTool::OnMouseUp(TMouseEventArgs e, TVec2 world_cursor_location)
{

}
void TCreateSpritePolygonTool::Render(TDrawingHelper* drawing_helper)
{

}

TSpriteEditorRegistry::TSpriteEditorRegistry(TSpriteEditorScene* scene)
{
	this->scene = scene;
	tools.emplace_back(new TCreateSpritePolygonTool(scene), "Polygon");
	tools.emplace_back(new TBoundaryBoxesModifyTool(scene), "Modify");
}
TSpriteEditorRegistry::TSpriteEditorRegistry(TSpriteEditorRegistry&& o)
{
	tools = std::move(o.tools);
	scene = std::move(o.scene);
}
const std::vector<TToolWithDescription>& TSpriteEditorRegistry::GetTools()
{
	return tools;
}
TSpriteEditorRegistry::~TSpriteEditorRegistry()
{

}