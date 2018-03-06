#pragma once

#include <Common/Director.h>

#include <Render/DrawingHelper.h>

using namespace BaluEngine;

char* PlayerJump_source = //(IBaluTransformedClassInstance object)
"	if (object.GetProperties().GetBool(\"can_jump\"))\n"
"	{\n"
"		vec2 speed = object.GetPhysBody().GetLinearVelocity();\n"
"		speed.y = 4;\n"
"		object.GetPhysBody().SetLinearVelocity(speed);\n"
"	}\n";

char* PlayerLeft_source = //(void* user_data, IBaluTransformedClassInstance* object)
"	float mult = 0.8;\n"
"	if(object.GetProperties().GetBool(\"can_jump\")) mult = 1;\n"
"	vec2 speed = object.GetPhysBody().GetLinearVelocity();\n"
"	speed.x = -1.4*mult;\n"
"	object.GetPhysBody().SetLinearVelocity(speed);\n";

char* PlayerRight_source = //(void* user_data, IBaluTransformedClassInstance* object)
"	float mult = 0.8;\n"
"	if(object.GetProperties().GetBool(\"can_jump\")) mult = 1;\n"
"	vec2 speed = object.GetPhysBody().GetLinearVelocity();\n"
"	speed.x = 1.4*mult;\n"
"	object.GetPhysBody().SetLinearVelocity(speed);\n";

char* PlayerJumpSensorCollide_source = //(TCallbackData* callback, EngineInterface::IBaluPhysShapeInstance* source, EngineInterface::IBaluTransformedClassInstance* obstacle)
"	object.GetProperties().SetBool(\"can_jump\", true);\n";

char* PlayerPrePhysStep_source = //(void* user_data, IBaluTransformedClassInstance* object)
"	PropertyType type;\n"
"	if (!object.GetProperties().HasProperty(\"can_jump\", type))\n"
"		object.GetProperties().SetBool(\"can_jump\", false);\n"
"	bool can_jump = object.GetProperties().GetBool(\"can_jump\");\n"
"	vec2 speed = object.GetPhysBody().GetLinearVelocity();\n"
"	string hor_anim, v_anim;\n"
"	if (speed.x > 0)\n"
"		hor_anim = \"_right\";\n"
"	else\n"
"		hor_anim = \"_left\";\n"
"	if (can_jump)\n"
"	{\n"
"		if (Abs(speed.x) > 0.5)\n"
"			v_anim = \"run\";\n"
"		else\n"
"			v_anim = \"stay\";\n"
"	}\n"
"	else\n"
"	{\n"
"		if (speed.y > 0)\n"
"			v_anim = \"jump_up\";\n"
"		else\n"
"			v_anim = \"jump_down\";\n"
"	}\n"
"	object.GetSprite(0).GetPolygon().SetActiveAnimation(v_anim + hor_anim);\n"
"	object.GetProperties().SetBool(\"can_jump\", false);\n";

char* BonesPlayerPrePhysStep_source = //(void* user_data, IBaluTransformedClassInstance* object)
"	vec2 speed = object.GetPhysBody().GetLinearVelocity();\n"
"	if (Abs(speed[0]) > 0)\n"
"		object.GetSkeletonAnimation().PlayAnimation(\"walk\", 1);\n"
"	else\n"
"		object.GetSkeletonAnimation().StopAnimation(\"walk\");\n";

char* ViewportResize_source = //(IDirector director, vec2i old_size, vec2i new_size)
"	vec2 k = vec2(new_size[0], new_size[1]) / vec2(old_size[0], old_size[1]);\n"
"	IViewport main_viewport = director.GetWorldInstance().GetSceneInstance(0).GetSource().FindViewport(\"main_viewport\");\n"
"	vec2 old_vieport_size = main_viewport.GetSize();\n"
"	vec2 new_vieport_size = old_vieport_size*k;\n"
"	main_viewport.SetSize(new_vieport_size);\n";

