#pragma once

#include "World.h"
#include "SceneInstance.h"

class TBaluWorldInstance
{
private:
	TBaluWorld* source;
	std::vector<std::unique_ptr<TBaluSceneInstance>> instances;
public:
	TBaluWorldInstance(TBaluWorld* source);
	TBaluSceneInstance* RunScene(TBaluScene* scene_source);
	void StopScene(TBaluSceneInstance*);

	void OnPrePhysStep();
	void PhysStep(float step);

	void OnProcessCollisions();
	void OnStep(float step);

	void OnKeyDown(TKey key);

	void UpdateTransform();

	void DebugDraw();
};