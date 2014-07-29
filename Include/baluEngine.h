#pragma once

#include <baluRender.h>
#include <baluScript.h>
#include <box2d.h>

#include "../Source/scriptClasses.h""

enum TBaluEvent
{
	EVENT_CREATE,
	EVENT_DESTROY,
	EVENT_STEP,
	EVENT_DRAW,//TODO что делать если здесь произойдет перемещение тела и оно выйдет из обл видимости или войдет в неё
	EVENT_GLOBALMOUSEDOWN,
	EVENT_GLOBALMOUSEUP,
	EVENT_GLOBALMOUSEMOVE,
	EVENT_GLOBALMOUSEWHEEL,
	EVENT_KEYDOWN,
	EVENT_KEYUP,
	MAX_EVENTS
};

const static char* event_name[MAX_EVENTS]=
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

class TBaluClass
{
	friend class TBaluEngine;
private:
	TBaluSprite sprite;
	TSMethod* events[MAX_EVENTS];
	TDynArr* objects_array;
	std::string events_code[MAX_EVENTS];
	std::string class_members;
	std::string class_name;
	void Clear(){
		for(int i=0;i<=MAX_EVENTS;i++)
		{
			events[i]=NULL;
		}
	}
public:
	TBaluClass(){
		Clear();
	}
	void SetEvent(TBaluEvent use_event,const char* code){
		events_code[use_event]=code;
	}
	void SetMembers(const char* code){
		class_members=code;
	}
};

#include <map>

