#include "IClass.h"

#include <Common/SerializeCommon.h>

#include "../../IWorld.h"

using namespace EngineInterface;

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
		auto temp = std::unique_ptr<TTrack>(new TTrack());
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
		auto temp = std::unique_ptr<TTimeLine>(new TTimeLine());
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


void TBaluTransformedSprite::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node sprite_node = parent_node.append_child("sprite");
	sprite_node.append_attribute("name").set_value(sprite->GetName().c_str());
	SaveTransformWithScale(sprite_node, "Transform", local);
}

void TBaluTransformedSprite::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	sprite = dynamic_cast<TBaluSprite*>(world->GetObjectByName(TWorldObjectType::Sprite, node.attribute("name").as_string()));
	local = LoadTransformWithScale(node.child("Transform"));
}

void TBaluClass::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Class");
	new_node.append_attribute("name").set_value(name.c_str());
	//new_node.append_attribute("name").set_value(layer_name.c_str());
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
		//xml_node callbacks_node = new_node.append_child("KeyDownScripts");
		//for (auto i = on_key_down_callbacks.begin(); i != on_key_down_callbacks.end(); i++)
		//{
		//	xml_node key_callbacks = callbacks_node.append_child("Key");
		//	key_callbacks.append_attribute("key").set_value(i->first);
		//	for (auto& v : i->second)
		//	{
		//		v.SaveToXML(key_callbacks, version);
		//	}
		//}

		//callbacks_node = new_node.append_child("KeyUpScripts");
		//for (auto i = on_key_up_callbacks.begin(); i != on_key_up_callbacks.end(); i++)
		//{
		//	xml_node key_callbacks = callbacks_node.append_child("Key");
		//	key_callbacks.append_attribute("key").set_value(i->first);
		//	for (auto& v : i->second)
		//	{
		//		v.SaveToXML(key_callbacks, version);
		//	}
		//}

		//callbacks_node = new_node.append_child("BeforePhysicsScripts");
		//for (auto i = before_physics_callbacks.begin(); i != before_physics_callbacks.end(); i++)
		//{
		//	i->SaveToXML(callbacks_node, version);
		//}

		//callbacks_node = new_node.append_child("CollideScripts");
		//for (auto& v : on_collide_callbacks)
		//{
		//	xml_node collide_with = callbacks_node.append_child("CollideWith");
		//	collide_with.append_attribute("class").set_value(v.with_class->GetName().c_str());
		//	collide_with.append_attribute("sprite").set_value(v.sprite->GetName().c_str());
		//	v.script.SaveToXML(collide_with, version);
		//}
	}
}

void TBaluClass::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	name = node.attribute("name").as_string();
	//layer_name = node.attribute("name").as_string();
	{
		xml_node sprites_node = node.child("sprites");
		for (pugi::xml_node sprite_node = sprites_node.first_child(); sprite_node; sprite_node = sprite_node.next_sibling())
		{
			TBaluTransformedSprite* new_sprite_instance = new TBaluTransformedSprite();
			new_sprite_instance->Load(sprite_node, version, world);
			sprites.push_back(std::unique_ptr<TBaluTransformedSprite>(new_sprite_instance));
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
		/*xml_node child_node = node.child("KeyDownScripts");
		for (pugi::xml_node instance_node = child_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			auto key = (TKey)(instance_node.attribute("key").as_int());
			for (pugi::xml_node callback = instance_node.first_child(); callback; callback = callback.next_sibling())
			{
				TScript t;
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
				TScript t;
				t.LoadFromXML(callback, version);
				on_key_up_callbacks[key].push_back(t);
			}
		}
		child_node = node.child("BeforePhysicsScripts");
		for (pugi::xml_node instance_node = child_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			TScript t;
			t.LoadFromXML(instance_node, version);
			before_physics_callbacks.push_back(t);
		}

		{
			xml_node collide_collbacks_node = node.child("CollideScripts");
			for (pugi::xml_node collide_collback_node = collide_collbacks_node.first_child(); collide_collback_node; collide_collback_node = collide_collback_node.next_sibling())
			{
				xml_node collide_with_node = collide_collback_node.child("Script");

				TScript new_callback;
				new_callback.LoadFromXML(collide_with_node, version);

				auto class_name = collide_collback_node.attribute("class").as_string();
				auto sprite_name = collide_collback_node.attribute("sprite").as_string();

				auto collide_with_class = dynamic_cast<TBaluClass*>(world->GetObjectByName(TWorldObjectType::Class, class_name));
				auto collide_sprite = dynamic_cast<TBaluSprite*>(world->GetObjectByName(TWorldObjectType::Sprite, sprite_name));

				on_collide_callbacks.push_back(TSpriteWithClassCollide(collide_sprite, collide_with_class, new_callback));
			}
		}*/
	}
}
