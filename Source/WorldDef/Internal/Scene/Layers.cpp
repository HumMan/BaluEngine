#include "Layers.h"

#include <pugixml.hpp>

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace pugi;

TLayer::TLayer()
{
}

TLayer::TLayer(std::string name, bool visible)
{
}

void BaluEngine::WorldDef::Internal::TLayer::Save(pugi::xml_node & parent_node, const int version) const
{
	xml_node new_node = parent_node.append_child("Layer");
	TProperties::Save(new_node, version);
}

void BaluEngine::WorldDef::Internal::TLayer::Load(const pugi::xml_node & instance_node, const int version, IWorld * world)
{
	TProperties::Load(instance_node, version, world);
}

TLayersManager::TLayersManager(IScene* scene)
{
	layers.push_back(std::unique_ptr<TLayer>(new TLayer("Default", true)));
	this->scene = scene;
}

ILayer* TLayersManager::GetLayer(int id)
{
	return layers[id].get();
}

int TLayersManager::GetLayersCount()
{
	return layers.size();
}

ILayer* TLayersManager::AddLayer(int after_id, const std::string& name)
{
	layers.push_back(std::unique_ptr<TLayer>(new TLayer(name, true)));
	for (auto& v : listeners) v->LayerAdded(layers.size() - 1);

	return layers.back().get();
}
void TLayersManager::RemoveLayer(int layer_id)
{
	layers.pop_back();
	for (auto& v : listeners) v->LayerRemoved(layers.size() - 1);
}