#include "scriptClasses2.h"

#include <SDL.h>

//testing only
//#include "texture_polygon.h"
//#include <IL/ilut.h>

#include "World.h"
#include "WorldInstance.h"

#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\wglew.h>

using namespace TBaluRenderEnums;

std::string base_path;

class TBaluEngineInternal
{
public:
	std::unique_ptr<TBaluRender> render;
};

void PlayerJump(TBaluInstance* object)
{
	
	if (object->GetBool("can_jump"))
	{
		auto speed = object->GetPhysBody()->GetLinearVelocity();
		speed[1] = 4;
		object->GetPhysBody()->SetLinearVelocity(speed);
	}
}
void PlayerLeft(TBaluInstance* object)
{
	float mult = (object->GetBool("can_jump")) ? 1 : 0.8;
	auto speed = object->GetPhysBody()->GetLinearVelocity();
	speed[0] = -1.4*mult;
	object->GetPhysBody()->SetLinearVelocity(speed);
}
void PlayerRight(TBaluInstance* object)
{
	float mult = (object->GetBool("can_jump")) ? 1 : 0.8;
	auto speed = object->GetPhysBody()->GetLinearVelocity();
	speed[0] = 1.4*mult;
	object->GetPhysBody()->SetLinearVelocity(speed);
}

void BonesPlayerLeft(TBaluInstance* object)
{
	object->GetSkeletonAnimation().PlayAnimation("walk", 1);
}

//void PlayerJumpSensorCollide(TBaluInstance* source, TSensorInstance* sensor, TBaluInstance* obstacle, TBaluPhysShapeInstance* obstacle_shape)
//{
//	source->SetBool("can_jump", true);
//}

std::vector<TBaluPhysShapeInstance*> obstacle_shapes;

void PlayerJumpSensorBeginCollide(TBaluInstance* source, TSensorInstance* sensor, TBaluInstance* obstacle, TBaluPhysShapeInstance* obstacle_shape)
{
	auto it = std::find(obstacle_shapes.begin(), obstacle_shapes.end(), obstacle_shape);
	if (it == obstacle_shapes.end())
	{
		obstacle_shapes.push_back(obstacle_shape);
	}
	source->SetBool("can_jump", obstacle_shapes.size()>0);
}

void PlayerJumpSensorEndCollide(TBaluInstance* source, TSensorInstance* sensor, TBaluInstance* obstacle, TBaluPhysShapeInstance* obstacle_shape)
{
	
	auto it = std::find(obstacle_shapes.begin(), obstacle_shapes.end(), obstacle_shape);
	if (it != obstacle_shapes.end())
	{
		obstacle_shapes.erase(it);
	}
	source->SetBool("can_jump", obstacle_shapes.size()>0);
}
void PlayerPrePhysStep(TBaluInstance* object)
{
	auto can_jump = object->GetBool("can_jump");

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
	object->GetSprite(0)->GetPolygon().SetActiveAnimation((v_anim+hor_anim).c_str());
}

void BonesPlayerPrePhysStep(TBaluInstance* object)
{
	auto can_jump = object->GetBool("can_jump");

	auto speed = object->GetPhysBody()->GetLinearVelocity();
	std::string hor_anim, v_anim;
	if (abs(speed[0]) > 0)
		object->GetSkeletonAnimation().PlayAnimation("walk", 1);
	else 
		object->GetSkeletonAnimation().StopAnimation("walk");
}

