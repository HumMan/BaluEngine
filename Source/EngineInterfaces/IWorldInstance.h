#pragma once

#include "IScene.h"
#include "ISceneInstance.h"
#include "IWorld.h"

namespace EngineInterface
{
	class IBaluWorldInstance
	{
	public:
		virtual IBaluWorld* GetSource()=0;
		virtual IBaluSceneInstance* RunScene(IBaluScene* scene_source)=0;
		virtual void StopScene(IBaluSceneInstance*)=0;

		virtual int GetSceneInstancesCount()=0;
		virtual IBaluSceneInstance* GetSceneInstance(int index)=0;

		virtual void MouseDown(TMouseEventArgs e) = 0;
		virtual void MouseMove(TMouseEventArgs e) = 0;
		virtual void MouseUp(TMouseEventArgs e) = 0;
		virtual void MouseVerticalWheel(int amount)=0;

		virtual void CompileScripts() = 0;
	};

	class IResources;

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluWorldInstance, "IWorldInstance");
	//MUnpackRA1(WrapPointer<IBaluSceneInstance>, WrapInterface<IBaluWorldInstance>, GetSceneInstance, WrapValue<int>);
	BALU_ENGINE_SCRIPT_END_CLASS(WrapInterface<IBaluWorldInstance>);
#endif


	BALUENGINEDLL_API EngineInterface::IBaluWorldInstance* CreateWorldInstance(EngineInterface::IBaluWorld* source, EngineInterface::IResources* resources);
	BALUENGINEDLL_API void DestroyWorldInstance(EngineInterface::IBaluWorldInstance* world);

}


