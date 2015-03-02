#pragma once

#include "World.h"
#include "SceneInstance.h"

class TBaluWorldInstance : public EngineInterface::IBaluWorldInstance
{
private:
	TBaluWorld* source;
	std::vector<std::unique_ptr<TBaluSceneInstance>> instances;
	TResources* resources;
public:
	TBaluWorld* GetSource();

	TBaluWorldInstance(TBaluWorld* source, TResources* resources);

	TBaluSceneInstance* RunScene(TBaluScene* scene_source);
	void StopScene(TBaluSceneInstance*);

	EngineInterface::IBaluSceneInstance* RunScene(EngineInterface::IBaluScene* scene_source);
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

	void UpdateTransform();
	void DebugDraw();
};