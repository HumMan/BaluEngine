
#include <baluEngine.h>

#include "../Source/exportMacro.h"

#include <map>

#include <baluRender.h>

#include <box2d.h>

#include "../Source/scriptClasses.h""

const int MAX_EVENTS = (int)TBaluEvent::MAX_EVENTS;

const static char* event_name[MAX_EVENTS] =
{
	"OnCreate",
	"OnDestroy",
	"OnStep",
	"OnDraw",
	"OnGlobalMouseDown",
	"OnGlobalMouseUp",
	"OnGlobalMouseMove",
	"OnGlobalMouseWheel",
	"OnKeyDown",
	"OnKeyUp",
};

using namespace TBaluRenderEnums;

class TBaluClassInternal
{
public:
	TBaluSprite sprite;
	TSMethod* events[MAX_EVENTS];
	TDynArr* objects_array;
	std::string events_code[MAX_EVENTS];
	std::string class_members;
	std::string class_name;
	void Clear(){
		for (int i = 0; i <= MAX_EVENTS; i++)
		{
			events[i] = NULL;
		}
	}
};


TBaluClass::TBaluClass()
{
	p.reset(new TBaluClassInternal());
	p->Clear();
}
TBaluClass::~TBaluClass()
{

}
void TBaluClass::SetEvent(TBaluEvent use_event, const char* code)
{
	p->events_code[(int)use_event] = code;
}
void TBaluClass::SetMembers(const char* code)
{
	p->class_members = code;
}



class TBaluEngineInternal
{
public:
	std::unique_ptr<TBaluRender> render;
	//TVirtualMachine vmachine;

	std::vector<TStaticValue> static_objects;

	TSyntaxAnalyzer syntax;
	TProgram program;
	//
	b2World* phys_world;
	bool keyboard_init;
	unsigned char keystates[256];
	bool mouse_init;
	bool mouse_buttons[3];
	TVec2i mouse_client_pos;
	std::map<std::string, TTextureId> textures;
	std::map<std::string, TBaluMaterial> materials;
	std::map<std::string, TBaluShape> shapes;
	std::map<std::string, TBaluSprite> sprites;
	std::map<std::string, TBaluClass> classes;
	std::vector<TBaluInstance> start_instances;
	//global script classes
	TBaluMouse* Mouse;
	TBaluKeyboard* Keyboard;
	TBaluTime* Time;
	TBaluScreen* Screen;
};
void TBaluEngine::CallEvent(TBaluEvent use_event, int par0)
{
	std::map<std::string, TBaluClass>::iterator i;
	for (i = p->classes.begin(); i != p->classes.end(); i++)
	{
		TBaluClass* cl = &i->second;
		for (int k = 0; k < cl->p->objects_array->v->size(); k += cl->p->objects_array->el_class->GetSize())//TODO проход по всем объектам не нужен, можно в начале опеределить для каких объектов как события вызывать
			if (cl->p->events[(int)use_event] != NULL)
			{
			TBaluInstance* inst = (TBaluInstance*)&cl->p->objects_array->v[k];
			//TODO
			//vmachine.Push((int)inst);
			//vmachine.Push(par0);
			//vmachine.Execute(cl->events[use_event],vmachine.GetHigh(),(int*)inst);
			//inst=(TBaluInstance*)cl->objects_array->Get(k);
			}
	}
}
TBaluEngine::TBaluEngine(int hWnd, TVec2i use_size)
{
	p.reset(new TBaluEngineInternal());
	p->render.reset(new TBaluRender(hWnd, use_size));///,vmachine(100000),syntax()
	p->keyboard_init = false;
	p->mouse_init = false;
	p->phys_world = NULL;
	p->Mouse = NULL;
	p->Time = NULL;
	p->Screen = NULL;
}
TBaluEngine::~TBaluEngine()
{
	//vmachine.DestructStaticVars();
	delete p->phys_world;
}