TBaluWorld* CreateDemoWorld()
{
	auto world = new TBaluWorld();

	auto brick_mat = world->CreateMaterial("brick");

	brick_mat->SetImagePath(base_path+"\\textures\\brick.png");
	brick_mat->SetColor(TVec4(1, 1, 1, 1));

	auto box_sprite = world->CreateSprite("box0");
	box_sprite->GetPolygone().SetMaterial(brick_mat);
	box_sprite->GetPolygone().SetAsBox(1, 1);
	box_sprite->GetPolygone().SetTexCoordsFromVertices(TVec2(-0.5, -0.5), TVec2(1, 1));
	box_sprite->SetPhysShape(new TBaluBoxShape(1, 1));

	auto box_class = world->CreateClass("box");
	auto box_class_instance = box_class->AddSprite(box_sprite);
	box_class->GetPhysBody().Enable(true);
	box_class->GetPhysBody().SetPhysBodyType(TPhysBodyType::Static);
	
	auto player_mat = world->CreateMaterial("player_skin");
	player_mat->SetImagePath(base_path + "\\textures\\player.png");
	auto player_sprite = world->CreateSprite("player");

	player_sprite->GetPolygone().SetMaterial(player_mat);
	//player_sprite->GetPolygone().SetAsBox(20.0/8, 20.0/8);
	player_sprite->GetPolygone().SetAsBox(6, 6);
	//player_sprite->GetPolygone().SetTexCoordsFromVertices(TVec2(0, 0), TVec2(1, 1));
	player_sprite->SetPhysShape(new TBaluCircleShape(2.5));
	//player_sprite->SetPhysShape(new TBaluBoxShape(0.5,2));

	TGridFrames* grid_frames = new TGridFrames(TVec2(0, 0), TVec2(1, 1), 8, 4);

	player_sprite->GetPolygone().AddAnimDesc(grid_frames);
	
	player_sprite->GetPolygone().CreateAnimationLine("run_right", grid_frames, FramesRange(0, 7));
	player_sprite->GetPolygone().CreateAnimationLine("jump_up_right", grid_frames, FramesRange(9, 9));
	player_sprite->GetPolygone().CreateAnimationLine("jump_down_right", grid_frames, FramesRange(10, 10));
	player_sprite->GetPolygone().CreateAnimationLine("stay_right", grid_frames, FramesRange(11, 11));
	player_sprite->GetPolygone().CreateAnimationLine("run_right", grid_frames, FramesRange(0, 7));
	player_sprite->GetPolygone().CreateAnimationLine("run_left", grid_frames, FramesRange(16, 16 + 7));
	player_sprite->GetPolygone().CreateAnimationLine("jump_up_left", grid_frames, FramesRange(16 + 7 + 2, 16 + 7 + 2));
	player_sprite->GetPolygone().CreateAnimationLine("jump_down_left", grid_frames, FramesRange(16 + 7 + 3, 16 + 7 + 3));
	player_sprite->GetPolygone().CreateAnimationLine("stay_left", grid_frames, FramesRange(16 + 7 + 4, 16 + 7 + 4));

	auto player_class = world->CreateClass("player");
	auto player_class_instance = player_class->AddSprite(player_sprite);
	player_class_instance->tag = "character_sprite";
	player_class->GetPhysBody().Enable(true);
	player_class->GetPhysBody().SetPhysBodyType(TPhysBodyType::Dynamic);
	player_class->GetPhysBody().SetFixedRotation(true);

	auto sensor = player_class->GetPhysBody().CreateSensor(new TBaluCircleShape(0.4, TVec2(0, -2.5)));

	player_class->OnKeyDown(TKey::Up, PlayerJump);
	player_class->OnKeyDown(TKey::Left, PlayerLeft);
	player_class->OnKeyDown(TKey::Right, PlayerRight);

	player_class->OnBeforePhysicsStep(PlayerPrePhysStep);
	//player_class->OnSensorCollide(sensor, PlayerJumpSensorCollide);
	player_class->OnBeginContact(sensor, PlayerJumpSensorBeginCollide);
	player_class->OnEndContact(sensor, PlayerJumpSensorEndCollide);

	auto bones_player = world->CreateClass("bones");
	bones_player->OnKeyDown(TKey::Left, BonesPlayerLeft);
	bones_player->OnBeforePhysicsStep(BonesPlayerPrePhysStep);
	{
		auto bones_mat = world->CreateMaterial("zombie");

		bones_mat->SetImagePath(base_path + "\\textures\\zombie.png");
		bones_mat->SetColor(TVec4(1, 1, 1, 1));

		//special phys sprite
		auto bones_phys_sprite = world->CreateSprite("bones_phys_sprite");
		bones_phys_sprite->SetPhysShape(new TBaluCircleShape(1.0, TVec2(0,-1.5)));
		bones_phys_sprite->GetPolygone().SetEnable(false);

		auto bones_player_class_instance = bones_player->AddSprite(bones_phys_sprite);
		bones_player->GetPhysBody().Enable(true);
		bones_player->GetPhysBody().SetPhysBodyType(TPhysBodyType::Dynamic);
		bones_player->GetPhysBody().SetFixedRotation(true);

		//sprites
		auto bones_head = world->CreateSprite("bones_head");
		bones_head->GetPolygone().SetMaterial(bones_mat);
		bones_head->GetPolygone().SetAsBox(2,2);
		bones_head->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(0, 256 - 256) / 256, TVec2(73, 256 -192) / 256);

		auto bones_torso = world->CreateSprite("bones_torso");
		bones_torso->GetPolygone().SetMaterial(bones_mat);
		bones_torso->GetPolygone().SetAsBox(1.6, 2.5);
		bones_torso->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(0, 256 - 189) / 256, TVec2(53, 256 - 112) / 256);

		//hands

		auto bones_left_shoulder = world->CreateSprite("bones_left_shoulder");
		bones_left_shoulder->GetPolygone().SetMaterial(bones_mat);
		bones_left_shoulder->GetPolygone().SetAsBox(1, 1);
		bones_left_shoulder->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(113, 256 - 190) / 256, TVec2(152, 256 - 142) / 256);

		auto bones_left_hand = world->CreateSprite("bones_left_hand");
		bones_left_hand->GetPolygone().SetMaterial(bones_mat);
		bones_left_hand->GetPolygone().SetAsBox(1, 1);
		bones_left_hand->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(75, 256 - 256) / 256, TVec2(138, 256 - 193) / 256);

		auto bones_right_shoulder = world->CreateSprite("bones_right_shoulder");
		bones_right_shoulder->GetPolygone().SetMaterial(bones_mat);
		bones_right_shoulder->GetPolygone().SetAsBox(1, 1);
		bones_right_shoulder->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(152, 256 - 192) / 256, TVec2(183, 256 - 143) / 256);

		auto bones_right_hand = world->CreateSprite("bones_right_hand");
		bones_right_hand->GetPolygone().SetMaterial(bones_mat);
		bones_right_hand->GetPolygone().SetAsBox(1, 1);
		bones_right_hand->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(58, 256 - 190) / 256, TVec2(113, 256 - 129) / 256);

		//legs

		auto bones_left_leg = world->CreateSprite("bones_left_leg");
		bones_left_leg->GetPolygone().SetMaterial(bones_mat);
		bones_left_leg->GetPolygone().SetAsBox(1, 1);
		bones_left_leg->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(55, 256 - 72) / 256, TVec2(94, 256 - 14) / 256);

		auto bones_left_foot = world->CreateSprite("bones_left_foot");
		bones_left_foot->GetPolygone().SetMaterial(bones_mat);
		bones_left_foot->GetPolygone().SetAsBox(1, 1);
		bones_left_foot->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(54, 256 - 131) / 256, TVec2(94, 256 - 75) / 256);

		auto bones_right_leg = world->CreateSprite("bones_right_leg");
		bones_right_leg->GetPolygone().SetMaterial(bones_mat);
		bones_right_leg->GetPolygone().SetAsBox(1, 1);
		bones_right_leg->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(0, 256 - 55) / 256, TVec2(44, 256 - 7) / 256);

		auto bones_right_foot = world->CreateSprite("bones_right_foot");
		bones_right_foot->GetPolygone().SetMaterial(bones_mat);
		bones_right_foot->GetPolygone().SetAsBox(1, 1);
		bones_right_foot->GetPolygone().SetTexCoordsFromVerticesByRegion(TVec2(9, 256 - 112) / 256, TVec2(39, 256 - 56) / 256);

		auto& bones_player_skel = bones_player->GetSkeleton();

		//bones
		auto root_bone = bones_player_skel.CreateBone(nullptr);
		
		auto right_leg_bone = bones_player_skel.CreateBone(root_bone);
		right_leg_bone->SetTransform(TBaluTransform(TVec2(-0.5, -1.5), b2Rot(0)));
		auto right_foot_bone = bones_player_skel.CreateBone(right_leg_bone);
		right_foot_bone->SetTransform(TBaluTransform(TVec2(0, -1), b2Rot(0)));

		auto left_leg_bone = bones_player_skel.CreateBone(root_bone);
		left_leg_bone->SetTransform(TBaluTransform(TVec2(0.5, -1), b2Rot(0)));
		auto left_foot_bone = bones_player_skel.CreateBone(left_leg_bone);
		left_foot_bone->SetTransform(TBaluTransform(TVec2(0.0, -0.5), b2Rot(0)));

		auto right_shoulder_bone = bones_player_skel.CreateBone(root_bone);
		auto right_hand_bone = bones_player_skel.CreateBone(right_shoulder_bone);

		auto left_shoulder_bone = bones_player_skel.CreateBone(root_bone);
		auto left_hand_bone = bones_player_skel.CreateBone(left_shoulder_bone);

		//create skin
		auto skin = bones_player_skel.CreateSkin();
		skin->SetBoneSprite(bones_player_skel.GetBoneIndex(root_bone), bones_head, TBaluTransform(TVec2(-0.3,2),b2Rot(0)));

		skin->SetBoneSprite(bones_player_skel.GetBoneIndex(root_bone), bones_torso, TBaluTransform(TVec2(0, 0), b2Rot(0)));

		skin->SetBoneSprite(bones_player_skel.GetBoneIndex(right_leg_bone), bones_right_leg, TBaluTransform(TVec2(0, 0), b2Rot(0)));
		skin->SetBoneSprite(bones_player_skel.GetBoneIndex(right_foot_bone), bones_right_foot, TBaluTransform(TVec2(0, 0), b2Rot(0)));

		skin->SetBoneSprite(bones_player_skel.GetBoneIndex(left_leg_bone), bones_left_leg, TBaluTransform(TVec2(0, -0.5), b2Rot(0)));
		skin->SetBoneSprite(bones_player_skel.GetBoneIndex(left_foot_bone), bones_left_foot, TBaluTransform(TVec2(0, -1), b2Rot(0)));

		//walk animation
		auto& skel_anim = bones_player->GetSkeletonAnimation();

		auto walk_anim = skel_anim.CreateAnimation("walk");
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
		inst0->transform = TBaluTransform(TVec2(0, 0+i), b2Rot(0));

		auto inst1 = scene0->CreateInstance(bones_player);
		inst1->transform = TBaluTransform(TVec2(3, 0 + i), b2Rot(0));
	}

	for (int i = -10; i < 40; i++)
	{
		auto inst0 = scene0->CreateInstance(box_class);
		inst0->transform = TBaluTransform(TVec2(-5+i*0.9+0.3, -7+sinf(i*0.3)*1), b2Rot(i));
	}

	auto viewport = scene0->CreateViewport("main_viewport");
	viewport->SetTransform(TBaluTransform(TVec2(0,0),b2Rot(0)));
	viewport->SetAspectRatio(1);
	viewport->SetWidth(5);

	return world;
}

