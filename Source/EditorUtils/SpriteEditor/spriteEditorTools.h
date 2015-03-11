#pragma once

#include "../BoundaryEditor.h"

#include "../../EditorInterfaces.h"

using namespace EngineInterface;

class TSpriteEditorScene;

class TSpriteEditorToolsRegistry
{
public:
	std::vector<TToolWithDescription> tools;
	TSpriteEditorScene* scene;
public:
	TSpriteEditorToolsRegistry(TSpriteEditorScene* scene);
	TSpriteEditorToolsRegistry(TSpriteEditorToolsRegistry&& o);
	const std::vector<TToolWithDescription>& GetTools();
	~TSpriteEditorToolsRegistry();
};
