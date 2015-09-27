#pragma once

#include "../../EditorInterfaces.h"

class TMaterialEditorScene;

class TMaterialEditorToolsRegistry
{
	std::vector<EngineInterface::TToolWithDescription> tools;
	TMaterialEditorScene* scene;
public:
	TMaterialEditorToolsRegistry(TMaterialEditorScene* scene);
	TMaterialEditorToolsRegistry(TMaterialEditorToolsRegistry&& o);
	const std::vector<EngineInterface::TToolWithDescription>& GetTools();
	~TMaterialEditorToolsRegistry();
};
