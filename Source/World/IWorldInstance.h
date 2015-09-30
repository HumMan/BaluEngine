#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#include <World\Layers.h>

#ifndef BALU_ENGINE_SCRIPT_CLASSES

#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#include <WorldObjects\Scene\IScene.h>
#include <WorldObjects\Scene\ISceneInstance.h>
#include "IWorld.h"
#include "IComposer.h"
#include "IDirector.h"
#include "IScriptInstance.h"
#endif

namespace EngineInterface
{
	class IResources;
	class IComposer;
	class IBaluWorld;
	class TDirector;
}
#endif

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
	class TMouseEventListener
	{
	public:
		virtual void OnMouseMove(TMouseEventArgs e){}
		virtual void OnMouseDown(TMouseEventArgs e){}
		virtual void OnMouseUp(TMouseEventArgs e){}
	};

	class IBaluWorldInstance
	{
	public:

		virtual void AddMouseEventListener(TMouseEventListener*)=0;
		virtual void RemoveMouseEventListener(TMouseEventListener*) = 0;

		virtual IBaluWorld* GetSource()=0;
		virtual IBaluSceneInstance* RunScene(IBaluScene* scene_source)=0;
		virtual IBaluSceneInstance* RunScene() = 0;
		virtual IBaluSceneInstance* RunScene(TLayersManager* scene_layers) = 0;
		virtual void StopScene(IBaluSceneInstance*)=0;

		virtual int GetSceneInstancesCount()=0;
		virtual IBaluSceneInstance* GetSceneInstance(int index)=0;

		virtual void MouseDown(TMouseEventArgs e) = 0;
		virtual void MouseMove(TMouseEventArgs e) = 0;
		virtual void MouseUp(TMouseEventArgs e) = 0;
		virtual void MouseVerticalWheel(int amount)=0;
		virtual IComposer* GetComposer() = 0;
	};

#ifndef BALU_ENGINE_DLL_INTERFACES
	class TBaluWorldInstance : public IBaluWorldInstance
	{
	private:
		TBaluWorld* source;
		std::vector<std::unique_ptr<TBaluSceneInstance>> scene_instances;
		std::vector<std::unique_ptr<TBaluClassInstance>> class_instances;
		TResources* resources;
		TBaluScriptInstance script_engine;
		TComposer composer;

		std::vector<TScriptInstance>
			mouse_down_callbacks,
			mouse_up_callbacks,
			mouse_move_callbacks;
		std::vector<TScriptInstance> on_start_world_callback;
		std::vector<TScriptInstance> viewport_resize_callback;
		std::vector<TMouseEventListener*> OnMouseEventListeners;
	public:

		void AddMouseEventListener(TMouseEventListener*);
		void RemoveMouseEventListener(TMouseEventListener*);

		TBaluClassInstance* GetClassInstance(TBaluClass* source)
		{
			for (auto& v : class_instances)
				if (v->GetClass() == source)
					return v.get();
			return nullptr;
		}
		TBaluScriptInstance* GetScriptEngine()
		{
			return &script_engine;
		}
		TBaluWorld* GetSource();

		TBaluWorldInstance(TBaluWorld* source, TResources* resources);
		~TBaluWorldInstance()
		{
		}

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

		void OnPrePhysStep();
		void PhysStep(float step);

		void OnProcessCollisions();
		void OnStep(float step);

		void KeyDown(TKey key);
		void KeyUp(TKey key);

		void MouseDown(TMouseEventArgs e);
		void MouseMove(TMouseEventArgs e);
		void MouseUp(TMouseEventArgs e);
		void MouseVerticalWheel(int amount);

		void ViewportResize(TDirector* director, TVec2i old_size, TVec2i new_size);
		//void Render(TDirector* director, TRender* render);

		void UpdateTransform();

		bool CompileScripts();
		static bool CheckScriptErrors(TBaluWorld* source, TBaluScriptInstance* script_engine, std::vector<std::string>& errors_list);

		TComposer* GetComposer()
		{
			return &composer;
		}
};
#endif
#endif

#ifdef BALU_ENGINE_SCRIPT_CLASSES
	BALU_ENGINE_SCRIPT_BEGIN_CLASS(WrapInterface, IBaluWorldInstance, "IWorldInstance");
	MUnpackRA1(WrapPointer<IBaluSceneInstance>, WrapInterface<IBaluWorldInstance>, GetSceneInstance, WrapValue<int>);
	MUnpackRA1(WrapPointer<IBaluSceneInstance>, WrapInterface<IBaluWorldInstance>, RunScene, WrapInterface<IBaluScene>);
	MUnpackRA0(WrapPointer<IBaluWorld>, WrapInterface<IBaluWorldInstance>, GetSource);
	BALU_ENGINE_SCRIPT_END_CLASS;
#endif



#ifndef BALU_ENGINE_SCRIPT_CLASSES
	BALUENGINEDLL_API IBaluWorldInstance* CreateWorldInstance(IBaluWorld* source, IResources* resources);
	BALUENGINEDLL_API void DestroyWorldInstance(IBaluWorldInstance* world);
#endif

}


