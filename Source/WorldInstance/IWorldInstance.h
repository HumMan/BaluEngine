#pragma once

#include "Objects/Scene/ISceneInstance.h"
#include <WorldDef/IWorld.h>
#include "IComposer.h"

namespace EngineInterface
{
	class IResources;
	class IComposer;
	class IBaluWorld;
	class TDirector;
	class TEventsEditorInstance;
	class IEventsEditorInstance;
}

namespace EngineInterface
{

	class TBaluClassCompiledScripts;
	class TBaluClass;

	class IBaluWorldInstance
	{
	public:
		virtual TResources* GetResources() = 0;
		

		virtual IBaluWorld* GetSource()=0;
		virtual IBaluSceneInstance* RunScene(IBaluScene* scene_source)=0;
		virtual IBaluSceneInstance* RunScene() = 0;

		//создание пустой сцены используется в редакторе
		virtual IBaluSceneInstance* RunScene(TLayersManager* scene_layers) = 0;
		virtual void StopScene(IBaluSceneInstance*)=0;

		virtual int GetSceneInstancesCount()=0;
		virtual IBaluSceneInstance* GetSceneInstance(int index)=0;

		virtual IEventsEditorInstance* GetEventsEditor()=0;
		
		virtual IComposer* GetComposer() = 0;
	};

#ifdef BALUENGINEDLL_EXPORTS
	class TBaluWorldInstance : public IBaluWorldInstance
	{
	private:
		TBaluWorld* source;
		std::vector<std::unique_ptr<TBaluSceneInstance>> scene_instances;
		
		TResources* resources;
		
		TComposer composer;

		std::unique_ptr<TEventsEditorInstance> events_editor;

	public:
		~TBaluWorldInstance();
		IEventsEditorInstance* GetEventsEditor();

		TResources* GetResources()
		{
			return resources;
		}

		TBaluWorld* GetSource();

		TBaluWorldInstance(TBaluWorld* source, TResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message);

		TBaluSceneInstance* RunScene(TBaluScene* scene_source);
		void StopScene(TBaluSceneInstance*);

		IBaluSceneInstance* RunScene(IBaluScene* scene_source);
		TBaluSceneInstance* RunScene();
		TBaluSceneInstance* RunScene(TLayersManager* scene_layers);

		int GetSceneInstancesCount()
		{
			return scene_instances.size();
		}
		TBaluSceneInstance* GetSceneInstance(int index)
		{
			return scene_instances[index].get();
		}
		void StopScene(IBaluSceneInstance*);

		
		void PhysStep(float step);

		
		void OnStep(float step);

		//void Render(TDirector* director, TRender* render);

		void UpdateTransform();

		
		TComposer* GetComposer()
		{
			return &composer;
		}
};
#endif

	BALUENGINEDLL_API IBaluWorldInstance* CreateWorldInstance(IBaluWorld* source, IResources* resources, std::string assets_dir, bool call_scripts, bool& compile_success, std::string& error_message);
	BALUENGINEDLL_API void DestroyWorldInstance(IBaluWorldInstance* world);


}


