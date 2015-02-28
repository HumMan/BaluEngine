#pragma once

#include "IClass.h"

#include "../../BaluLib/Source/BVolumes/AABB.h"

namespace EngineInterface
{
	class IBaluSceneClassInstance
	{
	public:
		virtual ~IBaluSceneClassInstance(){}
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual TVec2 GetScale() = 0;
	};

	class IBaluScene
	{
	public:

		virtual TVec2 FromViewportToScene(IViewport* viewport, TVec2 viewport_coord)=0;
		virtual TVec2 FromSceneToViewport(IViewport* viewport, TVec2 scene_coord)=0;

		virtual IViewport* CreateViewport(std::string name)=0;

		virtual std::string GetName() = 0;
		virtual void SetName(std::string name) = 0;

		virtual int GetInstancesCount() = 0;
		virtual IBaluSceneClassInstance* GetInstance(int index) = 0;

		virtual IBaluSceneClassInstance* CreateInstance(IBaluClass* balu_class) = 0;
		virtual void DestroyInstance(IBaluSceneClassInstance* instance) = 0;
	};
}