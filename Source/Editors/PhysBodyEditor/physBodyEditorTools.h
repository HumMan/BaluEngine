#pragma once

#include "../BoundaryEditor.h"

class TPhysBodyEditorScene;

class TPhysEditorTools : public TEditorTool
{
protected:
	TPhysBodyEditorScene* phys_body_editor_scene;
};



class TPhysBodyEditorToolsRegistry//: public TEditorToolsRegistry
{
	std::vector<TToolWithDescription> tools;
	TPhysBodyEditorScene* phys_body_editor_scene;
public:
	TPhysBodyEditorToolsRegistry(TPhysBodyEditorScene* phys_body_editor_scene);
	TPhysBodyEditorToolsRegistry(TPhysBodyEditorToolsRegistry&& o);
	const std::vector<TToolWithDescription>& GetTools();
	~TPhysBodyEditorToolsRegistry();
};
