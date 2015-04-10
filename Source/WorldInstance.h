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
	std::vector<std::unique_ptr<TBaluSceneInstance>> instances;
	TResources* resources;
	TBaluScriptInstance script_engine;
	TComposer composer;
public:
	TBaluWorld* GetSource();

	TBaluWorldInstance(TBaluWorld* source, TResources* resources);

	TBaluSceneInstance* RunScene(TBaluScene* scene_source);
	void StopScene(TBaluSceneInstance*);

	EngineInterface::IBaluSceneInstance* RunScene(EngineInterface::IBaluScene* scene_source);
	int GetSceneInstancesCount()
	{
		return instances.size();
	}
	TBaluSceneInstance* GetSceneInstance(int index)
	{
		return instances[index].get();
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
	void DebugDraw();

	void CompileScripts();

	TComposer* GetComposer()
	{
		return &composer;
	}
};