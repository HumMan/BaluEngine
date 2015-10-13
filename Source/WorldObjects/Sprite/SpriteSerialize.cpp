#include <World\SerializeCommon.h>

#include "Interface.h"

#include <World\IWorld.h>

using namespace EngineInterface;

void TBaluSprite::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Sprite");
	new_node.append_attribute("name").set_value(sprite_name.c_str());
	sprite_polygon.Save(new_node, version);

	if (phys_shape)
	{
		xml_node fixture = new_node.append_child("Fixture");
		phys_shape->Save(fixture, version);
	}


}

void TBaluSprite::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	this->world = world;
	sprite_name = node.attribute("name").as_string();
	xml_node polygon_node = node.child("SpritePolygon");
	sprite_polygon.Load(polygon_node, version, world);

	xml_node fixture = node.child("Fixture");
	if (!fixture.empty())
	{
		fixture = fixture.first_child();
		TBaluPhysShape* new_shape = nullptr;
		if (std::string(fixture.name()) == "PolygoneShape")
			new_shape = new TBaluPolygonShape();
		if (std::string(fixture.name()) == "CircleShape")
			new_shape = new TBaluCircleShape();
		if (std::string(fixture.name()) == "BoxShape")
			new_shape = new TBaluBoxShape();
		new_shape->Load(fixture, version, world);
		phys_shape.reset(new_shape);
	}


}

void TBaluSpritePolygon::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("SpritePolygon");
	if (material != nullptr)
		new_node.append_attribute("material_name").set_value(material->GetName().c_str());

	SaveCoord(new_node, "size", size);

	SaveTransformWithScale(new_node, "Transform", transform);

	SaveCoord(new_node, "tex_coord_origin", tex_coord_origin);
	SaveCoord(new_node, "tex_coord_scale", tex_coord_scale);

	new_node.append_attribute("enable").set_value(enable);

	{
		xml_node polygons_node = new_node.append_child("polygon_vertices");
		for (const TVec2& v : polygon_vertices)
		{
			SaveCoord(polygons_node, "vertex", v);
		}
	}
	{
		xml_node polygons_node = new_node.append_child("triangulated");
		for (const TVec2& v : triangulated)
		{
			SaveCoord(polygons_node, "vertex", v);
		}
	}
	{
		xml_node polygons_node = new_node.append_child("tex_coordinates");
		for (const TVec2& v : tex_coordinates)
		{
			SaveCoord(polygons_node, "vertex", v);
		}
	}
	{
		xml_node polygons_node = new_node.append_child("AnimDescs");
		for (auto& anim_desc : anim_descs)
		{
			anim_desc->Save(polygons_node, version);
		}
	}
	{
		xml_node polygons_node = new_node.append_child("AnimLines");
		for (auto& anim_line : animation_lines)
		{
			anim_line.second.Save(polygons_node, version, this);
		}
	}
}

void TBaluSpritePolygon::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	std::string mat_name = "";
	if (node.attribute("material_name"))
		mat_name = node.attribute("material_name").as_string();

	if (mat_name != "")
		material = dynamic_cast<TBaluMaterial*>(world->GetMaterial(mat_name.c_str()));

	size = LoadCoord(node.child("size"));

	transform = LoadTransformWithScale(node.child("Transform"));

	tex_coord_origin = LoadCoord(node.child("tex_coord_origin"));
	tex_coord_scale = LoadCoord(node.child("tex_coord_scale"));

	enable = node.attribute("enable").as_bool();

	{
		xml_node polygons_node = node.child("polygon_vertices");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			polygon_vertices.push_back(LoadCoord(polygon));
		}
	}
	{
		xml_node polygons_node = node.child("triangulated");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			triangulated.push_back(LoadCoord(polygon));
		}
	}
	{
		xml_node polygons_node = node.child("tex_coordinates");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			tex_coordinates.push_back(LoadCoord(polygon));
		}
	}
	{
		xml_node polygons_node = node.child("AnimDescs");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			EngineInterface::TAnimDesc* new_desc = EngineInterface::AnimDescFactory::Create(polygon.name());
			new_desc->Load(polygon, version, world);
			anim_descs.push_back(std::unique_ptr<EngineInterface::TAnimDesc>(new_desc));
		}
	}
	{
		xml_node polygons_node = node.child("AnimLines");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			EngineInterface::TAnimLine line;
			line.Load(polygon, version, world, this);
			animation_lines.insert(std::make_pair(line.line_name, line));
		}
	}
}


void TBaluBoxShape::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("BoxShape");
	{
		new_node.append_attribute("width").set_value(width);
		new_node.append_attribute("height").set_value(height);
		TBaluPolygonShape::Save(new_node, version);
	}
}

void TBaluBoxShape::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	width = node.attribute("width").as_float();
	height = node.attribute("height").as_float();
	xml_node new_node = node.child("PolygoneShape");
	TBaluPolygonShape::Load(new_node, version, world);
}


