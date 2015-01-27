#pragma once

#include <vector>
#include <memory>

#include "../../EngineInterfaces/IScene.h"

using namespace EngineInterface;

class TSceneEditorScene : public TBoundaryBoxScene
{
public:
	IBaluScene* balu_scene;

	void Initialize(IBaluScene* balu_scene)
	{
		this->balu_scene = balu_scene;
	}
};