char* WorldStart_source = //(IWorldInstance world_instance, IComposer composer)
"	IScene scene = world_instance.GetSource().GetScene(\"scene0\");\n"
"	ISceneInstance scene_instance = world_instance.RunScene(scene);\n"
"	composer.AddToRender(scene_instance, scene.FindViewport(\"main_viewport\"));\n";

WorldDef::IWorld* CreateDemoWorld(std::string assets_dir)
{
	using namespace WorldDef;
	using namespace BaluLib;

	auto world = CreateWorld();

	world->GetEventsEditor()->GlobalInsert(GlobalCallbackType::WorldStart, -1, TScript(WorldStart_source));
	world->GetEventsEditor()->GlobalInsert(GlobalCallbackType::ViewportResize, -1, TScript(ViewportResize_source));

	auto brick_mat = dynamic_cast<IMaterial*>(world->CreateObject(TWorldObjectType::Material, "brick"));

	brick_mat->SetImagePath("\\textures\\brick.png");
	brick_mat->SetColor(TVec4(1, 1, 1, 1));

	auto box_sprite = dynamic_cast<ISprite*>(world->CreateObject(TWorldObjectType::Sprite, "box0"));
	box_sprite->GetPolygon()->SetMaterial(brick_mat);
	//box_sprite->GetPolygon()->SetAsBox(1, 1);
	box_sprite->GetPolygon()->SetPolygonFromTexture(assets_dir);
	box_sprite->GetPolygon()->SetTexCoordsFromVertices(TVec2(-0.5, -0.5), TVec2(1, 1));
	box_sprite->SetPhysShape(GetPhysShapeFactory()->CreateBoxShape(1, 1)->GetPhysShape());

	auto box_class = world->CreateClass("box");
	auto box_class_instance = box_class->AddSprite(box_sprite);
	box_class->GetPhysBody()->SetEnabled(true);
	box_class->GetPhysBody()->SetPhysBodyType(TPhysBodyType::Static);

	auto box_class_dyn = world->CreateClass("box_dyn");
	auto box_class_instance_dyn = box_class_dyn->AddSprite(box_sprite);
	box_class_dyn->GetPhysBody()->SetEnabled(true);
	box_class_dyn->GetPhysBody()->SetPhysBodyType(TPhysBodyType::Dynamic);

	auto player_mat = world->CreateMaterial("player_skin");
	player_mat->SetImagePath("\\textures\\player.png");
	auto player_sprite = world->CreateSprite("player");

	player_sprite->GetPolygon()->SetMaterial(player_mat);
	//player_sprite->GetPolygon()->SetAsBox(20.0/8, 20.0/8);
	player_sprite->GetPolygon()->SetAsBox(6, 6);
	//player_sprite->GetPolygon()->SetPolygonFromTexture();
	//player_sprite->GetPolygon()->SetTexCoordsFromVertices(TVec2(0, 0), TVec2(1, 1));
	player_sprite->SetPhysShape(GetPhysShapeFactory()->CreateCircleShape(2.5, TVec2(0,0))->GetPhysShape());
	//player_sprite->SetPhysShape(new TBaluBoxShape(0.5,2));

	auto grid_frames = IAnimDesc::Create_TGridFrames(TVec2(0, 0), TVec2(1, 1), 8, 4);

	player_sprite->GetPolygon()->AddAnimDesc(grid_frames);

	player_sprite->GetPolygon()->CreateAnimationLine("run_right", grid_frames, TFramesRange(0, 7).ToFramesArray());
	player_sprite->GetPolygon()->CreateAnimationLine("jump_up_right", grid_frames, TFramesRange(9, 9).ToFramesArray());
	player_sprite->GetPolygon()->CreateAnimationLine("jump_down_right", grid_frames, TFramesRange(10, 10).ToFramesArray());
	player_sprite->GetPolygon()->CreateAnimationLine("stay_right", grid_frames, TFramesRange(11, 11).ToFramesArray());
	player_sprite->GetPolygon()->CreateAnimationLine("run_right", grid_frames, TFramesRange(0, 7).ToFramesArray());
	player_sprite->GetPolygon()->CreateAnimationLine("run_left", grid_frames, TFramesRange(16, 16 + 7).ToFramesArray());
	player_sprite->GetPolygon()->CreateAnimationLine("jump_up_left", grid_frames, TFramesRange(16 + 7 + 2, 16 + 7 + 2).ToFramesArray());
	player_sprite->GetPolygon()->CreateAnimationLine("jump_down_left", grid_frames, TFramesRange(16 + 7 + 3, 16 + 7 + 3).ToFramesArray());
	player_sprite->GetPolygon()->CreateAnimationLine("stay_left", grid_frames, TFramesRange(16 + 7 + 4, 16 + 7 + 4).ToFramesArray());

	auto player_class = world->CreateClass("player");
	auto player_class_instance = player_class->AddSprite(player_sprite);
	player_class->GetPhysBody()->SetEnabled(true);
	player_class->GetPhysBody()->SetPhysBodyType(TPhysBodyType::Dynamic);
	player_class->GetPhysBody()->SetFixedRotation(true);

	auto player_phys_sprite = world->CreateSprite("player_phys");
	auto player_phys_sprite_instance = player_class->AddSprite(player_phys_sprite);
	player_phys_sprite->SetPhysShape(GetPhysShapeFactory()->CreateCircleShape(0.4, TVec2(0, -3.5))->GetPhysShape());
	player_phys_sprite->GetPhysShape()->SetIsSensor(true);

	world->GetEventsEditor()->ClassKeyInsert(ClassKeyCallbackType::KeyDown, TKey::Up, player_class->GetName(), -1, TScript(PlayerJump_source));
	world->GetEventsEditor()->ClassKeyInsert(ClassKeyCallbackType::KeyDown, TKey::Left, player_class->GetName(), -1, TScript(PlayerLeft_source));
	world->GetEventsEditor()->ClassKeyInsert(ClassKeyCallbackType::KeyDown, TKey::Right, player_class->GetName(), -1, TScript(PlayerRight_source));

	player_class->GetProperties()->SetBool("can_jump", false);

	world->GetEventsEditor()->ClassInsert(ClassCallbackType::BeforePhysics, player_class->GetName(), -1, TScript(PlayerPrePhysStep_source));
	world->GetEventsEditor()->OnCollideInsert(-1, player_class->GetName(), 0, box_class->GetName(), TScript(PlayerJumpSensorCollide_source));

	auto bones_player = world->CreateClass("bones");

	world->GetEventsEditor()->ClassInsert(ClassCallbackType::BeforePhysics, bones_player->GetName(), -1, TScript(BonesPlayerPrePhysStep_source));

	{
		auto bones_mat = world->CreateMaterial("zombie");

		bones_mat->SetImagePath("\\textures\\zombie.png");
		bones_mat->SetColor(TVec4(1, 1, 1, 1));

		//special phys sprite
		auto bones_phys_sprite = world->CreateSprite("bones_phys_sprite");
		bones_phys_sprite->SetPhysShape(GetPhysShapeFactory()->CreateCircleShape(1.0, TVec2(0, -1.5))->GetPhysShape());
		bones_phys_sprite->GetPolygon()->SetEnabled(false);

		auto bones_player_class_instance = bones_player->AddSprite(bones_phys_sprite);
		bones_player->GetPhysBody()->SetEnabled(true);
		bones_player->GetPhysBody()->SetPhysBodyType(TPhysBodyType::Dynamic);
		bones_player->GetPhysBody()->SetFixedRotation(true);

		//sprites
		auto bones_head = world->CreateSprite("bones_head");
		bones_head->GetPolygon()->SetMaterial(bones_mat);
		bones_head->GetPolygon()->SetAsBox(2, 2);
		bones_head->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(0, 256 - 256) / 256, TVec2(73, 256 - 192) / 256);

		auto bones_torso = world->CreateSprite("bones_torso");
		bones_torso->GetPolygon()->SetMaterial(bones_mat);
		bones_torso->GetPolygon()->SetAsBox(1.6, 2.5);
		bones_torso->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(0, 256 - 189) / 256, TVec2(53, 256 - 112) / 256);

		//hands

		auto bones_left_shoulder = world->CreateSprite("bones_left_shoulder");
		bones_left_shoulder->GetPolygon()->SetMaterial(bones_mat);
		bones_left_shoulder->GetPolygon()->SetAsBox(1, 1);
		bones_left_shoulder->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(113, 256 - 190) / 256, TVec2(152, 256 - 142) / 256);

		auto bones_left_hand = world->CreateSprite("bones_left_hand");
		bones_left_hand->GetPolygon()->SetMaterial(bones_mat);
		bones_left_hand->GetPolygon()->SetAsBox(1, 1);
		bones_left_hand->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(75, 256 - 256) / 256, TVec2(138, 256 - 193) / 256);

		auto bones_right_shoulder = world->CreateSprite("bones_right_shoulder");
		bones_right_shoulder->GetPolygon()->SetMaterial(bones_mat);
		bones_right_shoulder->GetPolygon()->SetAsBox(1, 1);
		bones_right_shoulder->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(152, 256 - 192) / 256, TVec2(183, 256 - 143) / 256);

		auto bones_right_hand = world->CreateSprite("bones_right_hand");
		bones_right_hand->GetPolygon()->SetMaterial(bones_mat);
		bones_right_hand->GetPolygon()->SetAsBox(1, 1);
		bones_right_hand->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(58, 256 - 190) / 256, TVec2(113, 256 - 129) / 256);

		//legs

		auto bones_left_leg = world->CreateSprite("bones_left_leg");
		bones_left_leg->GetPolygon()->SetMaterial(bones_mat);
		bones_left_leg->GetPolygon()->SetAsBox(1, 1);
		bones_left_leg->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(55, 256 - 72) / 256, TVec2(94, 256 - 14) / 256);

		auto bones_left_foot = world->CreateSprite("bones_left_foot");
		bones_left_foot->GetPolygon()->SetMaterial(bones_mat);
		bones_left_foot->GetPolygon()->SetAsBox(1, 1);
		bones_left_foot->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(54, 256 - 131) / 256, TVec2(94, 256 - 75) / 256);

		auto bones_right_leg = world->CreateSprite("bones_right_leg");
		bones_right_leg->GetPolygon()->SetMaterial(bones_mat);
		bones_right_leg->GetPolygon()->SetAsBox(1, 1);
		bones_right_leg->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(0, 256 - 55) / 256, TVec2(44, 256 - 7) / 256);

		auto bones_right_foot = world->CreateSprite("bones_right_foot");
		bones_right_foot->GetPolygon()->SetMaterial(bones_mat);
		bones_right_foot->GetPolygon()->SetAsBox(1, 1);
		bones_right_foot->GetPolygon()->SetTexCoordsFromVerticesByRegion(TVec2(9, 256 - 112) / 256, TVec2(39, 256 - 56) / 256);

		auto bones_player_skel = bones_player->GetSkeleton();

		//bones
		auto root_bone = bones_player_skel->CreateBone(nullptr);

		auto right_leg_bone = bones_player_skel->CreateBone(root_bone);
		right_leg_bone->SetTransform(TTransform(TVec2(-0.5, -1.2), TRot(0)));
		auto right_foot_bone = bones_player_skel->CreateBone(right_leg_bone);
		right_foot_bone->SetTransform(TTransform(TVec2(0, -1.0), TRot(0)));

		auto left_leg_bone = bones_player_skel->CreateBone(root_bone);
		left_leg_bone->SetTransform(TTransform(TVec2(0.5, -1.2), TRot(0)));
		auto left_foot_bone = bones_player_skel->CreateBone(left_leg_bone);
		left_foot_bone->SetTransform(TTransform(TVec2(0.0, -1.0), TRot(0)));

		auto right_shoulder_bone = bones_player_skel->CreateBone(root_bone);
		auto right_hand_bone = bones_player_skel->CreateBone(right_shoulder_bone);

		auto left_shoulder_bone = bones_player_skel->CreateBone(root_bone);
		auto left_hand_bone = bones_player_skel->CreateBone(left_shoulder_bone);

		//create skin
		auto skin = bones_player_skel->CreateSkin();
		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(root_bone), bones_head, TTransform(TVec2(-0.3, 2.0), TRot(0)));

		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(root_bone), bones_torso, TTransform(TVec2(0, 0), TRot(0)));

		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(right_leg_bone), bones_right_leg, TTransform(TVec2(0, -0.5), TRot(0)));
		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(right_foot_bone), bones_right_foot, TTransform(TVec2(0, -0.5), TRot(0)));

		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(left_leg_bone), bones_left_leg, TTransform(TVec2(0, -0.5), TRot(0)));
		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(left_foot_bone), bones_left_foot, TTransform(TVec2(0, -0.5), TRot(0)));

		//walk animation
		auto skel_anim = bones_player->GetSkeletonAnimation();

		auto walk_anim = skel_anim->CreateAnimation("walk");
		float timeline_size = 0.5;
		walk_anim->SetTimelineSize(timeline_size);
		auto left_leg_bone_track = walk_anim->CreateTrack(left_leg_bone);

		left_leg_bone_track->CreateFrame(0, 0);
		left_leg_bone_track->CreateFrame(0.25* timeline_size, DegToRad(40.0));
		left_leg_bone_track->CreateFrame(0.75* timeline_size, DegToRad(-40.0));

		auto left_foot_bone_track = walk_anim->CreateTrack(left_foot_bone);

		left_foot_bone_track->CreateFrame(0, 0);
		left_foot_bone_track->CreateFrame(0.25* timeline_size, DegToRad(40.0));
		left_foot_bone_track->CreateFrame(0.75* timeline_size, DegToRad(-40.0));

		auto right_leg_bone_track = walk_anim->CreateTrack(right_leg_bone);

		right_leg_bone_track->CreateFrame(0, 0);
		right_leg_bone_track->CreateFrame(0.25* timeline_size, DegToRad(-40.0));
		right_leg_bone_track->CreateFrame(0.75* timeline_size, DegToRad(40.0));

		auto right_foot_bone_track = walk_anim->CreateTrack(right_foot_bone);

		right_foot_bone_track->CreateFrame(0, 0);
		right_foot_bone_track->CreateFrame(0.25* timeline_size, DegToRad(-40.0));
		right_foot_bone_track->CreateFrame(0.75* timeline_size, DegToRad(40.0));
	}

	auto scene0 = world->CreateScene("scene0");

	for (int i = 0; i < 1; i++)
	{
		auto inst0 = scene0->CreateInstance(player_class);
		inst0->SetTransform(TTransform(TVec2(0, 0 + i), TRot(0)));

		auto inst1 = scene0->CreateInstance(bones_player);
		inst1->SetTransform(TTransform(TVec2(3, 0 + i), TRot(0)));
	}

	for (int i = -10; i < 40; i++)
	{
		auto inst0 = scene0->CreateInstance(box_class);
		inst0->SetTransform(TTransform(TVec2(-5 + i*0.9 + 0.3, -7 + sinf(i*0.3) * 1), TRot(i)));
	}

	for (int i = -0; i < 10; i++)
	{
		auto inst0 = scene0->CreateInstance(box_class_dyn);
		inst0->SetTransform(TTransform(TVec2(-5 + i*0.9 + 0.3, 7 + sinf(i*0.3) * 1), TRot(i)));
	}

	auto main_viewport = scene0->CreateViewport("main_viewport");
	main_viewport->SetTransform(TTransform(TVec2(0, 0), TRot(0)));
	main_viewport->SetAspectRatio(1);
	main_viewport->SetWidth(20);

	return world;
}

