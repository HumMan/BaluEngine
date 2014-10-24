#include "classEditorAdornments.h"

TClassSpriteAdornment::TClassSpriteAdornment(TBaluSpriteInstanceDef* sprite_instance) :TBoundaryBoxAdornment(sprite_instance->GetOBB())
{
	this->sprite_instance = sprite_instance;
}

void TClassSpriteAdornment::OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
{
	//sprite_polygon_def->transform.position = new_box.GetPos();
	//auto orient = new_box.GetOrient();
	//sprite_polygon_def->transform.angle.c = orient[0][0];
	//sprite_polygon_def->transform.angle.s = orient[0][1];

	//auto old_aabb = old_box.GetLocalAABB();
	//auto new_aabb = new_box.GetLocalAABB();

	//auto trans = new_aabb.GetSize() / old_aabb.GetSize();

	//for (int i = 0; i < sprite_polygon_def->polygon_vertices.size(); i++)
	//{
	//	sprite_polygon_def->polygon_vertices[i][0] *= trans[0];
	//	sprite_polygon_def->polygon_vertices[i][1] *= trans[1];
	//}
}

void TClassSpriteAdornment::Render(TDrawingHelper* drawing_helper)
{
	TBoundaryBoxAdornment::Render(drawing_helper);
	//drawing_helper->DrawSpritePolygon(sprite_polygon_def);
}

bool TClassSpriteAdornment::IsCollideWithAdornment(TVec2 world_cursor_location)
{
	return boundary.Contain(world_cursor_location);
}
bool TClassSpriteAdornment::IsCollideWithObject(TVec2 world_cursor_location)
{
	//return polygon_world_object->b2shape.TestPoint(b2Transform(),*(b2Vec2*)&boundary.GetOrient().TransMul(world_cursor_location));
	throw std::exception();
}