#pragma once

#include <Common/ICommon.h>
#include "ICallbacks.h"

namespace EngineInterface
{
	class TBaluScriptInstancePrivate;
	class IComposer;
	class IBaluTransformedClassInstance;
	class IBaluTransformedSpriteInstance;
	class IDirector;

	class IBaluScriptInstance
	{
	public:
		virtual bool HasErrors() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluScriptInstance : public IBaluScriptInstance
	{
	private:
		std::unique_ptr<TBaluScriptInstancePrivate> p;
	public:

		bool HasErrors();
		std::vector<std::string> GetErrors();
		TBaluScriptInstance(std::string assets_dir);
		~TBaluScriptInstance();
		TScriptInstance CompileMethod(TScript* script, const char* code);
		void CallViewportResize(TScriptInstance &viewport_resize_callback, IDirector* director, TVec2i old_size, TVec2i new_size);
		void CallWorldStart(TScriptInstance &script_instance, IBaluWorldInstance* world_instance, IComposer* composer);
		//KeyUp KeyDown BeforePhysicsStep
		void CallInstanceEvent(TScriptInstance& script_instance, IBaluTransformedClassInstance* obj);
		void CallMouseEvent(TScriptInstance &callback, TMouseEventArgs* e);
		void CallCollide(TScriptInstance &callback, IBaluTransformedClassInstance* object, IBaluTransformedSpriteInstance* obj_a, IBaluTransformedClassInstance* obj_b);

		//std::string GetEventSignature(EngineInterface::TEventType event_type);

		std::string AddName(std::string format, std::string name)
		{
			size_t size = format.size() + name.size();
			std::unique_ptr<char> buf(new char[size]);
			sprintf(buf.get(), format.c_str());
			return buf.get();
		}
	};
#endif

	//BALUENGINEDLL_API bool CompileScripts(IBaluWorld* source, IBaluScriptInstance* script_instance, std::vector<std::string>& errors_list);
	//BALUENGINEDLL_API IBaluScriptInstance* CreateScriptInstance(std::string assets_dir);
	//BALUENGINEDLL_API void DestroyScriptInstance(IBaluScriptInstance* instance);

}


