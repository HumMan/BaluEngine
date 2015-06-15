#include "World.h"

#include <pugixml.hpp>

using namespace pugi;

void SaveColor(pugi::xml_node& parent, TVec4 color)
{
	xml_node new_node = parent.append_child("Color");
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
	SaveCoord(new_node, "offset", transform.position);
	new_node.append_attribute("rotation").set_value(transform.angle.GetAngle());
}

TBaluTransform LoadTransform(pugi::xml_node& node)
{
	TBaluTransform transform;
	transform.position = LoadCoord(node.child("offset"));
	transform.angle.Set(node.attribute("rotation").as_float());
	return transform;
}

void SaveTransformWithScale(pugi::xml_node& parent_node, std::string name, TBaluTransformWithScale transform)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	SaveCoord(new_node, "offset", transform.transform.position);
	new_node.append_attribute("rotation").set_value(transform.transform.angle.GetAngle());
	SaveCoord(new_node, "scale", transform.scale);
}

TBaluTransformWithScale LoadTransformWithScale(pugi::xml_node& node)
{
	TBaluTransformWithScale transform;
	transform.transform = LoadTransform(node);
	transform.scale = LoadCoord(node.child("scale"));
	return transform;
}

void TBaluMaterial::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Material");
	new_node.append_attribute("name").set_value(material_name.c_str());
	new_node.append_attribute("image_path").set_value(image_path.c_str());
	SaveColor(new_node, color);
}

void TBaluMaterial::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	material_name = node.attribute("name").as_string();
	image_path = node.attribute("image_path").as_string();
	color = LoadColor(node.child("Color"));
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
	cell_count_y=instance_node.attribute("cell_count_y").as_int();
	left_bottom = LoadCoord(instance_node.child("left_bottom"));
	width_height = LoadCoord(instance_node.child("width_height"));
}

