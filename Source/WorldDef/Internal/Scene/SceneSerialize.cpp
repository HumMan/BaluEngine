#include "Scene.h"

#include <pugixml.hpp>

#include "../Common/SerializeCommon.h"

using namespace pugi;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace BaluLib;

void TScene::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node new_node = parent_node.append_child("Scene");
	TProperties::Save(new_node,version);
	new_node.append_attribute("name").set_value(GetName().c_str());
	{
		xml_node instances_node = new_node.append_child("instances");
		for (int i = 0; i < instances.size(); i++)
		{
			instances[i]->Save(instances_node, version);
		}
	}
	xml_node viewports_node = new_node.append_child("Viewports");
	{
		for (auto& v : viewports)
		{
			v.second.Save(viewports_node, version);
			viewports_node.last_child().append_attribute("name").set_value(v.first.c_str());
		}
	}
}

void TScene::Load(const pugi::xml_node& scene_node, const int version, IWorld* world)
{
	TProperties::Load(scene_node, version, world);
	{
		xml_node instances_node = scene_node.child("instances");
		for (pugi::xml_node instance_node = instances_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			auto new_instance = SceneObjectFactory::Create(instance_node.name());
			new_instance->Load(instance_node, version, world);
			instances.push_back(std::unique_ptr<ISceneObject>(new_instance));
		}
	}
	{
		xml_node viewports_node = scene_node.child("Viewports");
		for (pugi::xml_node instance_node = viewports_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			TViewport temp;
			temp.Load(instance_node, version, world);
			viewports.insert(std::make_pair(instance_node.attribute("name").as_string(), temp));
		}
	}
}


void TViewport::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node viewport_node = parent_node.append_child("Viewport");
	SerializeCommon::SaveTransform(viewport_node, "transform", transform);
	viewport_node.append_attribute("aspect").set_value(aspect);
	viewport_node.append_attribute("width").set_value(width);
}

void TViewport::Load(const pugi::xml_node& viewport_node, const int version, IWorld* world)
{
	SerializeCommon::LoadTransform(viewport_node.child("transform"));
	aspect = viewport_node.attribute("aspect").as_float();
	width = viewport_node.attribute("width").as_float();
}
