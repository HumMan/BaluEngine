#pragma once

#include <map>

#include <baluScript.h>

#include <baluRender.h>
#include <Box2D.h>

#include "exportMacro.h"

class TBaluEngine;

namespace pugi
{
	class xml_node;
}

class BALUENGINEDLL_API  TBaluEngineTest
{
public:
	void Step(float step, double time);
};
//
//
//
//
//
//class TBaluEngineInternal;
//
//
//class BALUENGINEDLL_API  TBaluEngine
//{
//private:
//	std::unique_ptr<TBaluEngineInternal> p;
//
//	int MainLoop();
//public:
//
//	//void CallEvent(TBaluEvent use_event, int par0);
//public:
//	TBaluEngine();
//	TBaluEngine(int hWnd, TVec2i use_size);
//	~TBaluEngine();
//	void Start();
//	void Step(float step, double time);
//	void SetViewport(TVec2i use_size);
//
//	void OnMouseLeftUp();
//	void OnMouseLeftDown();
//	void OnMouseRightUp();
//	void OnMouseRightDown();
//	void OnMouseMiddleUp();
//	void OnMouseMiddleDown();
//	void OnMouseMove(TVec2i use_client_mouse_pos);
//	void OnMouseScroll(float delta);
//	void UpdateKeyStates(unsigned char new_keystates[]);
//	void UpdateMouseState(bool lpressed, bool mpressed, bool rpressed, TVec2i use_client_mouse_pos);
//};

//tesing only
//BALUENGINEDLL_API int SDLTest();
BALUENGINEDLL_API int MainLoop();