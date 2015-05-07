#pragma once

#include "../Source/EngineInterfaces.h"

using namespace EngineInterface;

#ifdef USE_CALLBACKS

void PlayerJump(TCallbackData* data, IBaluInstance* object)
{

	if (object->GetProperties()->GetBool("can_jump"))
	{
		auto speed = object->GetPhysBody()->GetLinearVelocity();
		speed[1] = 4;
		object->GetPhysBody()->SetLinearVelocity(speed);
	}
}

void PlayerLeft(TCallbackData* data, IBaluInstance* object)
{
	float mult = (object->GetProperties()->GetBool("can_jump")) ? 1 : 0.8;
	auto speed = object->GetPhysBody()->GetLinearVelocity();
	speed[0] = -1.4*mult;
	object->GetPhysBody()->SetLinearVelocity(speed);
}

void PlayerRight(TCallbackData* data, IBaluInstance* object)
{
	float mult = (object->GetProperties()->GetBool("can_jump")) ? 1 : 0.8;
	auto speed = object->GetPhysBody()->GetLinearVelocity();
	speed[0] = 1.4*mult;
	object->GetPhysBody()->SetLinearVelocity(speed);
}

void BonesPlayerLeft(TCallbackData* data, IBaluInstance* object)
{
	object->GetSkeletonAnimation()->PlayAnimation("walk", 1);
}

void PlayerJumpSensorCollide(TCallbackData* callback, EngineInterface::IBaluPhysShapeInstance* source, EngineInterface::IBaluInstance* obstacle)
{
	source->GetParent()->GetProperties()->SetBool("can_jump", true);
}

void PlayerPrePhysStep(TCallbackData* data, IBaluInstance* object)
{
	PropertyType type;
	if (!object->GetProperties()->HasProperty("can_jump", type))
		object->GetProperties()->SetBool("can_jump", false);
	auto can_jump = object->GetProperties()->GetBool("can_jump");

	auto speed = object->GetPhysBody()->GetLinearVelocity();
	std::string hor_anim, v_anim;
	if (speed[0] > 0)
		hor_anim = "_right";
	//
	else
		hor_anim = "_left";
	if (can_jump)
	{
		if (abs(speed[0]) > 0.5)
			v_anim = "run";
		else
			v_anim = "stay";
	}
	else
	{
		if (speed[1] > 0)
			v_anim = "jump_up";
		else
			v_anim = "jump_down";
	}
	object->GetSprite(0)->GetPolygon()->SetActiveAnimation((v_anim + hor_anim).c_str());

	object->GetProperties()->SetBool("can_jump", false);
}

void BonesPlayerPrePhysStep(TCallbackData* data, IBaluInstance* object)
{
	PropertyType type;
	if (!object->GetProperties()->HasProperty("can_jump", type))
		object->GetProperties()->SetBool("can_jump", false);
	auto can_jump = object->GetProperties()->GetBool("can_jump");

	auto speed = object->GetPhysBody()->GetLinearVelocity();
	std::string hor_anim, v_anim;
	if (abs(speed[0]) > 0)
		object->GetSkeletonAnimation()->PlayAnimation("walk", 1);
	else
		object->GetSkeletonAnimation()->StopAnimation("walk");
}


void ViewportResize(TCallbackData* data, IDirector* director, TVec2i old_size, TVec2i new_size)
{
	//main_viewport �� ���� �����
	TVec2 k = TVec2((float)new_size[0], (float)new_size[1]) / TVec2((float)old_size[0], (float)old_size[1]);
	auto main_viewport = director->GetWorldInstance()->GetSceneInstance(0)->GetSource()->FindViewport("main_viewport");
	auto old_vieport_size = main_viewport->GetSize();
	auto new_vieport_size = old_vieport_size.ComponentMul(k);
	main_viewport->SetSize(new_vieport_size);
}

void WorldStart(TCallbackData* data, IBaluWorldInstance* world_instance, IComposer* composer)
{
	auto scene = world_instance->GetSource()->GetScenes()[0].second;
	auto scene_instance = world_instance->RunScene(scene);
	composer->AddToRender(scene_instance, scene->FindViewport("main_viewport"));
}

