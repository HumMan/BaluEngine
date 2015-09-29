
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IWorld.h"
#include "ICommon.h"
#endif

#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluScriptInstance
	{
	public:
		virtual bool HasErrors() = 0;
	};

	class TBaluScriptInstancePrivate;
	class TBaluScriptInstance : public EngineInterface::IBaluScriptInstance
	{
	private:
		std::unique_ptr<TBaluScriptInstancePrivate> p;
	public:

		bool HasErrors();
		std::vector<std::string> GetErrors();
		TBaluScriptInstance(std::string assets_dir, EngineInterface::TScriptActiveType script_type_to_run);
		~TBaluScriptInstance();
		EngineInterface::TScriptInstance CompileMethod(EngineInterface::TScript* script, const char* code);
		void CallViewportResize(EngineInterface::TScriptInstance &viewport_resize_callback, EngineInterface::IDirector* director, TVec2i old_size, TVec2i new_size);
		void CallWorldStart(EngineInterface::TScriptInstance &script_instance, EngineInterface::IBaluWorldInstance* world_instance, EngineInterface::IComposer* composer);
		//KeyUp KeyDown BeforePhysicsStep
		void CallInstanceEvent(EngineInterface::TScriptInstance& script_instance, EngineInterface::IBaluInstance* obj);
		void CallMouseEvent(EngineInterface::TScriptInstance &callback, EngineInterface::TMouseEventArgs* e);
		void CallCollide(EngineInterface::TScriptInstance &callback, EngineInterface::IBaluPhysShapeInstance* obj_a, EngineInterface::IBaluInstance* obj_b);

		//std::string GetEventSignature(EngineInterface::TEventType event_type);

		std::string AddName(std::string format, std::string name)
		{
			size_t size = format.size() + name.size();
			std::unique_ptr<char> buf(new char[size]);
			sprintf_s(buf.get(), size*sizeof(char), format.c_str());
			return buf.get();
		}
	};
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	BALUENGINEDLL_API bool CompileScripts(IBaluWorld* source, IBaluScriptInstance* script_instance, std::vector<std::string>& errors_list);
	BALUENGINEDLL_API IBaluScriptInstance* CreateScriptInstance(std::string assets_dir, TScriptActiveType script_type_to_run);
	BALUENGINEDLL_API void DestroyScriptInstance(IBaluScriptInstance* instance);
#endif

}


