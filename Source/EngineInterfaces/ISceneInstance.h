#pragma once

#include "../RenderCommand.h"

#include "IScene.h"
#include "IClassInstance.h"

namespace EngineInterface
{
	class IBaluWorldInstance;

	class IBaluSceneInstance
	{
	public:

		virtual bool PointCollide(TVec2 scene_space_point, EngineInterface::IBaluInstance* &result)=0;
		virtual IBaluScene* GetSource()=0;
		virtual IBaluWorldInstance* GetWorld()=0;
		virtual IViewport* GetViewport(std::string name)=0;
		virtual void QueryAABB(TAABB2 frustum, std::vector<TRenderCommand>& results, std::vector<TCustomDrawCommand>& custom_draw) = 0;
		virtual IBaluInstance* CreateInstance(IBaluClass* use_class, TBaluTransform transform, TVec2 scale) = 0;
	};
}