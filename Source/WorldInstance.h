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

	void MouseDown(TMouseEventArgs e, TVec2 world_cursor_location);
	void MouseMove(TMouseEventArgs e, TVec2 world_cursor_location);
	void MouseUp(TMouseEventArgs e, TVec2 world_cursor_location);

	void UpdateTransform();
	void DebugDraw();
};