#else


char* PlayerJump_source = //(IBaluInstance object)
"	if (object.GetProperties().GetBool(\"can_jump\"))\n"
"	{\n"
"		vec2 speed = object.GetPhysBody().GetLinearVelocity();\n"
"		speed.y = 4;\n"
"		object.GetPhysBody().SetLinearVelocity(speed);\n"
"	}\n";

char* PlayerLeft_source = //(TCallbackData* data, IBaluInstance* object)
"	float mult = 0.8;\n"
"	if(object.GetProperties().GetBool(\"can_jump\")) mult = 1;\n"
"	vec2 speed = object.GetPhysBody().GetLinearVelocity();\n"
"	speed.x = -1.4*mult;\n"
"	object.GetPhysBody().SetLinearVelocity(speed);\n";

char* PlayerRight_source = //(TCallbackData* data, IBaluInstance* object)
"	float mult = 0.8;\n"
"	if(object.GetProperties().GetBool(\"can_jump\")) mult = 1;\n"
"	vec2 speed = object.GetPhysBody().GetLinearVelocity();\n"
"	speed.x = 1.4*mult;\n"
"	object.GetPhysBody().SetLinearVelocity(speed);\n";

char* PlayerJumpSensorCollide_source = //(TCallbackData* callback, EngineInterface::IBaluPhysShapeInstance* source, EngineInterface::IBaluInstance* obstacle)
"	source.GetParent().GetProperties().SetBool(\"can_jump\", true);\n";

char* PlayerPrePhysStep_source = //(TCallbackData* data, IBaluInstance* object)
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

char* BonesPlayerPrePhysStep_source = //(TCallbackData* data, IBaluInstance* object)
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
"	IScene scene = world_instance.GetSource().GetScene(1);\n"
"	ISceneInstance scene_instance = world_instance.RunScene(scene);\n"
"	composer.AddToRender(scene_instance, scene.FindViewport(\"main_viewport\"));\n";

#endif

