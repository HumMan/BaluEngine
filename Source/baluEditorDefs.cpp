
#include "baluEditorDefs.h"

#include <pugixml.hpp>

using namespace pugi;

TOBB<float, 2> TBaluPolygonShapeDef::GetOBB()
{
	auto aabb = TAABB<float, 2>();
	for (int i = 0; i < b2shape.GetVertexCount(); i++)
	{
		auto v = b2shape.GetVertex(i);
		aabb.operator+=(*(TVec2*)&v);
	}
	this->aabb = aabb;
	return TOBB<float, 2>(pos, TMatrix2(*(TVec2*)&angle.GetXAxis(), *(TVec2*)&angle.GetYAxis()), aabb);
}

TBaluPhysBodyDef::~TBaluPhysBodyDef()
{

}

void SaveColor(pugi::xml_node& parent_node, std::string name,TVec4 color)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	new_node.append_attribute("r").set_value(color[0]);
	new_node.append_attribute("g").set_value(color[1]);
	new_node.append_attribute("b").set_value(color[2]);
	new_node.append_attribute("a").set_value(color[3]);
}

TVec4 LoadColor(pugi::xml_node& node)
{
	TVec4 color;
	color[0] = node.attribute("r").as_float();
	color[1] = node.attribute("g").as_float();
	color[2] = node.attribute("b").as_float();
	color[3] = node.attribute("a").as_float();
	return color;
}

void SaveCoord(pugi::xml_node& parent_node, std::string name, TVec2 coord)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	new_node.append_attribute("x").set_value(coord[0]);
	new_node.append_attribute("y").set_value(coord[1]);
}

TVec2 LoadCoord(pugi::xml_node& node)
{
	TVec2 coord;
	coord[0] = node.attribute("x").as_float();
	coord[1] = node.attribute("y").as_float();
	return coord;
}

void SaveTransform(pugi::xml_node& parent_node, std::string name, TTransform transform)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	SaveCoord(new_node, "Offset", transform.offset);
	new_node.append_attribute("rotation").set_value(transform.rotation.GetAngle());
}

TTransform LoadTransform(pugi::xml_node& node)
{
	TTransform transform;
	transform.offset = LoadCoord(node.child("Offset"));
	transform.rotation.Set(node.attribute("rotation").as_float());
	return transform;
}

void TBaluMaterialDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Material");
	new_node.append_attribute("name").set_value(material_name.c_str());
	new_node.append_attribute("image_path").set_value(image_path.c_str());
	SaveColor(new_node, "color", color);
}

void TBaluMaterialDef::Load(const pugi::xml_node& node, const int version)
{
	material_name = node.attribute("name").as_string();
	image_path = node.attribute("image_path").as_string();
	color = LoadColor(node.child("color"));
}

void TBaluSpriteDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Sprite");
	new_node.append_attribute("name").set_value(sprite_name.c_str());
	new_node.append_attribute("material_name").set_value(material_name.c_str());
	new_node.append_attribute("polygon_mode").set_value((int)polygone_mode);
	new_node.append_attribute("primitive").set_value((int)primitive);

	{
		xml_node polygons_node = new_node.append_child("polygon_vertices");
		for (const TVec2& v : polygon_vertices)
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
}

void TBaluSpriteDef::Load(const pugi::xml_node& node, const int version)
{
}

void TBaluPolygonShapeDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("PolygoneShape");
	{
		xml_node polygons_node = new_node.append_child("polygon_vertex");
		for (int i = 0; i < b2shape.GetVertexCount(); i++)
		{
			SaveCoord(polygons_node, "vertex", *(TVec2*)(&b2shape.GetVertex(i)));
		}
	}
}

void TBaluPhysBodyDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("PhysBody");
	new_node.append_attribute("name").set_value(phys_body_name.c_str());

	xml_node fixtures_node = new_node.append_child("fixtures");
	for (int i = 0; i < fixtures.size(); i++)
	{
		fixtures[i]->Save(fixtures_node, version);
	}
}

void TBaluJointDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("JointCommon");
	new_node.append_attribute("bodyA").set_value(bodyA.c_str());
	new_node.append_attribute("bodyB").set_value(bodyB.c_str());

	new_node.append_attribute("is_interinstance_joint").set_value(is_interinstance_joint);
	if (is_interinstance_joint)
	{
		new_node.append_attribute("instanceA").set_value(instanceA.c_str());
		new_node.append_attribute("instanceB").set_value(instanceB.c_str());
	}
}

void TBaluPrismaticJointDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("PrismaticJoint");
	TBaluJointDef::Save(new_node, version);
}

void TBaluClass::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Class");
	new_node.append_attribute("class_name").set_value(class_name.c_str());
	{
		xml_node sprites_node = new_node.append_child("sprites");
		for (int i = 0; i < sprites.size(); i++)
		{
			xml_node sprite_node = sprites_node.append_child("sprite");
			sprite_node.append_attribute("sprite_name").set_value(sprites[i].c_str());
			sprite_node.append_attribute("sprite_tag").set_value(sprites_tags[i].c_str());
			SaveTransform(sprite_node, "Transform", sprites_transform[i]);
		}
	}
	{
		xml_node bodies_node = new_node.append_child("bodies");
		for (int i = 0; i < bodies.size(); i++)
		{
			xml_node body_node = bodies_node.append_child("body");
			body_node.append_attribute("body_name").set_value(bodies[i].c_str());
			body_node.append_attribute("body_tag").set_value(bodies_tags[i].c_str());
			SaveTransform(body_node, "Transform", bodies_transform[i]);
		}
	}
	{
		xml_node joints_node = new_node.append_child("joints");
		for (int i = 0; i < joints.size(); i++)
		{
			joints[i]->Save(joints_node, version);
		}
	}
}

void TBaluInstanceDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Instance");
	new_node.append_attribute("name").set_value(name.c_str());
	new_node.append_attribute("class_name").set_value(class_name.c_str());
	SaveTransform(new_node, "Transform", instance_transform);
}

void TBaluSceneDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Scene");
	new_node.append_attribute("name").set_value(name.c_str());
	{
		xml_node instances_node = new_node.append_child("instances");
		for (int i = 0; i < instances.size(); i++)
		{
			instances[i].Save(instances_node, version);
		}
	}
	{
		xml_node joints_node = new_node.append_child("joints");
		for (int i = 0; i < scene_joints.size(); i++)
		{
			scene_joints[i]->Save(joints_node, version);
		}
	}
}

void TBaluWorldDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("World");
	{
		xml_node materials_node = new_node.append_child("Materials");
		for (auto i = materials.begin(); i != materials.end(); i++)
		{
			i->second.Save(materials_node, version);
		}
	}
	{
		xml_node sprites_node = new_node.append_child("Sprites");
		for (auto i = sprites.begin(); i != sprites.end(); i++)
		{
			i->second.Save(sprites_node, version);
		}
	}
	{
		xml_node bodies_node = new_node.append_child("PhysBodies");
		for (auto i = phys_bodies.begin(); i != phys_bodies.end(); i++)
		{
			i->second.Save(bodies_node, version);
		}
	}
	{
		xml_node classes_node = new_node.append_child("Classes");
		for (auto i = classes.begin(); i != classes.end(); i++)
		{
			i->second.Save(classes_node, version);
		}
	}
	{
		xml_node scenes_node = new_node.append_child("Scenes");
		for (auto i = scenes.begin(); i != scenes.end(); i++)
		{
			i->Save(scenes_node, version);
		}
	}
}

