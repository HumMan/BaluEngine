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

	void IBaluWorldInstance_GetSceneInstance(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		result.get_as<IBaluSceneInstance*>() = object.get_as<IBaluWorldInstance*>()->GetSceneInstance(formal_params[0].get_as<int>());
	}

	void IWorldInstance_register(TClassRegistryParams& params)
	{
		auto scl = RegisterExternClass(params,
			"class extern IWorldInstance\n"
			"{\n"
			"func GetSceneInstance(int index):ISceneInstance;\n"
			"}\n",
			sizeof(IBaluWorldInstance*));
		RegisterMethod(params, scl, "GetSceneInstance", IBaluWorldInstance_GetSceneInstance);
	}
	static bool IWorldInstance_registered = TScriptClassesRegistry::Register("IWorldInstance", IWorldInstance_register);
#endif
}

BALUENGINEDLL_API EngineInterface::IBaluWorldInstance* CreateWorldInstance(EngineInterface::IBaluWorld* source, EngineInterface::IResources* resources);
BALUENGINEDLL_API void DestroyWorldInstance(EngineInterface::IBaluWorldInstance* world);


