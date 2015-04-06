
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "../RenderCommand.h"
#include "IScene.h"
#include "IClassInstance.h"
#endif

namespace EngineInterface
{
	class IBaluWorldInstance;
}
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluSceneInstance
	{
	public:

		virtual bool PointCollide(TVec2 scene_space_point, EngineInterface::IBaluInstance* &result)=0;
		virtual IBaluScene* GetSource()=0;
		virtual IBaluWorldInstance* GetWorld()=0;
		virtual IViewport* GetViewport(std::string name)=0;
		virtual void QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<TCustomDrawCommand>& custom_draw) = 0;
		virtual IBaluInstance* CreateInstance(IBaluClass* use_class, TBaluTransform transform, TVec2 scale) = 0;
		virtual void DestroyInstance(EngineInterface::IBaluInstance*) = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluSceneInstance, "ISceneInstance");
	MUnpackRA0(WrapPointer<IBaluScene>, TYPE, GetSource);
	BALU_ENGINE_SCRIPT_END_CLASS(WrapInterface<IBaluSceneInstance>);
#endif

}