
#include "baluEditorDefs.h"

#include <pugixml.hpp>

using namespace pugi;



void SaveColor(pugi::xml_node& parent_node, std::string name, TVec4 color)
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

void SaveTransform(pugi::xml_node& parent_node, std::string name, TBaluTransform transform)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	SaveCoord(new_node, "Offset", transform.position);
	new_node.append_attribute("rotation").set_value(transform.angle.GetAngle());
}

TBaluTransform LoadTransform(pugi::xml_node& node)
{
	TBaluTransform transform;
	transform.position = LoadCoord(node.child("Offset"));
	transform.angle.Set(node.attribute("rotation").as_float());
	return transform;
}

void TBaluMaterialDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Material");
	new_node.append_attribute("name").set_value(material_name.c_str());
	new_node.append_attribute("image_path").set_value(image_path.c_str());
	SaveColor(new_node, "color", color);
}

void TBaluMaterialDef::Load(const pugi::xml_node& node, const int version, TBaluWorldDef* world)
{
	material_name = node.attribute("name").as_string();
	image_path = node.attribute("image_path").as_string();
	color = LoadColor(node.child("color"));
}

TOBB<float, 2> TBaluSpritePolygonDef::GetOBB()
{
	auto aabb = TAABB<float, 2>(TVec2(0, 0), TVec2(0, 0));
	for (int i = 0; i < polygon_vertices.size(); i++)
	{
		aabb += polygon_vertices[i];
	}
	this->aabb = aabb;
	return TOBB<float, 2>(transform.position, TMatrix2(FromB2Vec(transform.angle.GetXAxis()), FromB2Vec(transform.angle.GetYAxis())), aabb);
}

void TBaluSpritePolygonDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("SpritePolygon");
	if (material != nullptr)
		new_node.append_attribute("material_name").set_value(material->material_name.c_str());
	new_node.append_attribute("polygon_mode").set_value((int)polygone_mode);
	new_node.append_attribute("primitive").set_value((int)primitive);

	SaveTransform(new_node, "Transform", transform);

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

void TBaluSpritePolygonDef::Load(const pugi::xml_node& node, const int version, TBaluWorldDef* world)
{
	material = &world->materials[node.attribute("material_name").as_string()];

	polygone_mode = (TPolygonMode)node.attribute("polygon_mode").as_int();
	primitive = (TPrimitive)node.attribute("primitive").as_int();

	transform = LoadTransform(node.child("Transform"));

	{
		xml_node polygons_node = node.child("polygon_vertices");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			polygon_vertices.push_back(LoadCoord(polygon));
		}
	}
	{
		xml_node polygons_node = node.child("tex_coordinates");
		for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
		{
			tex_coordinates.push_back(LoadCoord(polygon));
		}
	}
}

void TBaluSpriteDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Sprite");
	new_node.append_attribute("name").set_value(sprite_name.c_str());
	xml_node polygons_node = new_node.append_child("polygons");
	for (int i = 0; i < polygons.size(); i++)
	{
		polygons[i]->Save(polygons_node, version);
	}
}

void TBaluSpriteDef::Load(const pugi::xml_node& node, const int version, TBaluWorldDef* world)
{
	sprite_name = node.attribute("name").as_string();
	xml_node polygons_node = node.child("polygons");
	for (pugi::xml_node polygon = polygons_node.first_child(); polygon; polygon = polygon.next_sibling())
	{
		auto new_poly = new TBaluSpritePolygonDef();
		new_poly->Load(polygon, version, world);
		polygons.push_back(std::unique_ptr<TBaluSpritePolygonDef>(new_poly));
	}
}

void TBaluCircleShapeDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("CircleShape");
	{
		new_node.append_attribute("radius").set_value(b2shape.m_radius);
		SaveTransform(new_node, "Transform", transform);
	}
}

void TBaluCircleShapeDef::Load(const pugi::xml_node& node, const int version, TBaluWorldDef* world)
{
	float radius = node.attribute("radius").as_float();
	TVec2 pos = LoadCoord(node.child("position"));
	transform = LoadTransform(node.child("Transform"));
	b2shape.m_radius = radius;
}

TOBB<float, 2> TBaluCircleShapeDef::GetOBB()
{
	return TOBB<float, 2>(transform.position, TMatrix<float, 2>::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(b2shape.m_radius)));
}

TOBB<float, 2> TBaluPolygonShapeDef::GetOBB()
{
	auto aabb = TAABB<float, 2>(TVec2(0, 0), TVec2(0, 0));
	for (int i = 0; i < b2shape.GetVertexCount(); i++)
	{
		auto v = b2shape.GetVertex(i);
		aabb.operator+=(*(TVec2*)&v);
	}
	this->aabb = aabb;
	return TOBB<float, 2>(transform.position, TMatrix2(FromB2Vec(transform.angle.GetXAxis()), FromB2Vec(transform.angle.GetYAxis())), aabb);
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
		SaveTransform(new_node, "Transform", transform);
	}
}

