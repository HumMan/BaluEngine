#pragma once

#include "../BoundaryEditor.h"

class TSceneEditorScene;

class TSceneEditorToolsRegistry
{
public:
	std::vector<TToolWithDescription> tools;
	TSceneEditorScene* scene;
public:
	TSceneEditorToolsRegistry(TSceneEditorScene* scene);
	TSceneEditorToolsRegistry(TSceneEditorToolsRegistry&& o);
	const std::vector<TToolWithDescription>& GetTools();
	~TSceneEditorToolsRegistry();
};
