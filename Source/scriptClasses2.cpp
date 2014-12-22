#include "scriptClasses2.h"

#include <SDL.h>

//testing only
//#include "texture_polygon.h"
//#include <IL/ilut.h>

#include "World.h"
#include "WorldInstance.h"

class TBaluEngineInternal
{
public:
	std::unique_ptr<TBaluRender> render;

	b2World* phys_world;
};

void Finalize()
{

}
void Display()
{

}

void PlayerJump(TBaluInstance* object)
{
	if (object->GetBool("can_jump"))
	{
		auto speed = object->GetPhysBody().GetLinearVelocity();
		speed[1] = 1;
		object->GetPhysBody().SetLinearVelocity(speed);
	}
}
void PlayerLeft(TBaluInstance* object)
{
	float mult = (object->GetBool("can_jump")) ? 1 : 0.3;
	auto speed = object->GetPhysBody().GetLinearVelocity();
	speed[0] = -0.4*mult;
	object->GetPhysBody().SetLinearVelocity(speed);
}
void PlayerRight(TBaluInstance* object)
{
	float mult = (object->GetBool("can_jump")) ? 1 : 0.3;
	auto speed = object->GetPhysBody().GetLinearVelocity();
	speed[0] = 0.4*mult;
	object->GetPhysBody().SetLinearVelocity(speed);
}

void PlayerJumpSensorCollide(TBaluInstance* source, TBaluClass::TSensor* sensor, TBaluInstance* obstacle, TBaluPhysShapeInstance* obstacle_shape)
{
	source->SetBool("can_jump", true);
}

void PlayerPrePhysStep(TBaluInstance* object)
{
	object->SetBool("can_jump", false);
}

TBaluWorld* CreateDemoWorld()
{
	auto world = new TBaluWorld();

	auto brick_mat = world->CreateMaterial("brick");

	brick_mat->SetImagePath("images\brick.png");
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
	player_mat->SetImagePath("images\player.png");
	auto player_sprite = world->CreateSprite("player");

	player_sprite->GetPolygone().SetMaterial(player_mat);
	player_sprite->GetPolygone().SetAsBox(1, 1);
	player_sprite->SetPhysShape(new TBaluCircleShape(0.5));
	
	player_sprite->SetFramesGrid(512 / 8, 256 / 4);
	player_sprite->CreateAnimationLine("run_right", 0, 12);
	player_sprite->CreateAnimationLine("run_left", 15, 15+8);

	auto player_class = world->CreateClass("player");
	auto player_class_instance = player_class->AddSprite(player_sprite);
	player_class_instance->tag = "character_sprite";
	player_class->GetPhysBody().Enable(true);
	player_class->GetPhysBody().SetPhysBodyType(TPhysBodyType::Dynamic);
	player_class->GetPhysBody().SetFixedRotation(true);

	auto sensor = player_class->CreateSensor(new TBaluCircleShape(0.2, TVec2(-0.5, 0)));

	player_class->OnKeyDown(TKey::Up, PlayerJump);
	player_class->OnKeyDown(TKey::Left, PlayerLeft);
	player_class->OnKeyDown(TKey::Right, PlayerRight);

	player_class->OnBeforePhysicsStep(PlayerPrePhysStep);
	player_class->OnSensorCollide(sensor, PlayerJumpSensorCollide);

	return world;
}

void TextureToolTest()
{
	auto demo_world = CreateDemoWorld();

	//MainLoop();
}

//int TBaluEngine::MainLoop()
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
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	/* Turn on double buffering with a 24bit Z buffer.
	* You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	/* Create our window centered at 512x512 resolution */

	mainwindow = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!mainwindow)
	{ /* Die if creation failed */

		SDL_Quit();
		return 1;
	}

	/* Create our opengl context and attach it to our window */

	maincontext = SDL_GL_CreateContext(mainwindow);
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(1);
	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		Display();
		SDL_GL_SwapWindow(mainwindow);
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT){
				quit = true;

			}
		}
	}

	Finalize();
	/* Delete our opengl context, destroy our window, and shutdown SDL */
	SDL_GL_DeleteContext(maincontext);
	SDL_DestroyWindow(mainwindow);
	SDL_Quit();

	return 0;
}
//
//
//TBaluEngine::TBaluEngine()
//{
//	MainLoop();
//}
//
//TBaluEngine::TBaluEngine(int hWnd, TVec2i use_size)
//{
//	p.reset(new TBaluEngineInternal());
//	p->render.reset(new TBaluRender(hWnd, use_size));
//	p->phys_world = NULL;
//}
//TBaluEngine::~TBaluEngine()
//{
//	delete p->phys_world;
//}
//
//void TBaluEngine::SetViewport(TVec2i use_size)
//{
//	p->render->Set.Viewport(use_size);
//}
//
//void TBaluEngine::OnMouseLeftUp()
//{
//	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEUP, LEFT);
//}
//
//void TBaluEngine::OnMouseLeftDown()
//{
//	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEDOWN, LEFT);
//}
//
//void TBaluEngine::OnMouseRightUp()
//{
//	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEUP, RIGHT);
//}
//
//void TBaluEngine::OnMouseRightDown()
//{
//	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEDOWN, RIGHT);
//}
//
//void TBaluEngine::OnMouseMiddleUp()
//{
//	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEUP, MIDDLE);
//}
//
//void TBaluEngine::OnMouseMiddleDown()
//{
//	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEDOWN, MIDDLE);
//}
//
//void TBaluEngine::OnMouseMove(TVec2i use_client_mouse_pos)
//{
//}
//
//void TBaluEngine::OnMouseScroll(float delta)
//{
//	delta /= 120.f;
//	//CallEvent(TBaluEvent::EVENT_GLOBALMOUSEWHEEL, *(int*)&delta);
//}