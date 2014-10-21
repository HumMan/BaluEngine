#pragma once

#include "../BoundaryEditor.h"

class TSpriteEditorRegistry
{
	std::vector<TToolWithDescription> tools;
	TSpriteEditorScene* scene;
public:
	TSpriteEditorRegistry(TSpriteEditorScene* scene)
	{
		this->scene = scene;
		tools.emplace_back(new TBoundaryBoxesModifyTool(scene), "Modify");
	}
	TSpriteEditorRegistry(TSpriteEditorRegistry&& o);
	const std::vector<TToolWithDescription>& GetTools()
	{
		return tools;
	}
	~TSpriteEditorRegistry();
};
