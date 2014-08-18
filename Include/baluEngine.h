#pragma once

#ifdef BALUENGINEDLL_EXPORTS
#define BALUENGINEDLL_API __declspec(dllexport) 
#else
#define BALUENGINEDLL_API __declspec(dllimport) 
#endif

#include <memory>
#include <windows.h>

#include <baluLib.h>

enum class TBaluEvent
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

const int MAX_EVENTS = (int)TBaluEvent::MAX_EVENTS;

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

class TBaluClassInternal;
class BALUENGINEDLL_API TBaluClass
{
	friend class TBaluEngine;
private:	
	std::unique_ptr<TBaluClassInternal> p;
public:
	 TBaluClass();
	~TBaluClass();
	void SetEvent(TBaluEvent use_event, const char* code);
	void SetMembers(const char* code);
};

class TBaluShape;
class TBaluEngineInternal;
class BALUENGINEDLL_API TBaluEngine
{
	friend struct TBaluMouse;
	friend struct TBaluScreen;
	friend struct TBaluTime;
private:
	std::unique_ptr<TBaluEngineInternal> p;
public:
	
	void CallEvent(TBaluEvent use_event, int par0);
public:
	TBaluEngine(HWND hWnd, TVec2i use_size);
	~TBaluEngine();
	void Start();
	void Step(float step,double time);
	void SetViewport(TVec2i use_size);
	void AddMaterial(char* mat_name, char* tex_path, TVec4 use_color);
	void AddShape(char* shape_name, const TBaluShape& use_shape);
	void AddSprite(char* sprite_name, char* shape_name, char* mat_name, TVec2 use_size, float use_local_angle, TVec2 use_local_pos, float use_z_bias);
	void AddClass(char* class_name, char* sprite_name, const TBaluClass& use_class);
	void AddInstance(char* class_name, TVec2 use_pos, float use_angle);
	void OnMouseLeftUp();
	void OnMouseLeftDown();
	void OnMouseRightUp();
	void OnMouseRightDown();
	void OnMouseMiddleUp();
	void OnMouseMiddleDown();
	TVec2 ScreenToWorld(const TVec2& v);
	TVec2 WorldToScreen(const TVec2& v);
	void OnMouseMove(TVec2i use_client_mouse_pos);
	void OnMouseScroll(float delta);
	void UpdateKeyStates(unsigned char new_keystates[]);
	void UpdateMouseState(bool lpressed, bool mpressed, bool rpressed, TVec2i use_client_mouse_pos);
};
