#pragma once

#include <memory>

#include "Resources.h"

#include "EngineInterfaces\IDirector.h"
#include "EngineInterfaces\IComposer.h"

class TGameInternal;
class TBaluWorldInstance;

using namespace EngineInterface;

namespace EngineInterface
{
	class TRender;
}

class TDirector: public EngineInterface::IDirector
{
	std::unique_ptr < TGameInternal > p;

	
public:
	void Step(float step);
	//special only for testing
	void Initialize(void* handle);
	void BeginFrame();
	void EndFrame();
	//
	TDirector(std::string assets_dir);
	void SetWorldInstance(TBaluWorldInstance* world_instance);
	void SetWorldInstance(EngineInterface::IBaluWorldInstance* world_instance);
	EngineInterface::IBaluWorldInstance* GetWorldInstance();
	//void SetRenderWorldCallback(CallbackWithData<RenderWorldCallback> callback);
	
	int Initialize(bool create_window);
	TResources* GetResources();
	~TDirector();

	std::string GetAssetsDir();
	TVec2i GetScreenSize();
	void SetScreenSize(TVec2i size);

	//used if create_windows==true
	//void SetViewportResizeCallback(CallbackWithData<ViewportResizeCallback> callback);
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