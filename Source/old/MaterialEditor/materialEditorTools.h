#pragma once

#include "../BoundaryEditor.h"

class TMaterialEditorScene;

class TMaterialEditorTools : public TEditorTool
{
protected:
	TMaterialEditorScene* material_editor_scene;
};



class TMaterialEditorToolsRegistry//: public TEditorToolsRegistry
{
	std::vector<TToolWithDescription> tools;
	TMaterialEditorScene* material_editor_scene;
public:
	TMaterialEditorToolsRegistry(TMaterialEditorScene* material_editor_scene);
	TMaterialEditorToolsRegistry(TMaterialEditorToolsRegistry&& o);
	const std::vector<TToolWithDescription>& GetTools();
	~TMaterialEditorToolsRegistry();
};
