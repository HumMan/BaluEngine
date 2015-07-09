
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif


#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IClass.h"
#endif

#include "../../BaluLib/Source/BVolumes/AABB.h"

#include "../exportMacro.h"
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluSceneClassInstance
	{
	public:
		virtual ~IBaluSceneClassInstance(){}
		virtual void SetTransform(TBaluTransform transform) = 0;
		virtual void SetScale(TVec2 scale) = 0;
		virtual TBaluTransform GetTransform() = 0;
		virtual TVec2 GetScale() = 0;
		virtual TSceneObject* GetClass() = 0;
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluScene
	{
	public:
		BALUENGINEDLL_API static TVec2 FromViewportToScene(EngineInterface::IViewport* viewport, TVec2 viewport_coord);
		BALUENGINEDLL_API static TVec2 FromSceneToViewport(EngineInterface::IViewport* viewport, TVec2 scene_coord);

		static std::string GetDefaultName()
		{
			return "scene";
		}

		virtual IViewport* CreateViewport(std::string name)=0;
		virtual IViewport* FindViewport(std::string name)=0;

		virtual std::string GetName() = 0;
		virtual void SetName(std::string name) = 0;

		virtual int GetInstancesCount() = 0;
		virtual IBaluSceneClassInstance* GetInstance(int index) = 0;

		virtual IBaluSceneClassInstance* CreateInstance(IBaluClass* balu_class) = 0;
		virtual void DestroyInstance(IBaluSceneClassInstance* instance) = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES	
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluScene, "IScene");
	MUnpackRA1(WrapPointer<IViewport>, TYPE, FindViewport, TString);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

}