void EngineInterface::TAnimationFrames::Save(pugi::xml_node& parent_node, const int version, TBaluSpritePolygon* sprite_polygon)
{
	auto frames_node = parent_node.append_child("AnimationFrames");
	frames_node.append_attribute("anim_desc_id").set_value(sprite_polygon->GetAnimDescIndex(desc));
	auto f_node=frames_node.append_child("Frames");
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

void TBaluSpritePolygon::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("SpritePolygon");
	if (material != nullptr)
		new_node.append_attribute("material_name").set_value(material->GetName().c_str());

	SaveCoord(new_node, "size", size);

	SaveTransformWithScale(new_node, "Transform", local);

	SaveCoord(new_node, "tex_coord_origin", tex_coord_origin);
	SaveCoord(new_node, "tex_coord_scale", tex_coord_scale);

	assert(!is_custom_draw);

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
		material = world->GetMaterial(mat_name.c_str());

	size = LoadCoord(node.child("size"));

	local = LoadTransformWithScale(node.child("Transform"));

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

void TBaluClassPhysBody::Save(pugi::xml_node& parent_node, const int version)
{
	auto phys_Body_node = parent_node.append_child("PhysBody");
	phys_Body_node.append_attribute("enable").set_value(enable);
	auto body_def_node = phys_Body_node.append_child("PhysBody");
	body_def_node.append_attribute("fixed_rotation").set_value(body_def.fixedRotation);
	body_def_node.append_attribute("type").set_value(body_def.type);
}

void TBaluClassPhysBody::Load(const pugi::xml_node& phys_body_node, const int version, TBaluWorld* world)
{
	enable = phys_body_node.attribute("enable").as_bool();
	auto body_def_node = phys_body_node.child("PhysBody");
	body_def.fixedRotation = body_def_node.attribute("fixed_rotation").as_bool();
	body_def.type = (b2BodyType)body_def_node.attribute("type").as_int();
}

void TTrackFrame::Save(pugi::xml_node& parent_node, const int version)const
{
	auto frame_node = parent_node.append_child("Frame");
	frame_node.append_attribute("time").set_value(time);
	frame_node.append_attribute("rotation").set_value(rotation);
}

void TTrackFrame::Load(const pugi::xml_node& frame_node, const int version, TBaluWorld* world)
{
	time = frame_node.attribute("time").as_float();
	rotation = frame_node.attribute("rotation").as_float();
}


void TTrack::Save(pugi::xml_node& parent_node, const int version, TSkeleton* skeleton)
{
	auto track_node = parent_node.append_child("Track");
	track_node.append_attribute("bone_id").set_value(skeleton->GetBoneIndex(bone));
	auto tracks_node = track_node.append_child("Frames");
	for (auto& frame : frames)
	{
		frame.Save(tracks_node, version);
	}
}

void TTrack::Load(const pugi::xml_node& track_node, const int version, TBaluWorld* world, TSkeleton* skeleton)
{
	bone = skeleton->GetBone(track_node.attribute("bone_id").as_int());
	auto tracks_node = track_node.child("Frames");
	for (pugi::xml_node prop_node = tracks_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		TTrackFrame frame;
		frame.Load(prop_node, version, world);
		frames.insert(frame);
	}
}


void TTimeLine::Save(pugi::xml_node& parent_node, const int version, TSkeleton* skeleton)
{
	auto timeline_node = parent_node.append_child("TimeLine");
	timeline_node.append_attribute("name").set_value(name.c_str());
	timeline_node.append_attribute("timeline_size").set_value(timeline_size);

	auto tracks_node = timeline_node.append_child("Tracks");
	for (auto& track : tracks)
	{
		track->Save(tracks_node, version, skeleton);
	}
}

void TTimeLine::Load(const pugi::xml_node& timeline_node, const int version, TBaluWorld* world, TSkeleton* skeleton)
{
	name = timeline_node.attribute("name").as_string();
	timeline_size = timeline_node.attribute("timeline_size").as_float();

	auto tracks_node = timeline_node.child("Tracks");
	for (pugi::xml_node prop_node = tracks_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		auto temp = std::make_unique<TTrack>();
		temp->Load(prop_node, version, world, skeleton);
		tracks.push_back(std::move(temp));
	}
}


void TSkeletonAnimation::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node skeleton_animation_node = parent_node.append_child("SkeletonAnimation");
	xml_node animations_node = skeleton_animation_node.append_child("Animations");
	for (auto& v : animations)
	{
		v->Save(animations_node, version, skeleton);
	}
}

void TSkeletonAnimation::Load(const pugi::xml_node& skel_animation_node, const int version, TBaluWorld* world)
{
	auto animation_node = skel_animation_node.child("Animations");
	for (pugi::xml_node prop_node = animation_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		auto temp = std::make_unique<TTimeLine>();
		temp->Load(prop_node, version, world, skeleton);
		animations.push_back(std::move(temp));
	}
}

void TBone::Save(pugi::xml_node& parent_node, const int version, TSkeleton* skeleton)
{
	xml_node bone_node = parent_node.append_child("Bone");

	bone_node.append_attribute("id").set_value(skeleton->GetBoneIndex(this));

	if (parent != nullptr)
		bone_node.append_attribute("parent_id").set_value(skeleton->GetBoneIndex(parent));
	else
		bone_node.append_attribute("parent_id").set_value(-1);

	SaveTransform(bone_node, "LocalTransform", local);

	xml_node children_node = bone_node.append_child("Children");
	for (auto& v : children)
	{
		xml_node child_node = children_node.append_child("Child");
		child_node.append_attribute("Id").set_value(skeleton->GetBoneIndex(v));
	}
}

void TBone::Load(const pugi::xml_node& bone_node, const int version, TBaluWorld* world, TSkeleton* skeleton)
{
	auto parent_id = bone_node.attribute("parent_id").as_int();
	if (parent_id == -1)
		parent = nullptr;
	else
		parent = skeleton->GetBone(parent_id);

	local = LoadTransform(bone_node.child("LocalTransform"));

	xml_node children_node = bone_node.child("Children");
	for (pugi::xml_node prop_node = children_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		children.push_back(skeleton->GetBone(prop_node.attribute("Id").as_int()));
	}
}

