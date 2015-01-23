#pragma once

#include "IClass.h"

#include "../../BaluLib/Source/BVolumes/AABB.h"

namespace EngineInterface
{
	class IViewport
	{
	public:
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetAspectRatio(float aspect) = 0;
		virtual void SetWidth(float width) = 0;
		virtual TAABB2 GetAABB() = 0;
	};

	class IBaluSceneClassInstance
	{
	public:
	};

	class IBaluScene
	{
	public:
		virtual IViewport* CreateViewport(std::string name);

		virtual std::string GetName();
		virtual void SetName(std::string name);

		virtual int GetInstancesCount();
		virtual IBaluSceneClassInstance* GetInstance(int index);

		virtual IBaluSceneClassInstance* CreateInstance(IBaluClass* balu_class);
		virtual void DestroyIntance(IBaluSceneClassInstance*);
	};
}