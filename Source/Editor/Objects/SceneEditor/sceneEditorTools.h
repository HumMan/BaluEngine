#pragma once

#include <Editor/abstractEditor.h>

using namespace EngineInterface;

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
