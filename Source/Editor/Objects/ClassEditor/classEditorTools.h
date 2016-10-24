#pragma once

#include <Editor/abstractEditor.h>

using namespace EngineInterface;

class TClassEditorScene;

class TClassEditorToolsRegistry
{
public:
	std::vector<TToolWithDescription> tools;
	TClassEditorScene* scene;
public:
	TClassEditorToolsRegistry(TClassEditorScene* scene);
	TClassEditorToolsRegistry(TClassEditorToolsRegistry&& o);
	const std::vector<TToolWithDescription>& GetTools();
	~TClassEditorToolsRegistry();
};
