#pragma once

#include <vector>
#include <memory>

class TSceneEditorScene : public TBoundaryBoxScene
{
public:
	TBaluSceneDef* balu_scene;

	void Initialize(TBaluSceneDef* balu_scene)
	{
		this->balu_scene = balu_scene;
	}
};