#pragma once

#include "IResources.h"

#include "IWorldInstance.h"

#include "../Render.h"

namespace EngineInterface
{
	class IDirector;
}


namespace EngineInterface
{
	class IDirector
	{
	public:
		virtual void Step(float step)=0;
		virtual void SetWorldInstance(IBaluWorldInstance* world_instance)=0;
		virtual EngineInterface::IBaluWorldInstance* GetWorldInstance()=0;
		//virtual void SetRenderWorldCallback(CallbackWithData<RenderWorldCallback> callback)=0;
		//virtual void SetViewportResizeCallback(CallbackWithData<ViewportResizeCallback> callback) = 0;
		virtual void SetSymulatePhysics(bool enable)=0;
		virtual int Initialize(bool create_window)=0;
		virtual void MainLoop()=0;
		virtual IResources* GetResources()=0;
		virtual std::string GetBasePath() = 0;
		virtual TVec2i GetScreenSize() = 0;
		virtual void SetScreenSize(TVec2i size) = 0;
		virtual void SetViewport(TVec2i use_size)=0;
		virtual void Render()=0;

		//special only for testing
		virtual void Initialize(void* handle)=0;
		virtual void BeginFrame()=0;
		virtual void EndFrame()=0;
		//
	};

#ifdef BALU_ENGINE_SCRIPT_CLASSES

	void IDirector_GetWorldInstance(std::vector<TStaticValue> &static_fields, std::vector<TStackValue> &formal_params, TStackValue& result, TStackValue& object)
	{
		result.get_as<IBaluWorldInstance*>() = object.get_as<IDirector*>()->GetWorldInstance();
	}

	void IDirector_register(TClassRegistryParams& params)
	{
		auto scl = RegisterExternClass(params,
			"class extern IDirector\n"
			"{\n"
			"func GetWorldInstance:IWorldInstance;\n"
			"}\n",
			sizeof(IDirector*));
		RegisterMethod(params, scl, "GetWorldInstance", IDirector_GetWorldInstance);
	}
	static bool IDirector_registered = TScriptClassesRegistry::Register("IDirector", IDirector_register);
#endif
}

BALUENGINEDLL_API EngineInterface::IDirector* CreateDirector();
BALUENGINEDLL_API void DestroyDirector(EngineInterface::IDirector* director);


