#pragma once

#include <memory>

#include <Common\RenderCommand.h>

namespace EngineInterface
{
	class IDirector;
	class IBaluSceneInstance;
	class IViewport;
	class TComposerPrivate;
	class TRender;

	class IComposerStage
	{
	public:
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TComposerStage : public IComposerStage
	{
		friend class TComposer;
		TComposer* composer;
		IBaluSceneInstance* scene_instance;
		IViewport* viewport;
		TView view;
		//TODO effects, etc.
	public:
		void MoveFront();
		void MoveBack();
		void MoveForward();
		void MoveBackward();
	};
#endif

	class IComposer
	{
	public:
		virtual IComposerStage* AddToRender(IBaluSceneInstance* scene_instance, IViewport* viewport) = 0;
		virtual void RemoveFromRender(IComposerStage* stage)=0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	

	class TComposer: public IComposer
	{
		std::unique_ptr<TComposerPrivate> p;
	public:
		TComposer();
		//TComposer(TRender* render);
		TComposerStage* AddToRender(IBaluSceneInstance* scene_instance, IViewport* viewport);
		void RemoveFromRender(IComposerStage* stage);

		void Render(TRender* render);
		~TComposer();
};
#endif
}