class TBaluEngine
{
	friend struct TBaluMouse;
	friend struct TBaluScreen;
	friend struct TBaluTime;
private:
	TBaluRender render;
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
public:
	std::map<std::string,TTextureId> textures;
	std::map<std::string,TBaluMaterial> materials;
	std::map<std::string,TBaluShape> shapes;
	std::map<std::string,TBaluSprite> sprites;
	std::map<std::string,TBaluClass> classes;
	std::vector<TBaluInstance> start_instances;
	//global script classes
	TBaluMouse* Mouse;
	TBaluKeyboard* Keyboard;
	TBaluTime* Time;
	TBaluScreen* Screen;
	void CallEvent(TBaluEvent use_event,int par0)
	{
		std::map<std::string,TBaluClass>::iterator i;
		for(i=classes.begin();i!=classes.end();i++)
		{
			TBaluClass* cl=&i->second;
			for(int k=0;k<cl->objects_array->v->size();k+=cl->objects_array->el_class->GetSize())//TODO проход по всем объектам не нужен, можно в начале опеределить для каких объектов как события вызывать
				if(cl->events[use_event]!=NULL)
				{
					TBaluInstance* inst=(TBaluInstance*)&cl->objects_array->v[k];
					//TODO
					//vmachine.Push((int)inst);
					//vmachine.Push(par0);
					//vmachine.Execute(cl->events[use_event],vmachine.GetHigh(),(int*)inst);
					//inst=(TBaluInstance*)cl->objects_array->Get(k);
				}
		}
	}
public:
	TBaluEngine(HWND hWnd,TVec2i use_size)
		:render(hWnd,use_size)///,vmachine(100000),syntax()
	{
		keyboard_init=false;
		mouse_init=false;
		phys_world=NULL;
		Mouse=NULL;
		Time=NULL;
		Screen=NULL;
	}
	~TBaluEngine(){
		//vmachine.DestructStaticVars();
		delete phys_world;
	}
	void Start();
	void Step(float step,double time);
	void SetViewport(TVec2i use_size)
	{
		render.Set.Viewport(use_size);
	}
	void AddMaterial(char* mat_name,char* tex_path,TVec4 use_color)
	{
		using namespace std;
		typedef map<string,TTextureId>::iterator iterator;
		iterator t=textures.find(tex_path);
		if(t==textures.end())
		{
			typedef pair<string,TTextureId> Tex_Pair;
			pair<iterator,bool> t_t=textures.insert(Tex_Pair(tex_path,TTextureId(render.Texture.Create(tex_path))));
			t=t_t.first;
		}
		TBaluMaterial* mat=&materials[mat_name];
		mat->color=use_color;
		mat->texture=t->second;
	}
	void AddShape(char* shape_name,const TBaluShape& use_shape)
	{
		shapes[shape_name]=use_shape;
	}
	void AddSprite(char* sprite_name,char* shape_name,char* mat_name,TVec2 use_size,float use_local_angle,TVec2 use_local_pos,float use_z_bias)
	{
		TBaluSprite* sprite=&sprites[sprite_name];
		sprite->shape=shapes[shape_name];
		sprite->material=materials[mat_name];
		sprite->local_angle=use_local_angle;
		sprite->size=use_size;
		sprite->local_pos=use_local_pos;
		sprite->z_bias=use_z_bias;
	}
	void AddClass(char* class_name,char* sprite_name,const TBaluClass& use_class)
	{
		TBaluClass* cl=&classes[class_name];
		*cl=use_class;
		cl->class_name=class_name;
		cl->sprite=sprites[sprite_name];
	}
	void AddInstance(char* class_name,TVec2 use_pos,float use_angle)
	{
		start_instances.push_back(TBaluInstance());//TODO проверить наличие имени класса
		TBaluInstance* inst = &start_instances.back();
		TBaluClass* cl=&classes[class_name];
		inst->angle=use_angle;
		inst->pos=use_pos;
		inst->sprite=cl->sprite;
		inst->class_pointer=cl;
	}
	void OnMouseLeftUp()
	{
		CallEvent(EVENT_GLOBALMOUSEUP,LEFT);
	}
	void OnMouseLeftDown()
	{
		CallEvent(EVENT_GLOBALMOUSEDOWN,LEFT);
	}
	void OnMouseRightUp()
	{
		CallEvent(EVENT_GLOBALMOUSEUP,RIGHT);
	}
	void OnMouseRightDown()
	{
		CallEvent(EVENT_GLOBALMOUSEDOWN,RIGHT);
	}
	void OnMouseMiddleUp()
	{
		CallEvent(EVENT_GLOBALMOUSEUP,MIDDLE);
	}
	void OnMouseMiddleDown()
	{
		CallEvent(EVENT_GLOBALMOUSEDOWN,MIDDLE);
	}
	TVec2 ScreenToWorld(const TVec2& v)
	{
		return Screen->Pos+(v+TVec2(-0.5,-0.5)).ComponentMul(Screen->Size);
	}
	TVec2 WorldToScreen(const TVec2& v)
	{
		return (v-Screen->Pos)/Screen->Size+TVec2(-0.5f,-0.5f);
	}
	void OnMouseMove(TVec2i use_client_mouse_pos)
	{
		TVec2i screen_size=render.ScreenSize();
		Mouse->Pos=TVec2(use_client_mouse_pos[0]/(float)screen_size[0],1-use_client_mouse_pos[1]/(float)screen_size[1]);
		Mouse->WorldPos=ScreenToWorld(Mouse->Pos);
		//TODO вызвать OnMouseMove
	}
	void OnMouseScroll(float delta)
	{
		delta/=120.f;
		CallEvent(EVENT_GLOBALMOUSEWHEEL,*(int*)&delta);
	}
	void UpdateKeyStates(unsigned char new_keystates[])
	{
		if(!keyboard_init)
		{
			keyboard_init=true;
			memcpy(&keystates[0],&new_keystates[0],256);
			return;
		}
		for(int i=0;i<256;i++)
		{
			int balu_char=ToBaluChar(i);
			int balu_spec_key=-1;
			if(balu_char!=-1)
				Keyboard->chars[balu_char]=(new_keystates[i]&128)!=0;
			else
			{
				balu_spec_key=ToBaluSpecKey(i);
				if(balu_spec_key!=-1)
					Keyboard->special[balu_spec_key]=new_keystates[i];
			}
			if(keystates[i]!=new_keystates[i])
			{
			}
		}
	}
	void UpdateMouseState(bool lpressed,bool mpressed,bool rpressed,TVec2i use_client_mouse_pos)
	{
		if(!mouse_init)
		{
			mouse_init=true;
			mouse_buttons[0]=lpressed;
			mouse_buttons[1]=mpressed;
			mouse_buttons[2]=rpressed;
			mouse_client_pos=use_client_mouse_pos;
		}else
		{
			if(Mouse!=NULL)
			{
				Mouse->Button.Left=lpressed;
				Mouse->Button.Right=rpressed;
				Mouse->Button.Middle=mpressed;
			}
			if(mouse_buttons[0]!=lpressed)
			{
				if(lpressed)OnMouseLeftDown();else OnMouseLeftUp();
			}
			if(mouse_buttons[1]!=mpressed)
			{
				if(mpressed)OnMouseMiddleDown();else OnMouseMiddleUp();
			}
			if(mouse_buttons[2]!=rpressed)
			{
				if(rpressed)OnMouseRightDown();else OnMouseRightUp();
			}
			mouse_buttons[0]=lpressed;
			mouse_buttons[1]=mpressed;
			mouse_buttons[2]=rpressed;
			if(mouse_client_pos!=use_client_mouse_pos)
			{
				OnMouseMove(use_client_mouse_pos);
				mouse_client_pos=use_client_mouse_pos;
			}
		}
	}
};
