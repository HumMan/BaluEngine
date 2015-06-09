
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IWorld.h"
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
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	BALUENGINEDLL_API bool CompileScripts(IBaluWorld* source, IBaluScriptInstance* script_engine, std::vector<std::string>& errors_list);
	BALUENGINEDLL_API IBaluScriptInstance* CreateScriptInstance(std::string assets_dir);
	BALUENGINEDLL_API void DestroyScriptInstance(IBaluScriptInstance* instance);
#endif

}


