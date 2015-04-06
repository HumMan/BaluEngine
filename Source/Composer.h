#pragma once

#include "EngineInterfaces\ISceneInstance.h"

namespace EngineInterface
{
	class TRender;
}

class TComposer;

class TComposerStage
{
	TComposer* composer;

	EngineInterface::IBaluSceneInstance* scene_instance;
	EngineInterface::IViewport* viewport;
	EngineInterface::TView view;
	//TODO effects, etc.
public:
	void MoveFront();
	void MoveBack();
	void MoveForward();
	void MoveBackward();
};

class TComposer
{
public:
	TComposer(EngineInterface::TRender* render);
	TComposerStage* AddToRender(EngineInterface::IBaluSceneInstance* scene_instance);
	void RemoveFromRender(TComposerStage* stage);
};