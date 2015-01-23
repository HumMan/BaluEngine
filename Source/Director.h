#pragma once

#include <memory>

class TGameInternal;
class TBaluWorldInstance;
class TRender;

class TDirector
{
	std::unique_ptr < TGameInternal > p;

	void RenderWorld(TBaluWorldInstance* world, TRender* render);
	void Step(float step);
public:

	void MainLoop();
};