void TSkin::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node skin_node = parent_node.append_child("Skin");
	xml_node sprites_of_bones_node = skin_node.append_child("SpritesOfBones");
	for (auto& sprites : sprites_of_bones)
	{
		xml_node sprites_of_bone_node = sprites_of_bones_node.append_child("SpritesOfBone");
		for (auto& sprite : sprites)
		{
			sprite.Save(sprites_of_bone_node, version);
		}
	}
}

void TSkin::Load(const pugi::xml_node& skin_node, const int version, TBaluWorld* world)
{
	xml_node sprites_of_bones_node = skin_node.child("SpritesOfBones");
	for (pugi::xml_node sprites_node = sprites_of_bones_node.first_child(); sprites_node; sprites_node = sprites_node.next_sibling())
	{
		sprites_of_bones.emplace_back();
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			sprites_of_bones.back().emplace_back();
			sprites_of_bones.back().back().Load(sprite_node, version, world);
		}
	}
}

void TSkeleton::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node skeleton_node = parent_node.append_child("Skeleton");
	xml_node bones_node = skeleton_node.append_child("Bones");
	for (auto& v : bones)
	{
		v->Save(bones_node, version, this);
	}
	xml_node skins_node = skeleton_node.append_child("Skins");
	for (auto& v : skins)
	{
		v->Save(skins_node, version);
	}
	skeleton_node.append_attribute("root_node").set_value(root);
}

void TSkeleton::Load(const pugi::xml_node& skeleton_node, const int version, TBaluWorld* world)
{
	if (skeleton_node.first_child())
	{
		root = skeleton_node.attribute("root_node").as_int();
		xml_node bones_node = skeleton_node.child("Bones");
		for (pugi::xml_node prop_node = bones_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
		{
			bones.push_back(std::make_unique<TBone>());
		}
		int i = 0;
		for (pugi::xml_node prop_node = bones_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
		{
			bones[i]->Load(prop_node, version, world, this);
			i++;
		}
		xml_node skins_node = skeleton_node.child("Skins");
		for (pugi::xml_node prop_node = skins_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
		{
			auto temp = std::make_unique<TSkin>();
			temp->Load(prop_node, version, world);
			skins.push_back(std::move(temp));
		}
	}
}

void TProperties::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node props_node = parent_node.append_child("Properties");
	for (auto& v : properties)
	{
		v.second->Save(props_node, version);
		props_node.last_child().append_attribute("name").set_value(v.first.c_str());
	}
}

void TProperties::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
{
	xml_node props_node = instance_node.child("Properties");
	for (pugi::xml_node prop_node = props_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		auto new_prop = PropertiesFactory::Create(prop_node.attribute("type").as_string());
		new_prop->Load(prop_node, version, world);
		auto name = prop_node.attribute("name").as_string();
		properties[name].reset(new_prop);
	}
}

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

	{
		xml_node collide_collbacks = new_node.append_child("CollideScripts");
		for (auto& v : on_collide_callbacks)
		{
			xml_node collide_with = collide_collbacks.append_child("CollideWith");
			collide_with.append_attribute("class").set_value(v.first->GetName().c_str());
			v.second.SaveToXML(collide_with, version);
		}
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

	{
		xml_node collide_collbacks_node = node.child("CollideScripts");
		for (pugi::xml_node collide_collback_node = collide_collbacks_node.first_child(); collide_collback_node; collide_collback_node = collide_collback_node.next_sibling())
		{
			xml_node collide_with_node = collide_collback_node.child("Script");

			TSpecialCallback<CollideCallback> new_callback;
			new_callback.LoadFromXML(collide_with_node, version);

			auto class_name = collide_collback_node.attribute("class").as_string();
			auto collide_with_class = world->GetClass(class_name);
			on_collide_callbacks.push_back(std::make_pair(collide_with_class, new_callback));
		}
	}
}

void TBaluClassSpriteInstance::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node sprite_node = parent_node.append_child("sprite");
	sprite_node.append_attribute("sprite_name").set_value(sprite->GetName().c_str());
	SaveTransformWithScale(sprite_node, "Transform", local);
}

void TBaluClassSpriteInstance::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	sprite = world->GetSprite(node.attribute("sprite_name").as_string());
	local = LoadTransformWithScale(node.child("Transform"));
}