void TBaluCircleShape::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("CircleShape");
	{
		new_node.append_attribute("radius").set_value(b2shape.m_radius);
		SaveTransformWithScale(new_node, "Transform", local);
	}
}

void TBaluCircleShape::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	float radius = node.attribute("radius").as_float();
	TVec2 pos = LoadCoord(node.child("position"));
	local = LoadTransformWithScale(node.child("Transform"));
	b2shape.m_radius = radius;
}


void TBaluPolygonShape::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("PolygoneShape");
	{
		xml_node polygons_node = new_node.append_child("polygon_vertex");
		for (int i = 0; i < b2shape.GetVertexCount(); i++)
		{
			SaveCoord(polygons_node, "vertex", *(TVec2*)(&b2shape.GetVertex(i)));
		}
		SaveTransformWithScale(new_node, "Transform", local);
	}
}

void TBaluPolygonShape::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	xml_node polygons_node = node.child("polygon_vertex");
	std::vector<TVec2> vertices;
	for (pugi::xml_node polygon_node = polygons_node.first_child(); polygon_node; polygon_node = polygon_node.next_sibling())
	{
		vertices.push_back(LoadCoord(polygon_node));
	}
	b2shape.Set((b2Vec2*)&vertices[0], vertices.size());
	local = LoadTransformWithScale(node.child("Transform"));
}

void EngineInterface::TFrame::Save(pugi::xml_node& parent_node, const int version)
{
	auto frame_node = parent_node.append_child("Frame");
	SaveCoord(frame_node, "left_bottom", left_bottom);
	SaveCoord(frame_node, "right_top", right_top);
}

void EngineInterface::TFrame::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
{
	left_bottom = LoadCoord(instance_node.child("left_bottom"));
	right_top = LoadCoord(instance_node.child("right_top"));
}

void EngineInterface::TSpecificFrame::Save(pugi::xml_node& parent_node, const int version)
{
	auto frame_node = parent_node.append_child("SpecificFrame");
	SaveCoord(frame_node, "left_bottom", left_bottom);
	SaveCoord(frame_node, "right_top", right_top);
}

void EngineInterface::TSpecificFrame::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
{
	left_bottom = LoadCoord(instance_node.child("left_bottom"));
	right_top = LoadCoord(instance_node.child("right_top"));
}
void EngineInterface::TGridFrames::Save(pugi::xml_node& parent_node, const int version)
{
	auto frame_node = parent_node.append_child("GridFrames");
	frame_node.append_attribute("cell_count_x").set_value(cell_count_x);
	frame_node.append_attribute("cell_count_y").set_value(cell_count_y);
	SaveCoord(frame_node, "left_bottom", left_bottom);
	SaveCoord(frame_node, "width_height", width_height);
}

void EngineInterface::TGridFrames::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
{
	cell_count_x = instance_node.attribute("cell_count_x").as_int();
	cell_count_y = instance_node.attribute("cell_count_y").as_int();
	left_bottom = LoadCoord(instance_node.child("left_bottom"));
	width_height = LoadCoord(instance_node.child("width_height"));
}

void EngineInterface::TAnimationFrames::Save(pugi::xml_node& parent_node, const int version, TBaluSpritePolygon* sprite_polygon)
{
	auto frames_node = parent_node.append_child("AnimationFrames");
	frames_node.append_attribute("anim_desc_id").set_value(sprite_polygon->GetAnimDescIndex(desc));
	auto f_node = frames_node.append_child("Frames");
	for (auto& v : frames)
		f_node.append_child("Frame").append_attribute("value").set_value(v);
}

void EngineInterface::TAnimationFrames::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TBaluSpritePolygon* sprite_polygon)
{
	int anim_desc_id = instance_node.attribute("anim_desc_id").as_int();
	desc = sprite_polygon->GetAnimDesc(anim_desc_id);
	auto f_node = instance_node.child("Frames");
	for (pugi::xml_node polygon = f_node.first_child(); polygon; polygon = polygon.next_sibling())
	{
		frames.push_back(polygon.attribute("value").as_int());
	}
}

void EngineInterface::TAnimLine::Save(pugi::xml_node& parent_node, const int version, TBaluSpritePolygon* sprite_polygon)
{
	auto anim_line_node = parent_node.append_child("AnimLine");
	anim_line_node.append_attribute("name").set_value(line_name.c_str());
	auto frames_node = anim_line_node.append_child("Frames");
	for (auto& frame : frames)
		frame.Save(frames_node, version, sprite_polygon);
}

void EngineInterface::TAnimLine::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world, TBaluSpritePolygon* sprite_polygon)
{
	line_name = instance_node.attribute("name").as_string();
	auto f_node = instance_node.child("Frames");
	for (pugi::xml_node polygon = f_node.first_child(); polygon; polygon = polygon.next_sibling())
	{
		TAnimationFrames temp;
		temp.Load(polygon, version, world, sprite_polygon);
		frames.push_back(temp);
	}
}
