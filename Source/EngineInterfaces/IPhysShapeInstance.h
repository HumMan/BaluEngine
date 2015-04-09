
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

namespace EngineInterface
{
	class IBaluInstance;
	class IBaluSpriteInstance;
}

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluPhysShapeInstance
	{
	public:
		virtual IBaluInstance* GetParent()=0;
		virtual IBaluSpriteInstance* GetSpriteInstance() = 0;
	};
#endif

}