TBaluWorldInstance* demo_world_instance;
TBaluSceneInstance* scene_instance;

TBaluRender* render;

class TBaluEngineRender
{
public:
	static TResourses* CreateResources(TBaluRender* render)
	{
		return new TResourses(render);
	}
};


TResourses* resources;

void InitDemoWorld()
{
	auto demo_world = CreateDemoWorld();

	demo_world_instance = new TBaluWorldInstance(demo_world, resources);
	scene_instance = demo_world_instance->RunScene(demo_world->GetScene("scene0"));
}

void Render(std::vector<TRenderCommand>& render_commands)
{
	
	//render->AlphaTest.Enable(true);
	//render->AlphaTest.Func(TAlphaTestFunc::AT_GREATER, 0.9);
	render->Blend.Enable(true);
	render->Blend.Func(TBlendEquation::BE_SRC_ALPHA, TBlendFunc::BF_ADD, TBlendEquation::BE_ONE_MINUS_SRC_ALPHA);

	for (int i = 0; i < render_commands.size(); i++)
	{
		auto& c = render_commands[i];
		auto tex = c.material_id->GetTexture();
		render->Texture.Bind(*(TTextureId*)&tex);
		TStreamsDesc streams;
		streams.AddStream(TStream::Vertex, TDataType::Float, 2, c.vertices);
		streams.AddStream(TStream::TexCoord, TDataType::Float, 2, c.tex_coords);
		//streams.AddStream(TStream::Color, TDataType::Float, 4, c.colors);
		render->Draw(streams, TPrimitive::Triangles, c.vertices_count);
	}
}

