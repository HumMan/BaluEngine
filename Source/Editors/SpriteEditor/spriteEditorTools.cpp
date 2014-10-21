
#include "spriteEditorTools.h"

#include "spriteEditor.h"


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
	auto new_shape = new TBaluPolygonShapeDef();
	new_shape->pos = world_cursor_location;

	new_shape->b2shape.m_count = 8;
	for (int i = 0; i < 8; i++)
	{
		new_shape->b2shape.m_vertices[i] = *(b2Vec2*)&TVec2(1, 1).GetRotated(DegToRad(45.0f)*i);
	}

	phys_body_editor_scene->phys_body->fixtures.push_back(std::unique_ptr<TBaluShapeDef>(new_shape));

	auto new_box = new TPolygonShapeAdornment(new_shape);
	phys_body_editor_scene->boundaries.push_back(std::unique_ptr<TBoundaryBoxAdornment>(new_box));
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
