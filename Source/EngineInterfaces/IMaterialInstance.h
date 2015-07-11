
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
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

	typedef TSceneObjectInstance*(*SceneObjectInstanceClone)();
	class SceneObjectInstanceFactory
	{
	public:
		static bool Register(const char* name, SceneObjectInstanceClone clone);
		static TSceneObjectInstance* Create(const char* name);
	};

	class IBaluMaterialInstance
	{
	public:
	};
#endif

}