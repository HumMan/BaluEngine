#pragma once

#include "EngineInterfaces\ISceneInstance.h"
#include "EngineInterfaces\IComposer.h"

#include <memory>

namespace EngineInterface
{
	class TRender;
}

class TComposer;

class TComposerStage : public EngineInterface::IComposerStage
{
	friend class TComposer;
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

class TComposerPrivate;

class TComposer: public EngineInterface::IComposer
{
	std::unique_ptr<TComposerPrivate> p;
public:
	TComposer();
	//TComposer(EngineInterface::TRender* render);
	TComposerStage* AddToRender(EngineInterface::IBaluSceneInstance* scene_instance, EngineInterface::IViewport* viewport);
	void RemoveFromRender(EngineInterface::IComposerStage* stage);

	void Render(EngineInterface::TRender* render);
	~TComposer();
};