void TBaluClass::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Class");
	new_node.append_attribute("class_name").set_value(class_name.c_str());
	//new_node.append_attribute("layer_name").set_value(layer_name.c_str());
	{
		xml_node sprites_node = new_node.append_child("sprites");
		for (int i = 0; i < sprites.size(); i++)
		{
			sprites[i]->Save(sprites_node, version);
		}
	}

	phys_body.Save(new_node, version);
	skeleton->Save(new_node, version);
	skeleton_animation->Save(new_node, version);
	properties.Save(new_node, version);

	{
		xml_node callbacks_node = new_node.append_child("KeyDownScripts");
		for (auto i = on_key_down_callbacks.begin(); i != on_key_down_callbacks.end(); i++)
		{
			xml_node key_callbacks = callbacks_node.append_child("Key");
			key_callbacks.append_attribute("key").set_value(i->first);
			for (auto& v : i->second)
			{
				v.SaveToXML(key_callbacks, version);
			}
		}

		callbacks_node = new_node.append_child("KeyUpScripts");
		for (auto i = on_key_up_callbacks.begin(); i != on_key_up_callbacks.end(); i++)
		{
			xml_node key_callbacks = callbacks_node.append_child("Key");
			key_callbacks.append_attribute("key").set_value(i->first);
			for (auto& v : i->second)
			{
				v.SaveToXML(key_callbacks, version);
			}
		}

		callbacks_node = new_node.append_child("BeforePhysicsScripts");
		for (auto i = before_physics_callbacks.begin(); i != before_physics_callbacks.end(); i++)
		{
			i->SaveToXML(callbacks_node, version);
		}
	}
}

void TBaluClass::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	class_name = node.attribute("class_name").as_string();
	//layer_name = node.attribute("layer_name").as_string();
	{
		xml_node sprites_node = node.child("sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			TBaluClassSpriteInstance* new_sprite_instance = new TBaluClassSpriteInstance();
			new_sprite_instance->Load(sprite_node, version, world);
			sprites.push_back(std::unique_ptr<TBaluClassSpriteInstance>(new_sprite_instance));
		}
	}
	xml_node phys_body_node = node.child("PhysBody");
	phys_body.Load(phys_body_node, version, world);

	xml_node skeleton_node = node.child("Skeleton");
	skeleton->Load(skeleton_node, version, world);

	xml_node skeleton_animation_node = node.child("SkeletonAnimation");
	skeleton_animation->Load(skeleton_animation_node, version, world);

	properties.Load(node, version, world);

	{
		xml_node child_node = node.child("KeyDownScripts");
		for (pugi::xml_node instance_node = child_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			auto key = (TKey)(instance_node.attribute("key").as_int());
			for (pugi::xml_node callback = instance_node.first_child(); callback; callback = callback.next_sibling())
			{
				TSpecialCallback<KeyUpDownCallback> t;
				t.LoadFromXML(callback, version);
				on_key_down_callbacks[key].push_back(t);
			}
		}
		child_node = node.child("KeyUpScripts");
		for (pugi::xml_node instance_node = child_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			auto key = (TKey)(instance_node.attribute("key").as_int());
			for (pugi::xml_node callback = instance_node.first_child(); callback; callback = callback.next_sibling())
			{
				TSpecialCallback<KeyUpDownCallback> t;
				t.LoadFromXML(callback, version);
				on_key_up_callbacks[key].push_back(t);
			}
		}
		child_node = node.child("BeforePhysicsScripts");
		for (pugi::xml_node instance_node = child_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			TSpecialCallback<BeforePhysicsCallback> t;
			t.LoadFromXML(instance_node, version);
			before_physics_callbacks.push_back(t);
		}
	}
}

