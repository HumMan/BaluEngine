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

	//special only for testing
	void Initialize(void* handle);
	void BeginFrame();
	void EndFrame();
	//
	TDirector();
	void SetWorldInstance(TBaluWorldInstance* world_instance);
	void SetWorldInstance(EngineInterface::IBaluWorldInstance* world_instance);
	void SetRenderWorldCallback(RenderWorldCallback callback);
	
	int Initialize(bool create_window);
	TResources* GetResources();
	~TDirector();

	std::string GetBasePath();
	TVec2i GetScreenSize();

	//used if create_windows==true
	void SetViewportResizeCallback(VieportResizeCallback callback);
	void MainLoop();
	void SetSymulatePhysics(bool enable);

	//used if create_windows==false
	void Render();
	void SetViewport(TVec2i use_size);
	/*void OnMouseMove(TMouseEventArgs e);
	void OnMouseDown(TMouseEventArgs e);
	void OnMouseUp(TMouseEventArgs e);
	void OnMouseWheel(float delta);*/
};