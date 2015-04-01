#pragma once

#include "IClass.h"

#include "../../BaluLib/Source/BVolumes/AABB.h"

#include "../exportMacro.h"

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
		virtual IBaluClass* GetClass() = 0;
	};

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

#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void IBaluScene_FindViewport(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		result.get_as<IViewport*>() = object.get_as<IBaluScene*>()->FindViewport(*formal_params[0].get_as<TString>().v);
	}

	void IBaluScene_register(TClassRegistryParams& params)
	{
		auto scl = RegisterExternClass(params,
			"class extern IScene\n"
			"{\n"
			"func FindViewport(string name):IViewport;\n"
			"}\n",
			sizeof(IBaluScene*));
		RegisterMethod(params, scl, "FindViewport", IBaluScene_FindViewport);
	}
	static bool IBaluScene_registered = TScriptClassesRegistry::Register("IScene", IBaluScene_register);
#endif
}