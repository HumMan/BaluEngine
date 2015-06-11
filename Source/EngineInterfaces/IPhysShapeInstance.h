
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

namespace EngineInterface
{
	class IBaluInstance;
	class IBaluClassSpriteInstance;
}

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class IBaluPhysShapeInstance
	{
	public:
		virtual IBaluInstance* GetParent() = 0;
		virtual IBaluClassSpriteInstance* GetSpriteInstance() = 0;
	};
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluPhysShapeInstance, "IPhysShapeInstance");
	MUnpackRA0(WrapPointer<IBaluInstance>, TYPE, GetParent);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif
}