void TBaluPolygonShapeDef::Load(const pugi::xml_node& node, const int version, TBaluWorldDef* world)
{
	xml_node polygons_node = node.child("polygon_vertex");
	std::vector<TVec2> vertices;
	for (pugi::xml_node polygon_node = polygons_node.first_child(); polygon_node; polygon_node = polygon_node.next_sibling())
	{
		vertices.push_back(LoadCoord(polygon_node));
	}
	b2shape.Set((b2Vec2*)&vertices[0], vertices.size());
	transform = LoadTransform(node.child("Transform"));
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

void TBaluPhysBodyDef::Load(const pugi::xml_node& node, const int version, TBaluWorldDef* world)
{
	phys_body_name = node.attribute("name").as_string();

	xml_node fixtures_node = node.child("fixtures");
	for (pugi::xml_node fixture = fixtures_node.first_child(); fixture; fixture = fixture.next_sibling())
	{
		TBaluShapeDef* new_shape = nullptr;
		if (std::string(fixture.name()) == "PolygoneShape")
			new_shape = new TBaluPolygonShapeDef();
		if (std::string(fixture.name()) == "CircleShape")
			new_shape = new TBaluCircleShapeDef();
		new_shape->Load(fixture, version, world);
		fixtures.push_back(std::unique_ptr<TBaluShapeDef>(new_shape));
	}
}

TBaluPhysBodyDef::~TBaluPhysBodyDef()
{

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

void TBaluJointDef::Load(const pugi::xml_node& parent_node, const int version, TBaluWorldDef* world)
{
	xml_node new_node = parent_node.child("JointCommon");
	bodyA = new_node.attribute("bodyA").as_string();
	bodyB = new_node.attribute("bodyB").as_string();

	is_interinstance_joint = new_node.attribute("is_interinstance_joint").as_bool();
	if (is_interinstance_joint)
	{
		instanceA = new_node.attribute("instanceA").as_string();
		instanceB = new_node.attribute("instanceB").as_string();
	}
}

void TBaluPrismaticJointDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("PrismaticJoint");
	TBaluJointDef::Save(new_node, version);
}

void TBaluPrismaticJointDef::Load(const pugi::xml_node& parent_node, const int version, TBaluWorldDef* world)
{
	xml_node new_node = parent_node.child("PrismaticJoint");
	TBaluJointDef::Load(new_node, version, world);
}

void TBaluSpriteInstanceDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node sprite_node = parent_node.append_child("sprite");
	sprite_node.append_attribute("sprite_name").set_value(sprite->sprite_name.c_str());
	sprite_node.append_attribute("sprite_tag").set_value(tag.c_str());
	SaveTransform(sprite_node, "Transform", transform);
}

void TBaluSpriteInstanceDef::Load(const pugi::xml_node& node, const int version, TBaluWorldDef* world)
{
	sprite = &world->sprites[node.attribute("sprite_name").as_string()];
	tag = node.attribute("sprite_tag").as_string();
	transform = LoadTransform(node.child("Transform"));
}

TOBB<float, 2> TBaluSpriteInstanceDef::GetOBB()
{
	return TOBB<float, 2>(transform.position, TMatrix<float, 2>::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(0.5, 0.5)));
}

void TBaluBodyInstanceDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node body_node = parent_node.append_child("body");
	body_node.append_attribute("body_name").set_value(body->phys_body_name.c_str());
	body_node.append_attribute("body_tag").set_value(tag.c_str());
	SaveTransform(body_node, "Transform", transform);
}

void TBaluBodyInstanceDef::Load(const pugi::xml_node& node, const int version, TBaluWorldDef* world)
{
	body = &world->phys_bodies[node.attribute("body_name").as_string()];
	tag = node.attribute("body_tag").as_string();
	transform = LoadTransform(node.child("Transform"));
}

TOBB<float, 2> TBaluInstanceDef::GetOBB()
{
	return TOBB<float, 2>(this->instance_transform.position, TMatrix<float, 2>::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(0.5, 0.5)));
}

TOBB<float, 2> TBaluBodyInstanceDef::GetOBB()
{
	return TOBB<float, 2>(transform.position, TMatrix<float, 2>::GetIdentity(), TAABB<float, 2>(TVec2(0, 0), TVec2(0.5, 0.5)));
}

