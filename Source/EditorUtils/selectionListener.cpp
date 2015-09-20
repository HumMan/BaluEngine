#include "selectionListener.h"

void TSelectionChangeListeners::EmitOnSelectionChange(EngineInterface::IProperties* new_selection)
{
	for (auto& v : this->selection_listeners)
		v->OnSelectionChange(new_selection);
}

void TSelectionChangeListeners::AddSelectionChangeListener(ISelectionChangeListener* listener)
{
	assert(std::find(this->selection_listeners.begin(), this->selection_listeners.end(), listener) == this->selection_listeners.end());
	this->selection_listeners.push_back(listener);
}

void TSelectionChangeListeners::RemoveSelectionChangeListener(ISelectionChangeListener* listener)
{
	assert(std::find(this->selection_listeners.begin(), this->selection_listeners.end(), listener) != this->selection_listeners.end());
	this->selection_listeners.erase(std::find(this->selection_listeners.begin(), this->selection_listeners.end(), listener));
}
