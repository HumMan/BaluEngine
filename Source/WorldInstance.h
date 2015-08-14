#pragma once

#include "World.h"
#include "SceneInstance.h"
#include "Composer.h"

#include "EngineInterfaces\IWorldInstance.h"

#include "ScriptInstance.h"

class TDirector;

class TBaluWorldInstance : public EngineInterface::IBaluWorldInstance
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

	EngineInterface::IBaluSceneInstance* RunScene(EngineInterface::IBaluScene* scene_source);
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
	void StopScene(EngineInterface::IBaluSceneInstance*);

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