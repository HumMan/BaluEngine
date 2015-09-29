
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
#include <memory>

namespace EngineInterface
{
	class IDirector;
	class IBaluSceneInstance;
	class IViewport;
}
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IComposerStage
	{
	public:
	};


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

	class TComposerPrivate;

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

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IComposer, "IComposer");
	MUnpackRA2(WrapInterface<IComposerStage>, WrapInterface<IComposer>, AddToRender, WrapInterface<IBaluSceneInstance>, WrapInterface<IViewport>);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}




