#include "Class.h"

#include <pugixml.hpp>

#include "../Common/SerializeCommon.h"

using namespace pugi;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace BaluLib;

void TClassPhysBody::Save(pugi::xml_node& parent_node, const int version)const
{
	auto phys_Body_node = parent_node.append_child("PhysBody");
	TProperties::SaveProperties(phys_Body_node, version);
}

void TClassPhysBody::Load(const pugi::xml_node& phys_body_node, const int version, IWorld* world)
{
	TProperties::LoadProperties(phys_body_node, version);
}

void TTrackFrame_Save(const TTrackFrame& obj, pugi::xml_node& parent_node, const int version)
{
	auto frame_node = parent_node.append_child("Frame");
	frame_node.append_attribute("time").set_value(obj.time);
	frame_node.append_attribute("rotation").set_value(obj.rotation);
}

void TTrackFrame_Load(TTrackFrame& obj, const pugi::xml_node& frame_node, const int version, IWorld* world)
{
	obj.time = frame_node.attribute("time").as_float();
	obj.rotation = frame_node.attribute("rotation").as_float();
}


void TTrack::Save(pugi::xml_node& parent_node, const int version, ISkeleton* skeleton)
{
	auto track_node = parent_node.append_child("Track");
	track_node.append_attribute("bone_id").set_value(skeleton->GetBoneIndex(bone));
	auto tracks_node = track_node.append_child("Frames");
	for (auto& frame : frames)
	{
		TTrackFrame_Save(frame, tracks_node, version);
	}
}

void TTrack::Load(const pugi::xml_node& track_node, const int version, IWorld* world, ISkeleton* skeleton)
{
	bone = skeleton->GetBone(track_node.attribute("bone_id").as_int());
	auto tracks_node = track_node.child("Frames");
	for (pugi::xml_node prop_node = tracks_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		TTrackFrame frame;
		TTrackFrame_Load(frame, prop_node, version, world);
		frames.insert(frame);
	}
}

void TTimeLine::Save(pugi::xml_node& parent_node, const int version, ISkeleton* skeleton)
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

void TTimeLine::Load(const pugi::xml_node& timeline_node, const int version, IWorld* world, ISkeleton* skeleton)
{
	name = timeline_node.attribute("name").as_string();
	timeline_size = timeline_node.attribute("timeline_size").as_float();

	auto tracks_node = timeline_node.child("Tracks");
	for (pugi::xml_node prop_node = tracks_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		auto temp = std::unique_ptr<TTrack>(new TTrack());
		temp->Load(prop_node, version, world, skeleton);
		tracks.push_back(std::move(temp));
	}
}


void TSkeletonAnimation::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node skeleton_animation_node = parent_node.append_child("SkeletonAnimation");
	xml_node animations_node = skeleton_animation_node.append_child("Animations");
	for (auto& v : animations)
	{
		v->Save(animations_node, version, skeleton);
	}
}

void TSkeletonAnimation::Load(const pugi::xml_node& skel_animation_node, const int version, IWorld* world)
{
	auto animation_node = skel_animation_node.child("Animations");
	for (pugi::xml_node prop_node = animation_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		auto temp = std::unique_ptr<TTimeLine>(new TTimeLine());
		temp->Load(prop_node, version, world, skeleton);
		animations.push_back(std::move(temp));
	}
}

void TBone::Save(pugi::xml_node& parent_node, const int version, const TSkeleton* skeleton)const
{
	xml_node bone_node = parent_node.append_child("Bone");

	bone_node.append_attribute("id").set_value(skeleton->GetBoneIndex(this));

	if (parent != nullptr)
		bone_node.append_attribute("parent_id").set_value(skeleton->GetBoneIndex(parent));
	else
		bone_node.append_attribute("parent_id").set_value(-1);

	SerializeCommon::SaveTransform(bone_node, "LocalTransform", local);

	xml_node children_node = bone_node.append_child("Children");
	for (auto& v : children)
	{
		xml_node child_node = children_node.append_child("Child");
		child_node.append_attribute("Id").set_value(skeleton->GetBoneIndex(v));
	}
}