void TBaluScene::TClassInstance::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Instance");
	//new_node.append_attribute("name").set_value(name.c_str());
	new_node.append_attribute("class_name").set_value(balu_class->GetName().c_str());
	SaveTransformWithScale(new_node, "Transform", transform);
}

void TBaluScene::TClassInstance::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
{
	//name = instance_node.attribute("name").as_string();
	balu_class = world->GetClass(instance_node.attribute("class_name").as_string());
	transform = LoadTransformWithScale(instance_node.child("Transform"));
}

void TViewport::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node viewport_node = parent_node.append_child("Viewport");
	SaveTransform(viewport_node, "transform", transform);
	viewport_node.append_attribute("aspect").set_value(aspect);
	viewport_node.append_attribute("width").set_value(width);
}

void TViewport::Load(const pugi::xml_node& viewport_node, const int version, TBaluWorld* world)
{
	LoadTransform(viewport_node.child("transform"));
	aspect = viewport_node.attribute("aspect").as_float();
	width = viewport_node.attribute("width").as_float();
}

void TBaluScene::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Scene");
	new_node.append_attribute("name").set_value(scene_name.c_str());
	{
		xml_node instances_node = new_node.append_child("instances");
		for (int i = 0; i < instances.size(); i++)
		{
			EngineInterface::PropertyType type;
			if (instances[i]->GetClass()->GetProperties()->HasProperty("editor_temp_object", type))
				continue;
			instances[i]->Save(instances_node, version);
		}
	}
	xml_node viewports_node = new_node.append_child("Viewports");
	{
		for (auto& v : viewports)
		{
			v.second.Save(viewports_node, version);
			viewports_node.last_child().append_attribute("name").set_value(v.first.c_str());
		}
	}
	//TODO TLayersManager layers;
	properties.Save(new_node, version);
}

void TBaluScene::Load(const pugi::xml_node& scene_node, const int version, TBaluWorld* world)
{
	this->world = world;
	scene_name = scene_node.attribute("name").as_string();
	{
		xml_node instances_node = scene_node.child("instances");
		for (pugi::xml_node instance_node = instances_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			TBaluScene::TClassInstance* new_instance = new TBaluScene::TClassInstance();
			new_instance->Load(instance_node, version, world);
			instances.push_back(std::unique_ptr<TBaluScene::TClassInstance>(new_instance));
		}
	}
	{
		xml_node viewports_node = scene_node.child("Viewports");
		for (pugi::xml_node instance_node = viewports_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			TViewport temp;
			temp.Load(instance_node, version, world);
			viewports.insert(std::make_pair(instance_node.attribute("name").as_string(), temp));
		}
	}
	//TODO TLayersManager layers;
	properties.Load(scene_node, version, world);
}

