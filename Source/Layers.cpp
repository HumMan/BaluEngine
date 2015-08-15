#include "Layers.h"

TLayer::TLayer()
{
	name = "Layer";
	visible = true;
}
TLayer::TLayer(std::string name, bool visible)
{
	this->name = name;
	this->visible = visible;
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

float TLayerInstance::GetAlpha()
{
	return alpha;
}
void TLayerInstance::SetAlpha(float alpha)
{
	this->alpha = alpha;
}
bool TLayerInstance::IsLocked()
{
	return locked;
}
void TLayerInstance::SetIsLocked(bool is_locked)
{
	this->locked = is_locked;
}
bool TLayerInstance::IsVisibleInEditor()
{
	return editor_visible;
}
void TLayerInstance::SetIsVisibleInEditor(bool is_editor_visible)
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

TLayersManagerInstance::TLayersManagerInstance(TLayersManager* source)
	:source_changes_listener(this)
{
	this->source = source;
	for (int i = 0; i < source->GetLayersCount();i++)
	{
		layers.push_back(TLayerInstance());
	}
	source->AddListener(&this->source_changes_listener);
}
TLayersManagerInstance::~TLayersManagerInstance()
{
	source->RemoveListener(&this->source_changes_listener);
}
TLayersManager* TLayersManagerInstance::GetSource()
{
	return source;
}
TInstanceLayersManagerChangeListener::TInstanceLayersManagerChangeListener(TLayersManagerInstance* manager)
{
	this->manager = manager;
}
void TInstanceLayersManagerChangeListener::LayerReordered(int layer_id, int after_id)
{

}
void TInstanceLayersManagerChangeListener::LayerAdded(int layer_id)
{
	manager->layers.insert(manager->layers.begin() + layer_id, TLayerInstance());
}
void TInstanceLayersManagerChangeListener::LayerRemoved(int layer_id)
{
	manager->layers.erase(manager->layers.begin() + layer_id);
}
void TInstanceLayersManagerChangeListener::LayerChanged(int layer_id)
{

}