IBaluWorld* CreateDemoWorld(std::string assets_dir)
{
	auto world = CreateWorld();

	world->AddOnWorldStart(CallbackWithData<OnStartWorldCallback>(WorldStart_source, &world->GetCallbacksActiveType(), TCallbacksActiveType::DEFAULT));
	world->AddOnViewportResize(CallbackWithData<ViewportResizeCallback>(ViewportResize_source, &world->GetCallbacksActiveType(), TCallbacksActiveType::DEFAULT));

	auto brick_mat = world->CreateMaterial("brick");

	brick_mat->SetImagePath("\\textures\\brick.png");
	brick_mat->SetColor(TVec4(1, 1, 1, 1));

	auto box_sprite = world->CreateSprite("box0");
	box_sprite->GetPolygone()->SetMaterial(brick_mat);
	//box_sprite->GetPolygone()->SetAsBox(1, 1);
	box_sprite->GetPolygone()->SetPolygonFromTexture(assets_dir);
	box_sprite->GetPolygone()->SetTexCoordsFromVertices(TVec2(-0.5, -0.5), TVec2(1, 1));
	box_sprite->SetPhysShape(world->GetPhysShapeFactory()->CreateBoxShape(1, 1)->GetPhysShape());

	auto box_class = world->CreateClass("box");
	auto box_class_instance = box_class->AddSprite(box_sprite);
	box_class->GetPhysBody()->Enable(true);
	box_class->GetPhysBody()->SetPhysBodyType(TPhysBodyType::Static);

	auto player_mat = world->CreateMaterial("player_skin");
	player_mat->SetImagePath("\\textures\\player.png");
	auto player_sprite = world->CreateSprite("player");

	player_sprite->GetPolygone()->SetMaterial(player_mat);
	//player_sprite->GetPolygone()->SetAsBox(20.0/8, 20.0/8);
	player_sprite->GetPolygone()->SetAsBox(6, 6);
	//player_sprite->GetPolygone()->SetPolygonFromTexture();
	//player_sprite->GetPolygone()->SetTexCoordsFromVertices(TVec2(0, 0), TVec2(1, 1));
	player_sprite->SetPhysShape(world->GetPhysShapeFactory()->CreateCircleShape(2.5)->GetPhysShape());
	//player_sprite->SetPhysShape(new TBaluBoxShape(0.5,2));

	TGridFrames* grid_frames = new TGridFrames(TVec2(0, 0), TVec2(1, 1), 8, 4);

	player_sprite->GetPolygone()->AddAnimDesc(grid_frames);

	player_sprite->GetPolygone()->CreateAnimationLine("run_right", grid_frames, TFramesRange(0, 7).ToFramesArray());
	player_sprite->GetPolygone()->CreateAnimationLine("jump_up_right", grid_frames, TFramesRange(9, 9).ToFramesArray());
	player_sprite->GetPolygone()->CreateAnimationLine("jump_down_right", grid_frames, TFramesRange(10, 10).ToFramesArray());
	player_sprite->GetPolygone()->CreateAnimationLine("stay_right", grid_frames, TFramesRange(11, 11).ToFramesArray());
	player_sprite->GetPolygone()->CreateAnimationLine("run_right", grid_frames, TFramesRange(0, 7).ToFramesArray());
	player_sprite->GetPolygone()->CreateAnimationLine("run_left", grid_frames, TFramesRange(16, 16 + 7).ToFramesArray());
	player_sprite->GetPolygone()->CreateAnimationLine("jump_up_left", grid_frames, TFramesRange(16 + 7 + 2, 16 + 7 + 2).ToFramesArray());
	player_sprite->GetPolygone()->CreateAnimationLine("jump_down_left", grid_frames, TFramesRange(16 + 7 + 3, 16 + 7 + 3).ToFramesArray());
	player_sprite->GetPolygone()->CreateAnimationLine("stay_left", grid_frames, TFramesRange(16 + 7 + 4, 16 + 7 + 4).ToFramesArray());

	auto player_class = world->CreateClass("player");
	auto player_class_instance = player_class->AddSprite(player_sprite);
	//player_class_instance->tag = "character_sprite";
	player_class->GetPhysBody()->Enable(true);
	player_class->GetPhysBody()->SetPhysBodyType(TPhysBodyType::Dynamic);
	player_class->GetPhysBody()->SetFixedRotation(true);

	auto player_phys_sprite = world->CreateSprite("player_phys");
	player_class->AddSprite(player_phys_sprite);
	player_phys_sprite->SetPhysShape(world->GetPhysShapeFactory()->CreateCircleShape(0.4, TVec2(0, -2.5))->GetPhysShape());
	player_phys_sprite->GetPhysShape()->SetIsSensor(true);

#ifdef USE_CALLBACKS
	player_class->OnKeyDown(TKey::Up, CallbackWithData<KeyUpDownCallback>(PlayerJump, &world->GetCallbacksActiveType()));
	player_class->OnKeyDown(TKey::Left, CallbackWithData<KeyUpDownCallback>(PlayerLeft, &world->GetCallbacksActiveType()));
	player_class->OnKeyDown(TKey::Right, CallbackWithData<KeyUpDownCallback>(PlayerRight, &world->GetCallbacksActiveType()));

	player_class->OnBeforePhysicsStep(CallbackWithData<BeforePhysicsCallback>(PlayerPrePhysStep, &world->GetCallbacksActiveType()));
	player_phys_sprite->OnCollide(box_class, CallbackWithData<CollideCallback>(PlayerJumpSensorCollide, &world->GetCallbacksActiveType()));
#else
	player_class->OnKeyDown(TKey::Up, CallbackWithData<KeyUpDownCallback>(PlayerJump_source, &world->GetCallbacksActiveType()));
	player_class->OnKeyDown(TKey::Left, CallbackWithData<KeyUpDownCallback>(PlayerLeft_source, &world->GetCallbacksActiveType()));
	player_class->OnKeyDown(TKey::Right, CallbackWithData<KeyUpDownCallback>(PlayerRight_source, &world->GetCallbacksActiveType()));

	player_class->OnBeforePhysicsStep(CallbackWithData<BeforePhysicsCallback>(PlayerPrePhysStep_source, &world->GetCallbacksActiveType()));
	player_phys_sprite->AddOnCollide(box_class, CallbackWithData<CollideCallback>(PlayerJumpSensorCollide_source, &world->GetCallbacksActiveType()));
#endif

	auto bones_player = world->CreateClass("bones");
#ifdef USE_CALLBACKS
	bones_player->OnKeyDown(TKey::Left, CallbackWithData<KeyUpDownCallback>(BonesPlayerLeft, &world->GetCallbacksActiveType()));
	bones_player->OnBeforePhysicsStep(CallbackWithData<KeyUpDownCallback>(BonesPlayerPrePhysStep, &world->GetCallbacksActiveType()));
#else
	bones_player->OnBeforePhysicsStep(CallbackWithData<BeforePhysicsCallback>(BonesPlayerPrePhysStep_source, &world->GetCallbacksActiveType()));
#endif
	{
		auto bones_mat = world->CreateMaterial("zombie");

		bones_mat->SetImagePath("\\textures\\zombie.png");
		bones_mat->SetColor(TVec4(1, 1, 1, 1));

		//special phys sprite
		auto bones_phys_sprite = world->CreateSprite("bones_phys_sprite");
		bones_phys_sprite->SetPhysShape(world->GetPhysShapeFactory()->CreateCircleShape(1.0, TVec2(0, -1.5))->GetPhysShape());
		bones_phys_sprite->GetPolygone()->SetEnable(false);

		auto bones_player_class_instance = bones_player->AddSprite(bones_phys_sprite);
		bones_player->GetPhysBody()->Enable(true);
		bones_player->GetPhysBody()->SetPhysBodyType(TPhysBodyType::Dynamic);
		bones_player->GetPhysBody()->SetFixedRotation(true);

		//sprites
		auto bones_head = world->CreateSprite("bones_head");
		bones_head->GetPolygone()->SetMaterial(bones_mat);
		bones_head->GetPolygone()->SetAsBox(2, 2);
		bones_head->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(0, 256 - 256) / 256, TVec2(73, 256 - 192) / 256);

		auto bones_torso = world->CreateSprite("bones_torso");
		bones_torso->GetPolygone()->SetMaterial(bones_mat);
		bones_torso->GetPolygone()->SetAsBox(1.6, 2.5);
		bones_torso->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(0, 256 - 189) / 256, TVec2(53, 256 - 112) / 256);

		//hands

		auto bones_left_shoulder = world->CreateSprite("bones_left_shoulder");
		bones_left_shoulder->GetPolygone()->SetMaterial(bones_mat);
		bones_left_shoulder->GetPolygone()->SetAsBox(1, 1);
		bones_left_shoulder->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(113, 256 - 190) / 256, TVec2(152, 256 - 142) / 256);

		auto bones_left_hand = world->CreateSprite("bones_left_hand");
		bones_left_hand->GetPolygone()->SetMaterial(bones_mat);
		bones_left_hand->GetPolygone()->SetAsBox(1, 1);
		bones_left_hand->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(75, 256 - 256) / 256, TVec2(138, 256 - 193) / 256);

		auto bones_right_shoulder = world->CreateSprite("bones_right_shoulder");
		bones_right_shoulder->GetPolygone()->SetMaterial(bones_mat);
		bones_right_shoulder->GetPolygone()->SetAsBox(1, 1);
		bones_right_shoulder->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(152, 256 - 192) / 256, TVec2(183, 256 - 143) / 256);

		auto bones_right_hand = world->CreateSprite("bones_right_hand");
		bones_right_hand->GetPolygone()->SetMaterial(bones_mat);
		bones_right_hand->GetPolygone()->SetAsBox(1, 1);
		bones_right_hand->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(58, 256 - 190) / 256, TVec2(113, 256 - 129) / 256);

		//legs

		auto bones_left_leg = world->CreateSprite("bones_left_leg");
		bones_left_leg->GetPolygone()->SetMaterial(bones_mat);
		bones_left_leg->GetPolygone()->SetAsBox(1, 1);
		bones_left_leg->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(55, 256 - 72) / 256, TVec2(94, 256 - 14) / 256);

		auto bones_left_foot = world->CreateSprite("bones_left_foot");
		bones_left_foot->GetPolygone()->SetMaterial(bones_mat);
		bones_left_foot->GetPolygone()->SetAsBox(1, 1);
		bones_left_foot->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(54, 256 - 131) / 256, TVec2(94, 256 - 75) / 256);

		auto bones_right_leg = world->CreateSprite("bones_right_leg");
		bones_right_leg->GetPolygone()->SetMaterial(bones_mat);
		bones_right_leg->GetPolygone()->SetAsBox(1, 1);
		bones_right_leg->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(0, 256 - 55) / 256, TVec2(44, 256 - 7) / 256);

		auto bones_right_foot = world->CreateSprite("bones_right_foot");
		bones_right_foot->GetPolygone()->SetMaterial(bones_mat);
		bones_right_foot->GetPolygone()->SetAsBox(1, 1);
		bones_right_foot->GetPolygone()->SetTexCoordsFromVerticesByRegion(TVec2(9, 256 - 112) / 256, TVec2(39, 256 - 56) / 256);

		auto bones_player_skel = bones_player->GetSkeleton();

		//bones
		auto root_bone = bones_player_skel->CreateBone(nullptr);

		auto right_leg_bone = bones_player_skel->CreateBone(root_bone);
		right_leg_bone->SetTransform(TBaluTransform(TVec2(-0.5, -0.5), TRot(0)));
		auto right_foot_bone = bones_player_skel->CreateBone(right_leg_bone);
		right_foot_bone->SetTransform(TBaluTransform(TVec2(0, -1.0), TRot(0)));

		auto left_leg_bone = bones_player_skel->CreateBone(root_bone);
		left_leg_bone->SetTransform(TBaluTransform(TVec2(0.5, -0.5), TRot(0)));
		auto left_foot_bone = bones_player_skel->CreateBone(left_leg_bone);
		left_foot_bone->SetTransform(TBaluTransform(TVec2(0.0, -1.0), TRot(0)));

		auto right_shoulder_bone = bones_player_skel->CreateBone(root_bone);
		auto right_hand_bone = bones_player_skel->CreateBone(right_shoulder_bone);

		auto left_shoulder_bone = bones_player_skel->CreateBone(root_bone);
		auto left_hand_bone = bones_player_skel->CreateBone(left_shoulder_bone);

		//create skin
		auto skin = bones_player_skel->CreateSkin();
		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(root_bone), bones_head, TBaluTransform(TVec2(-0.3, 1.2), TRot(0)));

		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(root_bone), bones_torso, TBaluTransform(TVec2(0, 0), TRot(0)));

		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(right_leg_bone), bones_right_leg, TBaluTransform(TVec2(0, -0.5), TRot(0)));
		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(right_foot_bone), bones_right_foot, TBaluTransform(TVec2(0, -0.5), TRot(0)));

		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(left_leg_bone), bones_left_leg, TBaluTransform(TVec2(0, -0.5), TRot(0)));
		skin->SetBoneSprite(bones_player_skel->GetBoneIndex(left_foot_bone), bones_left_foot, TBaluTransform(TVec2(0, -0.5), TRot(0)));

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
		inst0->SetTransform(TBaluTransform(TVec2(0, 0 + i), TRot(0)));

		auto inst1 = scene0->CreateInstance(bones_player);
		inst1->SetTransform(TBaluTransform(TVec2(3, 0 + i), TRot(0)));
	}

	for (int i = -10; i < 40; i++)
	{
		auto inst0 = scene0->CreateInstance(box_class);
		inst0->SetTransform(TBaluTransform(TVec2(-5 + i*0.9 + 0.3, -7 + sinf(i*0.3) * 1), TRot(i)));
	}

	auto main_viewport = scene0->CreateViewport("main_viewport");
	main_viewport->SetTransform(TBaluTransform(TVec2(0, 0), TRot(0)));
	main_viewport->SetAspectRatio(1);
	main_viewport->SetWidth(20);

	return world;
}