void TBaluWorld::SaveToXML(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("World");
	{
		xml_node materials_node = new_node.append_child("Materials");
		for (auto i = materials.begin(); i != materials.end(); i++)
		{
			i->second->Save(materials_node, version);
		}
	}
	{
		xml_node sprites_node = new_node.append_child("Sprites");
		for (auto i = sprites.begin(); i != sprites.end(); i++)
		{
			EngineInterface::PropertyType type;
			if (i->second->GetProperties()->HasProperty("editor_temp_object", type))
				continue;
			i->second->Save(sprites_node, version);
		}
	}
	{
		xml_node classes_node = new_node.append_child("Classes");
		for (auto i = classes.begin(); i != classes.end(); i++)
		{
			EngineInterface::PropertyType type;
			if (i->second->GetProperties()->HasProperty("editor_temp_object", type))
				continue;
			i->second->Save(classes_node, version);
		}
	}
	{
		xml_node scenes_node = new_node.append_child("Scenes");
		for (auto i = scenes.begin(); i != scenes.end(); i++)
		{
			EngineInterface::PropertyType type;
			if (i->second->GetProperties()->HasProperty("editor_temp_object", type))
				continue;
			i->second->Save(scenes_node, version);
		}
	}

	{
		xml_node callbacks_node = new_node.append_child("MouseDownScripts");
		for (auto& v : mouse_down_callbacks)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
	{
		xml_node callbacks_node = new_node.append_child("MouseUpScripts");
		for (auto& v : mouse_up_callbacks)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
	{
		xml_node callbacks_node = new_node.append_child("MouseMoveScripts");
		for (auto& v : mouse_move_callbacks)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
	{
		xml_node callbacks_node = new_node.append_child("StartWorldScripts");
		for (auto& v : on_start_world_callback)
		{
			v.SaveToXML(callbacks_node, version);
		}
		callbacks_node = new_node.append_child("ViewportResizeScripts");
		for (auto& v : viewport_resize_callback)
		{
			v.SaveToXML(callbacks_node, version);
		}
	}
}

void TBaluWorld::LoadFromXML(const pugi::xml_node& document_node, const int version)
{
	xml_node world_node = document_node.child("World");
	{
		xml_node materials_node = world_node.child("Materials");
		for (pugi::xml_node material = materials_node.first_child(); material; material = material.next_sibling())
		{
			TBaluMaterial* new_material=new TBaluMaterial();
			new_material->Load(material, version, this);
			materials[new_material->GetName()].reset(new_material);
		}
	}
	//предварительно создаем классы, т.к. их имена используются в sprite OnCollide
	{
		xml_node classes_node = world_node.child("Classes");
		for (pugi::xml_node class_node = classes_node.first_child(); class_node; class_node = class_node.next_sibling())
		{
			std::string class_name = class_node.attribute("class_name").as_string();
			classes.emplace(class_name, std::make_unique<TBaluClass>(class_name.c_str(), this));
		}
	}
	{
		xml_node sprites_node = world_node.child("Sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			TBaluSprite* sprite = new TBaluSprite();
			sprite->Load(sprite_node, version, this);
			sprites[sprite->GetName()].reset(sprite);
		}
	}
	//загружаем классы полностью
	{
		xml_node classes_node = world_node.child("Classes");
		auto curr_class = classes.begin();
		for (pugi::xml_node class_node = classes_node.first_child(); class_node; class_node = class_node.next_sibling())
		{
			curr_class->second->Load(class_node, version, this);
			curr_class++;
		}
	}
	{
		xml_node scenes_node = world_node.child("Scenes");
		for (pugi::xml_node scene_node = scenes_node.first_child(); scene_node; scene_node = scene_node.next_sibling())
		{
			TBaluScene* scene = new TBaluScene();
			scene->Load(scene_node, version, this);
			scenes[scene->GetName()].reset(scene);
		}
	}

	{
		xml_node callbacks_node = world_node.child("MouseDownScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TSpecialCallback<MouseCallback> new_callback;
			new_callback.LoadFromXML(callback_node, version);
			mouse_down_callbacks.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("MouseUpScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TSpecialCallback<MouseCallback> new_callback;
			new_callback.LoadFromXML(callback_node, version);
			mouse_up_callbacks.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("MouseMoveScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TSpecialCallback<MouseCallback> new_callback;
			new_callback.LoadFromXML(callback_node, version);
			mouse_move_callbacks.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("StartWorldScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TSpecialCallback<OnStartWorldCallback> new_callback;
			new_callback.LoadFromXML(callback_node, version);
			on_start_world_callback.push_back(new_callback);
		}
	}
	{
		xml_node callbacks_node = world_node.child("ViewportResizeScripts");
		for (pugi::xml_node callback_node = callbacks_node.first_child(); callback_node; callback_node = callback_node.next_sibling())
		{
			TSpecialCallback<ViewportResizeCallback> new_callback;
			new_callback.LoadFromXML(callback_node, version);
			viewport_resize_callback.push_back(new_callback);
		}
	}
}

void TCallback::SaveToXML(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Script");
	new_node.append_attribute("callback_type").set_value(callback_type);

	xml_node ndAvatarData = new_node.append_child(pugi::node_pcdata);
	ndAvatarData.set_value(script_source.c_str());
}

void TCallback::LoadFromXML(const pugi::xml_node& document_node, const int version)
{
	callback_type = document_node.attribute("callback_type").as_int();
	script_source = document_node.child_value();
}