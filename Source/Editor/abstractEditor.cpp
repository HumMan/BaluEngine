#include "abstractEditor.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;

using namespace BaluLib;

TAbstractEditor::TAbstractEditor(WorldInstance::IWorld* world_instance)
{
	editor_global_pos = TVec2(0, 0);
	this->world_instance = world_instance;
	active_tool = nullptr;
	editor_global_pos = TVec2(0, 0);
	//world_instance->AddMouseEventListener(this);
}

TAbstractEditor::~TAbstractEditor()
{
	//world_instance->RemoveMouseEventListener(this);
}

void TAbstractEditor::OnMouseMove(WorldDef::TMouseEventArgs e)
{
	auto tool = GetActiveTool();
	if (tool != nullptr)
		tool->OnMouseMove(e);
}

void TAbstractEditor::OnMouseDown(WorldDef::TMouseEventArgs e)
{
	auto tool = GetActiveTool();
	if (tool != nullptr)
		tool->OnMouseDown(e);
}

void TAbstractEditor::OnMouseUp(WorldDef::TMouseEventArgs e)
{
	auto tool = GetActiveTool();
	if (tool != nullptr)
		tool->OnMouseUp(e);
}

void TAbstractEditor::SetActiveTool(IEditorTool* tool)
{
	if (tool == active_tool)
		return;
	if (active_tool != nullptr)
		active_tool->Deactivate();
	active_tool = tool;
	if (tool != nullptr)
		tool->Activate();
}