void TBaluClass::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Class");
	new_node.append_attribute("class_name").set_value(class_name.c_str());
	{
		xml_node sprites_node = new_node.append_child("sprites");
		for (int i = 0; i < sprites.size(); i++)
		{
			sprites[i]->Save(sprites_node, version);
		}
	}
	{
		xml_node bodies_node = new_node.append_child("bodies");
		for (int i = 0; i < bodies.size(); i++)
		{
			bodies[i]->Save(bodies_node, version);
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

void TBaluClass::Load(const pugi::xml_node& node, const int version, TBaluWorldDef* world)
{
	class_name = node.attribute("class_name").as_string();
	{
		xml_node sprites_node = node.child("sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			TBaluSpriteInstanceDef* new_sprite_instance = new TBaluSpriteInstanceDef();
			new_sprite_instance->Load(sprite_node, version, world);
			sprites.push_back(std::unique_ptr<TBaluSpriteInstanceDef>(new_sprite_instance));
		}
	}
	{
		xml_node bodies_node = node.child("bodies");
		for (pugi::xml_node body_node = bodies_node.first_child(); body_node; body_node = body_node.next_sibling())
		{
			TBaluBodyInstanceDef* new_sprite_instance = new TBaluBodyInstanceDef();
			new_sprite_instance->Load(body_node, version, world);
			bodies.push_back(std::unique_ptr<TBaluBodyInstanceDef>(new_sprite_instance));
		}
	}
	//{
	//	xml_node joints_node = node.child("joints");
	//	for (int i = 0; i < joints.size(); i++)
	//	{
	//		joints[i]->Load(joints_node, version, world);
	//	}
	//}
}

TBaluClass::~TBaluClass()
{

}

void TBaluInstanceDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Instance");
	new_node.append_attribute("name").set_value(name.c_str());
	new_node.append_attribute("class_name").set_value(instance_class->class_name.c_str());
	SaveTransform(new_node, "Transform", instance_transform);
}

void TBaluInstanceDef::Load(const pugi::xml_node& instance_node, const int version, TBaluWorldDef* world)
{
	name = instance_node.attribute("name").as_string();
	instance_class = &world->classes[instance_node.attribute("class_name").as_string()];
	instance_transform = LoadTransform(instance_node.child("Transform"));
}

void TBaluSceneDef::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Scene");
	new_node.append_attribute("name").set_value(scene_name.c_str());
	{
		xml_node instances_node = new_node.append_child("instances");
		for (int i = 0; i < instances.size(); i++)
		{
			instances[i]->Save(instances_node, version);
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

void TBaluSceneDef::Load(const pugi::xml_node& scene_node, const int version, TBaluWorldDef* world)
{
	scene_name = scene_node.attribute("name").as_string();
	{
		xml_node instances_node = scene_node.child("instances");
		for (pugi::xml_node instance_node = instances_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			TBaluInstanceDef* new_instance = new TBaluInstanceDef();
			new_instance->Load(instance_node, version, world);
			instances.push_back(std::unique_ptr<TBaluInstanceDef>(new_instance));
		}
	}
	//{
	//	xml_node joints_node = scene_node.child("joints");
	//	for (int i = 0; i < scene_joints.size(); i++)
	//	{
	//		scene_joints[i]->Load(joints_node, version, world);
	//	}
	//}
}

TBaluSceneDef::~TBaluSceneDef()
{

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
			i->second.Save(scenes_node, version);
		}
	}
}

void TBaluWorldDef::Load(const pugi::xml_node& document_node, const int version)
{
	xml_node world_node = document_node.child("World");
	{
		xml_node materials_node = world_node.child("Materials");
		for (pugi::xml_node material = materials_node.first_child(); material; material = material.next_sibling())
		{
			TBaluMaterialDef new_material;
			new_material.Load(material, version, this);
			materials[new_material.material_name] = new_material;
		}
	}
	{
		xml_node sprites_node = world_node.child("Sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			TBaluSpriteDef new_sprite;
			new_sprite.Load(sprite_node, version, this);
			sprites.insert(std::make_pair(new_sprite.sprite_name, std::move(new_sprite)));
		}
	}
	{
		xml_node bodies_node = world_node.child("PhysBodies");
		for (pugi::xml_node body_node = bodies_node.first_child(); body_node; body_node = body_node.next_sibling())
		{
			TBaluPhysBodyDef new_body;
			new_body.Load(body_node, version, this);
			phys_bodies.insert(std::make_pair(new_body.phys_body_name, std::move(new_body)));
		}
	}
	{
		xml_node classes_node = world_node.child("Classes");
		for (pugi::xml_node class_node = classes_node.first_child(); class_node; class_node = class_node.next_sibling())
		{
			TBaluClass new_class;
			new_class.Load(class_node, version, this);
			classes.insert(std::make_pair(new_class.class_name, std::move(new_class)));
		}
	}
	{
		xml_node scenes_node = world_node.child("Scenes");
		for (pugi::xml_node scene_node = scenes_node.first_child(); scene_node; scene_node = scene_node.next_sibling())
		{
			TBaluSceneDef new_scene;
			new_scene.Load(scene_node, version, this);
			scenes.insert(std::make_pair(new_scene.scene_name, std::move(new_scene)));
		}
	}
}

TBaluWorldDef::~TBaluWorldDef()
{

}