#include "physBodyEditorAdornments.h"

TPolygonShapeAdornment::TPolygonShapeAdornment(TBaluPolygonShapeDef* polygon_world_object) :TBoundaryBoxAdornment(polygon_world_object->GetOBB())
{
	this->polygon_world_object = polygon_world_object;
}

void TPolygonShapeAdornment::OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
{
	polygon_world_object->transform.position = new_box.GetPos();
	auto orient = new_box.GetOrient();
	polygon_world_object->transform.angle.c = orient[0][0];
	polygon_world_object->transform.angle.s = orient[0][1];

	auto old_aabb = old_box.GetLocalAABB();
	auto new_aabb = new_box.GetLocalAABB();

	auto trans = new_aabb.GetSize() / old_aabb.GetSize();

	for (int i = 0; i < polygon_world_object->b2shape.m_count; i++)
	{
		polygon_world_object->b2shape.m_vertices[i].x *= trans[0];
		polygon_world_object->b2shape.m_vertices[i].y *= trans[1];
	}
}

void TPolygonShapeAdornment::Render(TDrawingHelper* drawing_helper)
{
	TBoundaryBoxAdornment::Render(drawing_helper);
	drawing_helper->DrawPolygon(polygon_world_object);
}

bool TPolygonShapeAdornment::IsCollideWithAdornment(TVec2 world_cursor_location)
{
	return boundary.PointCollide(world_cursor_location);
}
bool TPolygonShapeAdornment::IsCollideWithObject(TVec2 world_cursor_location)
{
	return polygon_world_object->b2shape.TestPoint(b2Transform(),*(b2Vec2*)&boundary.GetOrient().TransMul(world_cursor_location));
}

TCircleShapeAdornment::TCircleShapeAdornment(TBaluCircleShapeDef* circle_world_object) :TBoundaryBoxAdornment(circle_world_object->GetOBB())
{
	this->circle_world_object = circle_world_object;
}
void TCircleShapeAdornment::OnBoxChange(TOBB<float, 2> old_box, TOBB<float, 2> new_box)
{
	circle_world_object->transform.position = new_box.GetPos();
	auto aabb = new_box.GetLocalAABB();
	circle_world_object->b2shape.m_radius = b2Min(aabb.GetSize()[0], aabb.GetSize()[1]);
}
void TCircleShapeAdornment::Render(TDrawingHelper* drawing_helper)
{
	TBoundaryBoxAdornment::Render(drawing_helper);
	drawing_helper->DrawCircle(circle_world_object);
}

bool TCircleShapeAdornment::IsCollideWithAdornment(TVec2 world_cursor_location)
{
	return boundary.PointCollide(world_cursor_location);
}
bool TCircleShapeAdornment::IsCollideWithObject(TVec2 world_cursor_location)
{
	return circle_world_object->b2shape.TestPoint(b2Transform(), *(b2Vec2*)&boundary.GetOrient().TransMul(world_cursor_location));
}
