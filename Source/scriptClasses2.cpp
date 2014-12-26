#include "scriptClasses2.h"

#include <SDL.h>

//testing only
//#include "texture_polygon.h"
//#include <IL/ilut.h>

#include "World.h"
#include "WorldInstance.h"

using namespace TBaluRenderEnums;

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
	float mult = (object->GetBool("can_jump")) ? 1 : 0.6;
	auto speed = object->GetPhysBody()->GetLinearVelocity();
	speed[0] = -1.4*mult;
	object->GetPhysBody()->SetLinearVelocity(speed);
}
void PlayerRight(TBaluInstance* object)
{
	float mult = (object->GetBool("can_jump")) ? 1 : 0.6;
	auto speed = object->GetPhysBody()->GetLinearVelocity();
	speed[0] = 1.4*mult;
	object->GetPhysBody()->SetLinearVelocity(speed);
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
	//object->SetBool("can_jump", false);
}

TBaluWorld* CreateDemoWorld()
{
	auto world = new TBaluWorld();

	auto brick_mat = world->CreateMaterial("brick");

	brick_mat->SetImagePath("d:\\Downloads\\github\\BaluEngine\\Output\\Debug\\textures\\brick.png");
	brick_mat->SetColor(TVec4(1, 1, 1, 1));

	auto box_sprite = world->CreateSprite("box0");
	box_sprite->GetPolygone().SetMaterial(brick_mat);
	box_sprite->GetPolygone().SetAsBox(1, 1);
	box_sprite->SetPhysShape(new TBaluBoxShape(1, 1));

	auto box_class = world->CreateClass("box");
	auto box_class_instance = box_class->AddSprite(box_sprite);
	box_class->GetPhysBody().Enable(true);
	box_class->GetPhysBody().SetPhysBodyType(TPhysBodyType::Static);
	
	auto player_mat = world->CreateMaterial("player_skin");
	player_mat->SetImagePath("d:\\Downloads\\github\\BaluEngine\\Output\\Debug\\textures\\player.png");
	auto player_sprite = world->CreateSprite("player");

	player_sprite->GetPolygone().SetMaterial(player_mat);
	player_sprite->GetPolygone().SetAsBox(1, 2);
	//player_sprite->SetPhysShape(new TBaluCircleShape(0.5));
	player_sprite->SetPhysShape(new TBaluBoxShape(0.5,2));
	
	player_sprite->SetFramesGrid(512 / 8, 256 / 4);
	player_sprite->CreateAnimationLine("run_right", 0, 12);
	player_sprite->CreateAnimationLine("run_left", 15, 15+8);

	auto player_class = world->CreateClass("player");
	auto player_class_instance = player_class->AddSprite(player_sprite);
	player_class_instance->tag = "character_sprite";
	player_class->GetPhysBody().Enable(true);
	player_class->GetPhysBody().SetPhysBodyType(TPhysBodyType::Dynamic);
	//player_class->GetPhysBody().SetFixedRotation(true);

	auto sensor = player_class->GetPhysBody().CreateSensor(new TBaluCircleShape(0.2, TVec2(0, -0.5)));

	player_class->OnKeyDown(TKey::Up, PlayerJump);
	player_class->OnKeyDown(TKey::Left, PlayerLeft);
	player_class->OnKeyDown(TKey::Right, PlayerRight);

	player_class->OnBeforePhysicsStep(PlayerPrePhysStep);
	//player_class->OnSensorCollide(sensor, PlayerJumpSensorCollide);
	player_class->OnBeginContact(sensor, PlayerJumpSensorBeginCollide);
	player_class->OnEndContact(sensor, PlayerJumpSensorEndCollide);

	auto scene0 = world->CreateScene("scene0");

	for (int i = 0; i < 1; i++)
	{
		auto inst0 = scene0->CreateInstance(player_class);
		inst0->transform = TBaluTransform(TVec2(0, 0+i), b2Rot(0));
	}

	for (int i = -10; i < 40; i++)
	{
		auto inst0 = scene0->CreateInstance(box_class);
		inst0->transform = TBaluTransform(TVec2(-5+i*0.9+0.3, -7+sinf(i*0.3)*3), b2Rot(i));
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

void InitDemoWorld()
{
	auto demo_world = CreateDemoWorld();

	demo_world_instance = new TBaluWorldInstance(demo_world);
	scene_instance = demo_world_instance->RunScene(demo_world->GetScene("scene0"));
}

void Render(std::vector<TRenderCommand>& render_commands)
{
	for (int i = 0; i < render_commands.size(); i++)
	{
		auto& c = render_commands[i];
		TStreamsDesc streams;
		streams.AddStream(TStream::Vertex, TDataType::Float, 2, c.vertices);
		//streams.AddStream(TStream::TexCoord, TDataType::Float, 2, c.tex_coords);
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

int MainLoop()
{

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

	InitDemoWorld();

	auto last_tick = SDL_GetTicks();

	while (!quit)
	{
		auto curr_tick = SDL_GetTicks();
		float step = (curr_tick - last_tick)/1000.0;
		last_tick = curr_tick;

		render->Clear(true);
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
			
		}
	}

	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}