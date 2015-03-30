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
		virtual void DestroyInstance(EngineInterface::IBaluInstance*) = 0;
	};

#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void IBaluSceneInstance_GetSource(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		*result.get_as<IBaluScene*>() = (*object.get_as<IBaluSceneInstance*>())->GetSource();
	}

	void IBaluSceneInstance_register(TClassRegistryParams& params)
	{
		auto scl = RegisterExternClass(params,
			"class extern ISceneInstance\n"
			"{\n"
			"func GetSource():IScene;\n"
			"}\n",
			sizeof(IBaluSceneInstance*));
		RegisterMethod(params, scl, "GetSource", IBaluSceneInstance_GetSource);
	}
	static bool IBaluSceneInstance_registered = TScriptClassesRegistry::Register("ISceneInstance", IBaluSceneInstance_register);
#endif
}