void Step(float step)
{

	demo_world_instance->OnPrePhysStep();
	demo_world_instance->PhysStep(step);
	
	demo_world_instance->UpdateTransform();

	auto viewport = scene_instance->GetViewport("main");

	std::vector<TBaluSpritePolygonInstance*> polygons;
	scene_instance->QueryAABB(viewport->GetAABB(), polygons);

	std::vector<TRenderCommand> render_commands;
	render_commands.resize(polygons.size());
	for (int i = 0; i < render_commands.size(); i++)
	{
		polygons[i]->Render(render_commands[i]);
	}

	render->Set.ModelView(TMatrix4::GetOrtho(TVec2(0, 0), TVec2(20, 20), -1, 1));

	Render(render_commands);

	demo_world_instance->OnProcessCollisions();

	demo_world_instance->OnStep(step);

	g_camera.m_height = 512;
	g_camera.m_width = 512;
	g_camera.m_extent = 10;
	g_camera.m_zoom = 1;

	demo_world_instance->DebugDraw();
}

void TBaluEngineTest::Step(float step, double time)
{

}

int MainLoop()
{

	base_path = SDL_GetBasePath();

	SDL_Window *mainwindow; /* Our window handle */

	SDL_GLContext maincontext; /* Our opengl context handle */

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{ /* Initialize SDL's Video subsystem */

		return 1;
	}
	/* Request opengl 4.4 context. */
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	/* Turn on double buffering with a 24bit Z buffer.
	* You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	/* Create our window centered at 512x512 resolution */

	mainwindow = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!mainwindow)
	{ /* Die if creation failed */

		SDL_Quit();
		return 1;
	}
	
	/* Create our opengl context and attach it to our window */

	maincontext = SDL_GL_CreateContext(mainwindow);

	auto err = SDL_GetError();
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	//SDL_GL_SetSwapInterval(1);
	
	bool quit = false;
	SDL_Event event;

	render = new TBaluRender(TVec2i(512, 512));

	resources = TBaluEngineRender::CreateResources(render);

	InitDemoWorld();

	auto last_tick = SDL_GetTicks();

	while (!quit)
	{
		auto curr_tick = SDL_GetTicks();
		float step = (curr_tick - last_tick)/1000.0;
		last_tick = curr_tick;
		render->Set.ClearColor(0.2, 0.3, 0.3);
		render->Clear(true,true);
		const Uint8 *keystate = SDL_GetKeyboardState(NULL);
		if (keystate[SDL_SCANCODE_LEFT])
			demo_world_instance->OnKeyDown(TKey::Left);
		if (keystate[SDL_SCANCODE_RIGHT])
			demo_world_instance->OnKeyDown(TKey::Right);
		if (keystate[SDL_SCANCODE_UP])
			demo_world_instance->OnKeyDown(TKey::Up);
		if (keystate[SDL_SCANCODE_DOWN])
			demo_world_instance->OnKeyDown(TKey::Down);

		Step(step);

		SDL_GL_SwapWindow(mainwindow);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (event.type == SDL_KEYUP)
			{
			}
			else if (event.type == SDL_KEYDOWN)
			{
				SDL_SetWindowTitle(mainwindow, "keydown");			
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				char b[100];
				sprintf_s(b, "Mouse %i %i", event.motion.x, event.motion.y);
				SDL_SetWindowTitle(mainwindow, b);
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{

			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
			}
			else if (event.type == SDL_MOUSEWHEEL)
			{

			}
			else if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					render->Set.Viewport(TVec2i(event.window.data1, event.window.data2));
			}
		}
	}

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}