void TBone::Load(const pugi::xml_node& bone_node, const int version, IWorld* world, TSkeleton* skeleton)
{
	auto parent_id = bone_node.attribute("parent_id").as_int();
	if (parent_id == -1)
		parent = nullptr;
	else
		parent = skeleton->GetBone(parent_id);

	local = SerializeCommon::LoadTransform(bone_node.child("LocalTransform"));

	xml_node children_node = bone_node.child("Children");
	for (pugi::xml_node prop_node = children_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
	{
		children.push_back(skeleton->GetBone(prop_node.attribute("Id").as_int()));
	}
}

void TSkin::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node skin_node = parent_node.append_child("Skin");
	xml_node sprites_of_bones_node = skin_node.append_child("SpritesOfBones");
	for (auto& sprites : sprites_of_bones)
	{
		xml_node sprites_of_bone_node = sprites_of_bones_node.append_child("SpritesOfBone");
		for (auto& sprite : sprites)
		{
			sprite->Save(sprites_of_bone_node, version);
		}
	}
}

void TSkin::Load(const pugi::xml_node& skin_node, const int version, IWorld* world)
{
	xml_node sprites_of_bones_node = skin_node.child("SpritesOfBones");
	for (pugi::xml_node sprites_node = sprites_of_bones_node.first_child(); sprites_node; sprites_node = sprites_node.next_sibling())
	{
		sprites_of_bones.emplace_back();
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			sprites_of_bones.back().emplace_back();
			auto new_sprite = new TTransformedSprite();
			new_sprite->Load(sprite_node, version, world);
			sprites_of_bones.back().back().reset(new_sprite);				
		}
	}
}

void TSkeleton::Save(pugi::xml_node& parent_node, const int version)const
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

void TSkeleton::Load(const pugi::xml_node& skeleton_node, const int version, IWorld* world)
{
	if (skeleton_node.first_child())
	{
		root = skeleton_node.attribute("root_node").as_int();
		xml_node bones_node = skeleton_node.child("Bones");
		for (pugi::xml_node prop_node = bones_node.first_child(); prop_node; prop_node = prop_node.next_sibling())
		{
			bones.push_back(std::unique_ptr<TBone>(new TBone()));
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
			auto temp = std::unique_ptr<TSkin>(new TSkin());
			temp->Load(prop_node, version, world);
			skins.push_back(std::move(temp));
		}
	}
}


void TTransformedSprite::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node sprite_node = parent_node.append_child("sprite");
	sprite_node.append_attribute("name").set_value(sprite->GetName().c_str());
	SerializeCommon::SaveTransformWithScale(sprite_node, "Transform", local);
}

void TTransformedSprite::Load(const pugi::xml_node& node, const int version, IWorld* world)
{
	auto obj = world->GetObjectByName(TWorldObjectType::Sprite, node.attribute("name").as_string());
	sprite = dynamic_cast<TSprite*>(obj);
	local = SerializeCommon::LoadTransformWithScale(node.child("Transform"));
}

void TClass::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node new_node = parent_node.append_child("Class");
	new_node.append_attribute("name").set_value(GetName().c_str());

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

	SaveProperties(new_node, version);

	GetProperties()->Save(new_node, version);
}

void TClass::Load(const pugi::xml_node& node, const int version, IWorld* world)
{
	LoadProperties(node, version);

	GetProperties()->Load(node, version, world);

	{
		xml_node sprites_node = node.child("sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			TTransformedSprite* new_sprite_instance = new TTransformedSprite();
			new_sprite_instance->Load(sprite_node, version, world);
			sprites.push_back(std::unique_ptr<TTransformedSprite>(new_sprite_instance));
		}
	}
	xml_node phys_body_node = node.child("PhysBody");
	phys_body.Load(phys_body_node, version, world);

	xml_node skeleton_node = node.child("Skeleton");
	skeleton->Load(skeleton_node, version, world);

	xml_node skeleton_animation_node = node.child("SkeletonAnimation");
	skeleton_animation->Load(skeleton_animation_node, version, world);
}

void TTransformedClass::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node new_node = parent_node.append_child("ClassInstance");

	new_node.append_attribute("class_name").set_value(balu_class->GetName().c_str());
	SerializeCommon::SaveTransformWithScale(new_node, "Transform", transform);
}

void TTransformedClass::Load(const pugi::xml_node& instance_node, const int version, IWorld* world)
{
	balu_class = dynamic_cast<TClass*>(world->GetObjectByName(TWorldObjectType::Class, instance_node.attribute("class_name").as_string()));
	transform = SerializeCommon::LoadTransformWithScale(instance_node.child("Transform"));
}