void TBaluEngine::SetViewport(TVec2i use_size)
{
	p->render->Set.Viewport(use_size);
}
void TBaluEngine::AddMaterial(char* mat_name, char* tex_path, TVec4 use_color)
{
	using namespace std;
	typedef map<string, TTextureId>::iterator iterator;
	iterator t = p->textures.find(tex_path);
	if (t == p->textures.end())
	{
		typedef pair<string, TTextureId> Tex_Pair;
		pair<iterator, bool> t_t = p->textures.insert(Tex_Pair(tex_path, TTextureId(p->render->Texture.Create(tex_path))));
		t = t_t.first;
	}
	TBaluMaterial* mat = &p->materials[mat_name];
	mat->color = use_color;
	mat->texture = t->second;
}
void TBaluEngine::AddShape(char* shape_name, const TBaluShape& use_shape)
{
	p->shapes[shape_name] = use_shape;
}
void TBaluEngine::AddSprite(char* sprite_name, char* shape_name, char* mat_name, TVec2 use_size, float use_local_angle, TVec2 use_local_pos, float use_z_bias)
{
	TBaluSprite* sprite = &p->sprites[sprite_name];
	sprite->shape = p->shapes[shape_name];
	sprite->material = p->materials[mat_name];
	sprite->local_angle = use_local_angle;
	sprite->size = use_size;
	sprite->local_pos = use_local_pos;
	sprite->z_bias = use_z_bias;
}
void TBaluEngine::AddClass(char* class_name, char* sprite_name, const TBaluClass& use_class)
{
	TBaluClass* cl = &p->classes[class_name];
	//*cl = use_class;
	cl->p->class_name = class_name;
	cl->p->sprite = p->sprites[sprite_name];
}
void TBaluEngine::AddInstance(char* class_name, TVec2 use_pos, float use_angle)
{
	p->start_instances.push_back(TBaluInstance());//TODO проверить наличие имени класса
	TBaluInstance* inst = &p->start_instances.back();
	TBaluClass* cl = &p->classes[class_name];
	inst->angle = use_angle;
	inst->pos = use_pos;
	inst->sprite = cl->p->sprite;
	inst->class_pointer = cl;
}
void TBaluEngine::OnMouseLeftUp()
{
	CallEvent(TBaluEvent::EVENT_GLOBALMOUSEUP, LEFT);
}
void TBaluEngine::OnMouseLeftDown()
{
	CallEvent(TBaluEvent::EVENT_GLOBALMOUSEDOWN, LEFT);
}
void TBaluEngine::OnMouseRightUp()
{
	CallEvent(TBaluEvent::EVENT_GLOBALMOUSEUP, RIGHT);
}
void TBaluEngine::OnMouseRightDown()
{
	CallEvent(TBaluEvent::EVENT_GLOBALMOUSEDOWN, RIGHT);
}
void TBaluEngine::OnMouseMiddleUp()
{
	CallEvent(TBaluEvent::EVENT_GLOBALMOUSEUP, MIDDLE);
}
void TBaluEngine::OnMouseMiddleDown()
{
	CallEvent(TBaluEvent::EVENT_GLOBALMOUSEDOWN, MIDDLE);
}
TVec2 TBaluEngine::ScreenToWorld(const TVec2& v)
{
	return p->Screen->Pos + (v + TVec2(-0.5, -0.5)).ComponentMul(p->Screen->Size);
}
TVec2 TBaluEngine::WorldToScreen(const TVec2& v)
{
	return (v - p->Screen->Pos) / p->Screen->Size + TVec2(-0.5f, -0.5f);
}
void TBaluEngine::OnMouseMove(TVec2i use_client_mouse_pos)
{
	TVec2i screen_size = p->render->ScreenSize();
	p->Mouse->Pos = TVec2(use_client_mouse_pos[0] / (float)screen_size[0], 1 - use_client_mouse_pos[1] / (float)screen_size[1]);
	p->Mouse->WorldPos = ScreenToWorld(p->Mouse->Pos);
	//TODO вызвать OnMouseMove
}
void TBaluEngine::OnMouseScroll(float delta)
{
	delta /= 120.f;
	CallEvent(TBaluEvent::EVENT_GLOBALMOUSEWHEEL, *(int*)&delta);
}
void TBaluEngine::UpdateKeyStates(unsigned char new_keystates[])
{
	if (!p->keyboard_init)
	{
		p->keyboard_init = true;
		memcpy(&p->keystates[0], &new_keystates[0], 256);
		return;
	}
	for (int i = 0; i < 256; i++)
	{
		int balu_char = ToBaluChar(i);
		int balu_spec_key = -1;
		if (balu_char != -1)
			p->Keyboard->chars[balu_char] = (new_keystates[i] & 128) != 0;
		else
		{
			balu_spec_key = ToBaluSpecKey(i);
			if (balu_spec_key != -1)
				p->Keyboard->special[balu_spec_key] = new_keystates[i];
		}
		if (p->keystates[i] != new_keystates[i])
		{
		}
	}
}
void TBaluEngine::UpdateMouseState(bool lpressed, bool mpressed, bool rpressed, TVec2i use_client_mouse_pos)
{
	if (!p->mouse_init)
	{
		p->mouse_init = true;
		p->mouse_buttons[0] = lpressed;
		p->mouse_buttons[1] = mpressed;
		p->mouse_buttons[2] = rpressed;
		p->mouse_client_pos = use_client_mouse_pos;
	}
	else
	{
		if (p->Mouse != NULL)
		{
			p->Mouse->Button.Left = lpressed;
			p->Mouse->Button.Right = rpressed;
			p->Mouse->Button.Middle = mpressed;
		}
		if (p->mouse_buttons[0] != lpressed)
		{
			if (lpressed)OnMouseLeftDown(); else OnMouseLeftUp();
		}
		if (p->mouse_buttons[1] != mpressed)
		{
			if (mpressed)OnMouseMiddleDown(); else OnMouseMiddleUp();
		}
		if (p->mouse_buttons[2] != rpressed)
		{
			if (rpressed)OnMouseRightDown(); else OnMouseRightUp();
		}
		p->mouse_buttons[0] = lpressed;
		p->mouse_buttons[1] = mpressed;
		p->mouse_buttons[2] = rpressed;
		if (p->mouse_client_pos != use_client_mouse_pos)
		{
			OnMouseMove(use_client_mouse_pos);
			p->mouse_client_pos = use_client_mouse_pos;
		}
	}
}

