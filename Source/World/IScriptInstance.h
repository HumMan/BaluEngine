
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IWorld.h"
#include "ICommon.h"
#include "ICallbacks.h"
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
	class TBaluScriptInstance : public IBaluScriptInstance
	{
	private:
		std::unique_ptr<TBaluScriptInstancePrivate> p;
	public:

		bool HasErrors();
		std::vector<std::string> GetErrors();
		TBaluScriptInstance(std::string assets_dir, TScriptActiveType script_type_to_run);
		~TBaluScriptInstance();
		TScriptInstance CompileMethod(TScript* script, const char* code);
		void CallViewportResize(TScriptInstance &viewport_resize_callback, IDirector* director, TVec2i old_size, TVec2i new_size);
		void CallWorldStart(TScriptInstance &script_instance, IBaluWorldInstance* world_instance, IComposer* composer);
		//KeyUp KeyDown BeforePhysicsStep
		void CallInstanceEvent(TScriptInstance& script_instance, IBaluInstance* obj);
		void CallMouseEvent(TScriptInstance &callback, TMouseEventArgs* e);
		void CallCollide(TScriptInstance &callback, IBaluPhysShapeInstance* obj_a, IBaluInstance* obj_b);

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


