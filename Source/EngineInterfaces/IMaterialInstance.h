
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include "IMaterial.h"
#endif

class TBaluSceneInstance;

#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES

	class TSceneObjectInstance
	{
	public:
		virtual ~TSceneObjectInstance()
		{
		}
	};

	typedef TSceneObjectInstance*(*SceneObjectInstanceClone)(TSceneObject* source_def, TBaluSceneInstance* scene);
	class SceneObjectInstanceFactory
	{
	public:
		static bool Register(const char* name, SceneObjectInstanceClone clone);
		static TSceneObjectInstance* Create(const char* name, TSceneObject* param, TBaluSceneInstance* scene);
	};

	class IBaluMaterialInstance
	{
	public:
	};
#endif

}