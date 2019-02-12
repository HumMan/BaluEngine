

#include "Sprite.h"

#include "../World/World.h"

#include <pugixml.hpp>

#include "../Common/SerializeCommon.h"

using namespace pugi;
using namespace BaluLib;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

void TSprite::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node new_node = parent_node.append_child("Sprite");
	GetProperties()->Save(new_node, version);

	new_node.append_attribute("name").set_value(GetName().c_str());
	sprite_polygon.Save(new_node, version);

	if (phys_shape)
	{
		xml_node fixture = new_node.append_child("Fixture");
		phys_shape->Save(fixture, version);
	}

	
}

void TSprite::Load(const pugi::xml_node& node, const int version, IWorld* world)
{
	GetProperties()->Load(node, version, world);

	this->world = world;
	xml_node polygon_node = node.child("SpritePolygon");
	sprite_polygon.Load(polygon_node, version, world);

	xml_node fixture = node.child("Fixture");
	if (!fixture.empty())
	{
		fixture = fixture.first_child();
		TPhysShape* new_shape = nullptr;
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

void TSpritePolygon::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node new_node = parent_node.append_child("SpritePolygon");
	SaveProperties(new_node, version);
	if (material != nullptr)
		new_node.append_attribute("material_name").set_value(material->GetName().c_str());

	SerializeCommon::SaveCoord(new_node, "size", size);

	SerializeCommon::SaveTransformWithScale(new_node, "Transform", transform);

	SerializeCommon::SaveCoord(new_node, "tex_coord_origin", tex_coord_origin);
	SerializeCommon::SaveCoord(new_node, "tex_coord_scale", tex_coord_scale);

	{
		xml_node polygons_node = new_node.append_child("polygon_vertices");
		for (const TVec2& v : polygon_vertices)
		{
			SerializeCommon::SaveCoord(polygons_node, "vertex", v);
		}
	}
	{
		xml_node polygons_node = new_node.append_child("triangulated");
		for (const TVec2& v : triangulated)
		{
			SerializeCommon::SaveCoord(polygons_node, "vertex", v);
		}
	}
	{
		xml_node polygons_node = new_node.append_child("tex_coordinates");
		for (const TVec2& v : tex_coordinates)
		{
			SerializeCommon::SaveCoord(polygons_node, "vertex", v);
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
			anim_line.second->Save(polygons_node, version, this);
			polygons_node.last_child().append_attribute("name").set_value(anim_line.first.c_str());
		}
	}
}

void TSpritePolygon::Load(const pugi::xml_node& node, const int version, IWorld* world)
{
	LoadProperties(node, version);
	std::string mat_name = "";
	if (node.attribute("material_name"))
		mat_name = node.attribute("material_name").as_string();

	if (mat_name != "")
		material = dynamic_cast<TMaterial*>(world->GetMaterial(mat_name.c_str()));

	size = SerializeCommon::LoadCoord(node.child("size"));

	transform = SerializeCommon::LoadTransformWithScale(node.child("Transform"));

	tex_coord_origin = SerializeCommon::LoadCoord(node.child("tex_coord_origin"));
	tex_coord_scale = SerializeCommon::LoadCoord(node.child("tex_coord_scale"));

	{
		xml_node polygons_node = node.child("polygon_vertices");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			polygon_vertices.push_back(SerializeCommon::LoadCoord(polygon));
		}
	}
	{
		xml_node polygons_node = node.child("triangulated");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			triangulated.push_back(SerializeCommon::LoadCoord(polygon));
		}
	}
	{
		xml_node polygons_node = node.child("tex_coordinates");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			tex_coordinates.push_back(SerializeCommon::LoadCoord(polygon));
		}
	}
	{
		xml_node polygons_node = node.child("AnimDescs");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			IAnimDesc* new_desc = AnimDescFactory::Create(polygon.name());
			new_desc->Load(polygon, version, world);
			anim_descs.push_back(std::unique_ptr<IAnimDesc>(new_desc));
		}
	}
	{
		xml_node polygons_node = node.child("AnimLines");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			auto line = new TAnimLine();
			line->Load(polygon, version, dynamic_cast<TWorld*>(world), this);
			animation_lines.insert(std::make_pair(polygon.attribute("name").as_string(), std::unique_ptr<TAnimLine>(line)));
		}
	}
}


void TBaluBoxShape::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node new_node = parent_node.append_child("BoxShape");
	{
		SaveProperties(new_node, version);
	}
}

void TBaluBoxShape::Load(const pugi::xml_node& node, const int version, IWorld* world)
{
	LoadProperties(node, version);
}


void TBaluCircleShape::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node new_node = parent_node.append_child("CircleShape");
	SaveProperties(new_node, version);
}

void TBaluCircleShape::Load(const pugi::xml_node& node, const int version, IWorld* world)
{
	LoadProperties(node, version);
}