void TBaluScreen::SetPos(TVec2& use_pos)
{
	Pos = use_pos;
	//TODO сделать в baluengine
	engine->p->Mouse->WorldPos = engine->ScreenToWorld(engine->p->Mouse->Pos);
}


void TBaluScreen::SetSize(TVec2& use_size)
{
	Size = use_size;
	//TODO сделать в baluengine
	engine->p->Mouse->WorldPos = engine->ScreenToWorld(engine->p->Mouse->Pos);
}

class MyRayCastCallback : public b2RayCastCallback
{
public:
	virtual ~MyRayCastCallback() {}

	/// Called for each fixture found in the query. You control how the ray cast
	/// proceeds by returning a float:
	/// return -1: ignore this fixture and continue
	/// return 0: terminate the ray cast
	/// return fraction: clip the ray to this point
	/// return 1: don't clip the ray and continue
	/// @param fixture the fixture hit by the ray
	/// @param point the point of initial intersection
	/// @param normal the normal vector at the point of intersection
	/// @return -1 to filter, 0 to terminate, fraction to clip the ray for
	/// closest hit, 1 to continue
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction)
	{
		return 1;
	}
};

void TBaluEngine::Start()
{
	//create and compile script
	const int source_len = 10e6;
	char* source = new char[source_len];
	int c = 0;

	c = sprintf_s(source, source_len, "\n class TGame \n{");

	char* script_base_classes = NULL;
	{
		TFileData file("../../BaluScript/Source/NativeTypes/base_types.bscript", "rb");
		char* base_source = new char[source_len];
		base_source = file.ReadAll();
		base_source[file.GetSize()] = '\0';
		script_base_classes = base_source;
	}

	c += sprintf_s(&source[c], source_len - c, "%s", script_base_classes);
	c += sprintf_s(&source[c], source_len - c, "%s", script_mouse);
	c += sprintf_s(&source[c], source_len - c, "%s", script_keyboard);//TODO это же можно одной коммандой сделать
	c += sprintf_s(&source[c], source_len - c, "%s", script_time);
	c += sprintf_s(&source[c], source_len - c, "%s", script_screen);
	c += sprintf_s(&source[c], source_len - c, "%s", script_texture);
	c += sprintf_s(&source[c], source_len - c, "%s", script_material);
	c += sprintf_s(&source[c], source_len - c, "%s", script_shape);
	c += sprintf_s(&source[c], source_len - c, "%s", script_body);
	c += sprintf_s(&source[c], source_len - c, "%s", script_sprite);
	c += sprintf_s(&source[c], source_len - c, "%s", script_instance);
	std::map<std::string, TBaluClass>::iterator i;

	for (i = p->classes.begin(); i != p->classes.end(); i++)
	{
		TBaluClass* cl = &i->second;
		c += sprintf_s(&source[c], source_len - c,
			"\n class T%s:TInstance\
						\n {\
									\n\t %s"
									, cl->p->class_name.c_str(), cl->p->class_members.c_str());
		for (int k = 0; k < MAX_EVENTS; k++){
			if (!cl->p->events_code[k].empty())
			{
				switch ((TBaluEvent)k)
				{
				case TBaluEvent::EVENT_CREATE:
				case TBaluEvent::EVENT_DESTROY:
				case TBaluEvent::EVENT_STEP:
				case TBaluEvent::EVENT_GLOBALMOUSEMOVE:
				{
					c += sprintf_s(&source[c], source_len - c,
						"\n func %s\
						\n {\
						\n %s\
						\n }", event_name[k], cl->p->events_code[k].c_str());
				}
					break;
				case TBaluEvent::EVENT_GLOBALMOUSEDOWN:
				case TBaluEvent::EVENT_GLOBALMOUSEUP:
				{
					c += sprintf_s(&source[c], source_len - c,
						"\n func %s(TMouseButton button)\
													\n {\
																				\n %s\
																																		\n }", event_name[k], cl->p->events_code[k].c_str());
				}
					break;
				case TBaluEvent::EVENT_GLOBALMOUSEWHEEL:
				{
					c += sprintf_s(&source[c], source_len - c,
						"\n func %s(float delta)\
													\n {\
																				\n %s\
																																		\n }", event_name[k], cl->p->events_code[k].c_str());
				}
					break;
				case TBaluEvent::EVENT_KEYDOWN:
				case TBaluEvent::EVENT_KEYUP:
				{
					c += sprintf_s(&source[c], source_len - c,
						"\n func %s(TKey key)\
													\n {\
																				\n %s\
																																		\n }", event_name[k], cl->p->events_code[k].c_str());
				}
					break;
				default:assert(false);
				}
			}
		}
		c += sprintf_s(&source[c], source_len - c, "%s", "\n }");
	}

	c += sprintf_s(&source[c], source_len - c, "%s", script_global_vars);

	for (i = p->classes.begin(); i != p->classes.end(); i++)
	{
		TBaluClass* cl = &i->second;
		c += sprintf_s(&source[c], source_len - c,
			"\n TDynArray<T%s> static %s;"
			, cl->p->class_name.c_str(), cl->p->class_name.c_str());
	}
	c += sprintf_s(&source[c], source_len - c,
		"\n }");

	char buf1[1000];

	FILE *stream;
	fopen_s(&stream, "baluscript.bscript", "w");
	fprintf(stream, "%s", source);
	fclose(stream);
	TTime time;

	TBaluMouse::LinkExternMethods(&p->syntax);
	TBaluKeyboard::LinkExternMethods(&p->syntax);
	TBaluTime::LinkExternMethods(&p->syntax);
	TBaluScreen::LinkExternMethods(&p->syntax);
	TBaluShape::LinkExternMethods(&p->syntax);
	TBaluBody::LinkExternMethods(&p->syntax);
	TBaluMaterial::LinkExternMethods(&p->syntax);
	TBaluSprite::LinkExternMethods(&p->syntax);
	TBaluInstance::LinkExternMethods(&p->syntax);

	try
	{
		p->syntax.Compile(source, time);
	}
	catch (std::string ex)
	{

	}

	InitializeStaticClassFields(p->syntax.static_fields, p->static_objects);
	InitializeStaticVariables(p->syntax.static_variables, p->static_objects);

	delete source;
	source = NULL;

	for (i = p->classes.begin(); i != p->classes.end(); i++)
	{
		TBaluClass* cl = &i->second;
		char buff[1000];
		for (int k = 0; k < MAX_EVENTS; k++)
			if (!cl->p->events_code[k].empty())
			{
			switch ((TBaluEvent)k)
			{
			case TBaluEvent::EVENT_CREATE:
			case TBaluEvent::EVENT_DESTROY:
			case TBaluEvent::EVENT_STEP:
			case TBaluEvent::EVENT_GLOBALMOUSEMOVE:
				sprintf_s(buff, "func TGame.T%s.%s", cl->p->class_name.c_str(), event_name[k]);
				break;
			case TBaluEvent::EVENT_GLOBALMOUSEDOWN:
			case TBaluEvent::EVENT_GLOBALMOUSEUP:
				sprintf_s(buff, "func TGame.T%s.%s(TMouseButton button)", cl->p->class_name.c_str(), event_name[k]);
				break;
			case TBaluEvent::EVENT_GLOBALMOUSEWHEEL:
				sprintf_s(buff, "func TGame.T%s.%s(float delta)", cl->p->class_name.c_str(), event_name[k]);
				break;
			case TBaluEvent::EVENT_KEYDOWN:
			case TBaluEvent::EVENT_KEYUP:
				sprintf_s(buff, "func TGame.T%s.%s(TKey key)", cl->p->class_name.c_str(), event_name[k]);
				break;
			default:assert(false);
			}
			cl->p->events[k] = p->syntax.GetMethod(buff);
			}
	}

	for (i = p->classes.begin(); i != p->classes.end(); i++)
	{
		TBaluClass* cl = &i->second;
		char buff[1000];
		sprintf_s(buff, "TGame.%s", cl->p->class_name.c_str());
		cl->p->objects_array = (TDynArr*)p->static_objects[p->syntax.GetStaticField(buff)->GetOffset()].get();
	}

	//получаем необходимые для взаимодействия со скриптом адреса
	p->Time = (TBaluTime*)p->static_objects[p->syntax.GetStaticField("TGame.Time")->GetOffset()].get();
	p->Mouse = (TBaluMouse*)p->static_objects[p->syntax.GetStaticField("TGame.Mouse")->GetOffset()].get();
	p->Keyboard = (TBaluKeyboard*)p->static_objects[p->syntax.GetStaticField("TGame.Keyboard")->GetOffset()].get();
	p->Screen = (TBaluScreen*)p->static_objects[p->syntax.GetStaticField("TGame.Screen")->GetOffset()].get();


	//инициализируем мир box2d
	b2AABB aabb;
	aabb.lowerBound.Set(-1000, -1000);
	aabb.upperBound.Set(1000, 10000);
	p->phys_world = new b2World(b2Vec2(0, -10));
	//

	{
		b2BodyDef bd;
		bd.position.Set(0.0f, 0.0f);
		b2Body* body = p->phys_world->CreateBody(&bd);

		b2EdgeShape shape;
		shape.Set(b2Vec2(50.0f, 0.0f), b2Vec2(-50.0f, 0.0f));

		body->CreateFixture(&shape, 0.0f);
		MyRayCastCallback my;
		p->phys_world->RayCast(&my, b2Vec2(0, -50), b2Vec2(0, 50));
	}		

	p->Time->engine = this;
	p->Mouse->engine = this;
	p->Screen->engine = this;
	p->Screen->Size = TVec2(1, 1);
	p->Screen->Pos = TVec2(0, 0);

	//инициализируем instances
	for (int i = 0; i < p->start_instances.size(); i++)
	{
		TDynArr* obj_arr = p->start_instances[i].class_pointer->p->objects_array;
		obj_arr->EmplaceBack(p->static_objects);
		TBaluInstance* inst = (TBaluInstance*)(obj_arr->GetElement(obj_arr->GetSize() - 1));
		*inst = p->start_instances[i];

		TBaluShape* shape = &inst->sprite.shape;
		b2PolygonShape shape_def;
		shape_def.SetAsBox(shape->box_size_x, shape->box_size_y);
		//if(instances[i].object->sprite->shape!=NULL)
		{
			b2BodyDef body_def;
			body_def.position.Set(inst->pos[0], inst->pos[1]);
			if (shape->density != 0)
				body_def.type = b2_dynamicBody;
			//body_def.fixedRotation=true;
			body_def.angle = inst->angle;
			shape->body = p->phys_world->CreateBody(&body_def);
			shape->body->CreateFixture(&shape_def, shape->density);
			//shape->UpdatePhysShape();
		}//else
		//	shape->type=TBaluShape::FT_NONE;

		//int m=inst->class_pointer->events[EVENT_CREATE];
		//if(m!=-1)
		//{
		//	vmachine.Push((int)inst);
		//	vmachine.Execute(m,NULL,(int*)inst);
		//}
	}

	p->render->Set.VSync(true);
}
void TBaluEngine::Step(float step, double time)
{
	//scripts globals
	p->Time->Step = step;
	p->Time->Current = time;
	//scripts

	float room_size = 40;

	TMatrix<float, 4> ortho_m = TMatrix<float, 4>::GetOrtho(TVec2(0, 20), TVec2(1, 1)*room_size*1.1, -10, 10);
	TMatrix<float, 4> ortho_m_inv = ortho_m.GetInverted();
	p->render->Set.Projection(ortho_m);

	std::map<std::string, TBaluClass>::iterator i;
	for (i = p->classes.begin(); i != p->classes.end(); i++)
	{
		TBaluClass* cl = &i->second;
		for (int k = 0; k < cl->p->objects_array->v->size(); k++)
			if (cl->p->events[(int)TBaluEvent::EVENT_STEP] != NULL)
			{
			TBaluInstance* inst = (TBaluInstance*)(&(*cl->p->objects_array->v)[k]);
			std::vector<TStackValue> without_params;
			TStackValue result;
			TStackValue obj(true, cl->p->objects_array->el_class);
			obj.SetAsReference(inst);
			//cl->events[EVENT_STEP]->Run(static_objects, without_params, result, obj);
			}
	}
	//physics

	for (i = p->classes.begin(); i != p->classes.end(); i++)
	{
		TBaluClass* cl = &i->second;
		for (int k = 0; k < cl->p->objects_array->GetSize(); k++)
		{
			TBaluInstance* inst = (TBaluInstance*)(cl->p->objects_array->GetElement(k));
			if (inst->sprite.shape.type == TBaluShape::FT_NONE)continue;
			b2Vec2 v = inst->sprite.shape.body->GetPosition();
			inst->pos[0] = v.x;
			inst->pos[1] = v.y;
			inst->angle = inst->sprite.shape.body->GetAngle();
		}
	}
	//draw
	p->render->BeginScene();
	{
		p->render->Set.ClearColor(0, 0, 0);
		p->render->Set.Color(1, 1, 1, 1);
		p->render->Clear(true);

		p->render->Texture.Enable(true);

		p->render->AlphaTest.Enable(true);
		p->render->Blend.Enable(true);

		p->render->AlphaTest.Func(">=", 0.1);
		p->render->Blend.Func("dc*(1-sa)+sc*sa");

		//glEnable(GL_LIGHTING);
		//glEnable(GL_LIGHT0);
		//TVec<float,4> light_position(Mouse->WorldPos[0],Mouse->WorldPos[1],0.3,1);
		//GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
		//GLfloat mat_shininess[]={50.0};
		//GLfloat white_light[]={1.0,1.0,1.0,1.0};
		//GLfloat quad_att[]={0.01,0,0,0};


		//glClearColor(0.0,0.0,0.0,0.0);
		//glShadeModel(GL_SMOOTH);
		//glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		//glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
		//glLightfv(GL_LIGHT0,GL_POSITION, (GLfloat*)&light_position);
		//glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
		//glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);
		//glLightfv(GL_LIGHT0,GL_LINEAR_ATTENUATION,quad_att);

		for (i = p->classes.begin(); i != p->classes.end(); i++)
		{
			TBaluClass* cl = &i->second;
			for (int k = 0; k < cl->p->objects_array->GetSize(); k++)
			{
				TBaluInstance* inst = (TBaluInstance*)(cl->p->objects_array->GetElement(k));
				p->render->Texture.Bind(inst->sprite.material.texture);
				//p->render->Set.Color(inst->material.color[0],inst->material.color[1],inst->material.color[2]);
				TQuad<float, 3> fscr;
				TQuad<float, 2> fscr_coords;
				TQuad<float, 3> fscr_normals;
				fscr_normals[0] = TVec3(0, 0, 1);
				fscr_normals[1] = fscr_normals[0];
				fscr_normals[2] = fscr_normals[0];
				fscr_normals[3] = fscr_normals[0];
				fscr.Set(
					inst->pos + inst->sprite.local_pos,
					inst->sprite.size,
					inst->angle + inst->sprite.local_angle,
					inst->sprite.z_bias);
				fscr_coords.Set(TVec2(0.5, 0.5), 1, 0);

				TStreamsDesc desc;
				desc.AddStream(TStream::Vertex, TDataType::Float, 3, &fscr);
				desc.AddStream(TStream::Normal, TDataType::Float, 3, &fscr_normals);
				desc.AddStream(TStream::TexCoord, TDataType::Float, 2, &fscr_coords);
				p->render->Draw(desc, TPrimitive::Quads, 4);
				//p->render->Quads.Begin();
				//p->render->Quads.Draw(fscr,fscr_coords,fscr_normals);
				//p->render->Quads.End();
			}
		}

		p->render->Texture.Enable(false);
		p->render->AlphaTest.Enable(false);
		p->render->Blend.Enable(false);
	}
	p->render->EndScene();
	//if(step<0.015f)
	for (int i = 0; i < 5; i++)
		p->phys_world->Step(0.005, 1, 1);
	//else
	{
		//phys_world->Step(0.0035f,30,10);
		/*int iter_count=int(step/0.015f)+1;
		for(int i=0;i<iter_count;i++)
		phys_world->Step(step/iter_count,10);*/
	}
}