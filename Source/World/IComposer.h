
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#include <memory>

#if !defined(BALU_ENGINE_SCRIPT_CLASSES)  && !defined(BALU_ENGINE_DISABLE_PRAGMA_ONCE)
#include "RenderCommand.h"
#endif

namespace EngineInterface
{
	class IDirector;
	class IBaluSceneInstance;
	class IViewport;
	class TComposerPrivate;
	class TRender;

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IComposerStage
	{
	public:
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
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
#endif


#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IComposerStage, "IComposerStage");
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IComposer
	{
	public:
		virtual IComposerStage* AddToRender(IBaluSceneInstance* scene_instance, IViewport* viewport) = 0;
		virtual void RemoveFromRender(IComposerStage* stage)=0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	

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
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IComposer, "IComposer");
	MUnpackRA2(WrapInterface<IComposerStage>, WrapInterface<IComposer>, AddToRender, WrapInterface<IBaluSceneInstance>, WrapInterface<IViewport>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}




