#pragma once

#include "../BoundaryEditor.h"

class TSpriteEditorScene;

class TSpriteEditorRegistry
{
public:
	std::vector<TToolWithDescription> tools;
	TSpriteEditorScene* scene;
public:
	TSpriteEditorRegistry(TSpriteEditorScene* scene);
	TSpriteEditorRegistry(TSpriteEditorRegistry&& o);
	const std::vector<TToolWithDescription>& GetTools();
	~TSpriteEditorRegistry();
};
