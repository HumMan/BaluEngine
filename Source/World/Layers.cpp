#include "Layers.h"

using namespace EngineInterface;

TLayer::TLayer()
{
	name = "Layer";
	visible = true;
	alpha = 1;
	locked = false;
	editor_visible = true;
}
TLayer::TLayer(std::string name, bool visible)
{
	this->name = name;
	this->visible = visible;
	alpha = 1;
	locked = false;
	editor_visible = true;
}
std::string TLayer::GetName()
{
	return name;
}
void TLayer::SetName(std::string name)
{
	this->name = name;
}
bool TLayer::IsVisible()
{
	return visible;
}
void TLayer::SetIsVisible(bool visible)
{
	this->visible = visible;
}
int TLayer::GetOrder()
{
	return order;
}
void TLayer::SetOrder(int order)
{
	this->order = order;
}
float TLayer::GetAlpha()
{
	return alpha;
}
void TLayer::SetAlpha(float alpha)
{
	this->alpha = alpha;
}
bool TLayer::IsLocked()
{
	return locked;
}
void TLayer::SetIsLocked(bool is_locked)
{
	this->locked = is_locked;
}
bool TLayer::IsVisibleInEditor()
{
	return editor_visible;
}
void TLayer::SetIsVisibleInEditor(bool is_editor_visible)
{
	this->editor_visible = is_editor_visible;
}
TLayer TLayersManager::GetLayer(int id)
{
	return layers[id];
}

int TLayersManager::GetLayersCount()
{
	return layers.size();
}

void TLayersManager::SetLayer(int id, TLayer layer)
{
	layers[id] = layer;
	for (auto& v : listeners) v->LayerChanged(id);
}

void TLayersManager::AddLayer(TLayer layer, int after_id)
{
	layers.push_back(layer);
	for (auto& v : listeners) v->LayerAdded(layers.size() - 1);
}
void TLayersManager::RemoveLayer(int layer_id)
{
	layers.pop_back();
	for (auto& v : listeners) v->LayerRemoved(layers.size() - 1);
}