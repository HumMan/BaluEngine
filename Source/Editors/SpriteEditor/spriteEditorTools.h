#pragma once

#include "../BoundaryEditor.h"

class TSpriteEditorScene;

class TSpriteEditorTools : public TEditorTool
{
protected:
	TSpriteEditorScene* sprite_polygon_editor_scene;
};

class TSpriteEditorRegistry
{
	std::vector<TToolWithDescription> tools;
	TSpriteEditorScene* scene;
public:
	TSpriteEditorRegistry(TSpriteEditorScene* scene)
	{

	}
	TSpriteEditorRegistry(TSpriteEditorRegistry&& o);
	const std::vector<TToolWithDescription>& GetTools();
	~TSpriteEditorRegistry();
};
