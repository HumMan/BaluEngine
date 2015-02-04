#pragma once

#include <memory>

#include "Resources.h"

#include "EngineInterfaces\IDirector.h"

class TGameInternal;
class TBaluWorldInstance;
class TRender;

class TDirector: public EngineInterface::IDirector
{
	std::unique_ptr < TGameInternal > p;

	void Step(float step);
public:
	TDirector();
	void SetWorldInstance(TBaluWorldInstance* world_instance);
	void SetWorldInstance(EngineInterface::IBaluWorldInstance* world_instance);
	void SetRenderWorldCallback(RenderWorldCallback callback);
	int Initialize();
	void MainLoop();
	TResources* GetResources();
	~TDirector();

	std::string GetBasePath();

	TVec2i GetScreenSize();
};