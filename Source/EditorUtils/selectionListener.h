#pragma once

#include "..\Source\exportMacro.h"

#include "..\EditorInterfaces.h"

class ISelectionChangeListener
{
public:
	virtual void OnSelectionChange(EngineInterface::IProperties* new_selection) = 0;
};

BALUENGINEDLL_API class TSelectionChangeListeners
{
private:
	std::vector<ISelectionChangeListener*> selection_listeners;
public:
	void AddSelectionChangeListener(ISelectionChangeListener* listener);
	void RemoveSelectionChangeListener(ISelectionChangeListener* listener);

	void EmitOnSelectionChange(EngineInterface::IProperties* new_selection);
};