void TBaluPolygonShape::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node new_node = parent_node.append_child("PolygoneShape");
	{
		SaveProperties(new_node, version);
		xml_node polygons_node = new_node.append_child("polygon_vertex");
		for(auto& v : vertices)
		{
			SerializeCommon::SaveCoord(polygons_node, "vertex", v);
		}		
	}
}

void TBaluPolygonShape::Load(const pugi::xml_node& node, const int version, IWorld* world)
{
	LoadProperties(node, version);
	xml_node polygons_node = node.child("polygon_vertex");
	vertices.clear();
	for (pugi::xml_node polygon_node = polygons_node.first_child(); polygon_node; polygon_node = polygon_node.next_sibling())
	{
		vertices.push_back(SerializeCommon::LoadCoord(polygon_node));
	}
}

//void TFrame::Save(pugi::xml_node& parent_node, const int version)const
//{
//	auto frame_node = parent_node.append_child("Frame");
//	SerializeCommon::SaveCoord(frame_node, "left_bottom", left_bottom);
//	SerializeCommon::SaveCoord(frame_node, "right_top", right_top);
//}
//
//void TFrame::Load(const pugi::xml_node& instance_node, const int version, IWorld* world)
//{
//	left_bottom = SerializeCommon::LoadCoord(instance_node.child("left_bottom"));
//	right_top = SerializeCommon::LoadCoord(instance_node.child("right_top"));
//}

void TSpecificFrame::Save(pugi::xml_node& parent_node, const int version)const
{
	auto frame_node = parent_node.append_child("SpecificFrame");
	SerializeCommon::SaveCoord(frame_node, "left_bottom", left_bottom);
	SerializeCommon::SaveCoord(frame_node, "right_top", right_top);
}

void TSpecificFrame::Load(const pugi::xml_node& instance_node, const int version, IWorld* world)
{
	left_bottom = SerializeCommon::LoadCoord(instance_node.child("left_bottom"));
	right_top = SerializeCommon::LoadCoord(instance_node.child("right_top"));
}
void TGridFrames::Save(pugi::xml_node& parent_node, const int version)const
{
	auto frame_node = parent_node.append_child("GridFrames");
	frame_node.append_attribute("cell_count_x").set_value(cell_count_x);
	frame_node.append_attribute("cell_count_y").set_value(cell_count_y);
	SerializeCommon::SaveCoord(frame_node, "left_bottom", left_bottom);
	SerializeCommon::SaveCoord(frame_node, "width_height", width_height);
}

void TGridFrames::Load(const pugi::xml_node& instance_node, const int version, IWorld* world)
{
	cell_count_x = instance_node.attribute("cell_count_x").as_int();
	cell_count_y = instance_node.attribute("cell_count_y").as_int();
	left_bottom = SerializeCommon::LoadCoord(instance_node.child("left_bottom"));
	width_height = SerializeCommon::LoadCoord(instance_node.child("width_height"));
}

void TAnimationFrames::Save(pugi::xml_node& parent_node, const int version, const ISpritePolygon* sprite_polygon)const
{
	auto frames_node = parent_node.append_child("AnimationFrames");
	frames_node.append_attribute("anim_desc_id").set_value(sprite_polygon->GetAnimDescIndex(desc));
	auto f_node = frames_node.append_child("Frames");
	for (auto& v : frames)
		f_node.append_child("Frame").append_attribute("value").set_value(v);
}

void TAnimationFrames::Load(const pugi::xml_node& instance_node, const int version, IWorld* world, ISpritePolygon* sprite_polygon)
{
	int anim_desc_id = instance_node.attribute("anim_desc_id").as_int();
	desc = sprite_polygon->GetAnimDesc(anim_desc_id);
	auto f_node = instance_node.child("Frames");
	for (pugi::xml_node polygon = f_node.first_child(); polygon; polygon = polygon.next_sibling())
	{
		frames.push_back(polygon.attribute("value").as_int());
	}
}

void TAnimLine::Save(pugi::xml_node& parent_node, const int version, const TSpritePolygon* sprite_polygon)const
{
	auto anim_line_node = parent_node.append_child("AnimLine");
	auto frames_node = anim_line_node.append_child("Frames");
	for (auto& frame : frames)
		frame.get()->Save(frames_node, version, sprite_polygon);
}

void TAnimLine::Load(const pugi::xml_node& instance_node, const int version, IWorld* world, TSpritePolygon* sprite_polygon)
{
	auto f_node = instance_node.child("Frames");
	for (pugi::xml_node polygon = f_node.first_child(); polygon; polygon = polygon.next_sibling())
	{
		auto temp = new TAnimationFrames();
		temp->Load(polygon, version, world, sprite_polygon);
		frames.push_back(std::unique_ptr<IAnimationFrames>(temp));
	}
}
