#include "materialEditorTools.h"

#include "materialEditor.h"

#include "materialEditorAdornments.h"

TMaterialEditorToolsRegistry::TMaterialEditorToolsRegistry(TMaterialEditorScene* material_editor_scene)
{
	this->scene = material_editor_scene;
}

TMaterialEditorToolsRegistry::TMaterialEditorToolsRegistry(TMaterialEditorToolsRegistry&& o)
{
	tools = std::move(o.tools);
	scene = std::move(o.scene);
}

const std::vector<TToolWithDescription>& TMaterialEditorToolsRegistry::GetTools()
{
	return tools;
}

TMaterialEditorToolsRegistry::~TMaterialEditorToolsRegistry()
{
}