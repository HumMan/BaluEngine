
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#if !defined(BALU_ENGINE_SCRIPT_CLASSES) && !defined(BALU_ENGINE_DLL_INTERFACES)

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "../Class/IClassInstance.h"
#include "../Sprite/ISpriteInstance.h"
#endif

#endif

namespace EngineInterface
{
	class IBaluInstance;
	class TBaluInstance;
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

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBaluPhysShapeInstance : public IBaluPhysShapeInstance
	{
	protected:
		TBaluPhysShape* source;
		//TBaluTransform global;
		b2Fixture* fixture;
		b2Body* body;
		TBaluInstance* parent;
		TBaluClassSpriteInstance* sprite_instance;
	public:
		TBaluPhysShapeInstance(TBaluPhysShape* source, TBaluInstance* parent_instance, TBaluClassSpriteInstance* sprite_instance);
		void BuildFixture(b2Body* body, TBaluTransformWithScale class_transform);

		//TODO попытаться сделать TBaluInstance
		IBaluInstance* GetParent();
		IBaluClassSpriteInstance* GetSpriteInstance();
	};
#endif

#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluPhysShapeInstance, "IPhysShapeInstance");
	MUnpackRA0(WrapPointer<IBaluInstance>, TYPE, GetParent);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif

}