#include <World\SerializeCommon.h>

#include "Interface.h"

#include <World\IWorld.h>

using namespace EngineInterface;

void TBaluScene::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Scene");
	new_node.append_attribute("name").set_value(scene_name.c_str());
	{
		xml_node instances_node = new_node.append_child("instances");
		for (int i = 0; i < instances.size(); i++)
		{
			EngineInterface::PropertyType type;
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
	//TODO TLayersManager layers;
	properties.Save(new_node, version);
}

void TBaluScene::Load(const pugi::xml_node& scene_node, const int version, TBaluWorld* world)
{
	scene_name = scene_node.attribute("name").as_string();
	{
		xml_node instances_node = scene_node.child("instances");
		for (pugi::xml_node instance_node = instances_node.first_child(); instance_node; instance_node = instance_node.next_sibling())
		{
			auto new_instance = SceneObjectFactory::Create(instance_node.name());
			new_instance->Load(instance_node, version, world);
			instances.push_back(std::unique_ptr<TSceneObject>(new_instance));
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
	//TODO TLayersManager layers;
	properties.Load(scene_node, version, world);
}

void TBaluSceneClassInstance::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("ClassInstance");

	new_node.append_attribute("class_name").set_value(balu_class->GetName().c_str());
	SaveTransformWithScale(new_node, "Transform", transform);
}

void TBaluSceneClassInstance::Load(const pugi::xml_node& instance_node, const int version, TBaluWorld* world)
{
	balu_class = dynamic_cast<TBaluClass*>(world->GetObjectByName(TWorldObjectType::Class, instance_node.attribute("class_name").as_string()));
	transform = LoadTransformWithScale(instance_node.child("Transform"));
}

void TViewport::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node viewport_node = parent_node.append_child("Viewport");
	SaveTransform(viewport_node, "transform", transform);
	viewport_node.append_attribute("aspect").set_value(aspect);
	viewport_node.append_attribute("width").set_value(width);
}

void TViewport::Load(const pugi::xml_node& viewport_node, const int version, TBaluWorld* world)
{
	LoadTransform(viewport_node.child("transform"));
	aspect = viewport_node.attribute("aspect").as_float();
	width = viewport_node.attribute("width").as_float();
}
