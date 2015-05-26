#pragma once

#include "../BoundaryEditor.h"

#include "../../EditorInterfaces.h"

class TMaterialEditorScene;

class TMaterialEditorToolsRegistry
{
	std::vector<TToolWithDescription> tools;
	TMaterialEditorScene* scene;
public:
	TMaterialEditorToolsRegistry(TMaterialEditorScene* scene);
	TMaterialEditorToolsRegistry(TMaterialEditorToolsRegistry&& o);
	const std::vector<TToolWithDescription>& GetTools();
	~TMaterialEditorToolsRegistry();
};
