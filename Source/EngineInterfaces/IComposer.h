
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#endif

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
#endif


#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IComposerStage, "IComposerStage");
	BALU_ENGINE_SCRIPT_END_CLASS(WrapInterface<IComposerStage>);
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IComposer
	{
	public:
		virtual IComposerStage* AddToRender(EngineInterface::IBaluSceneInstance* scene_instance, EngineInterface::IViewport* viewport) = 0;
		virtual void RemoveFromRender(IComposerStage* stage)=0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IComposer, "IComposer");
	MUnpackRA2(WrapInterface<IComposerStage>, WrapInterface<IComposer>, AddToRender, WrapInterface<IBaluSceneInstance>, WrapInterface<IViewport>);
	BALU_ENGINE_SCRIPT_END_CLASS(WrapInterface<IComposer>);
#endif
}




