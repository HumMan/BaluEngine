
#include "ClassCommands.h"

#include "Class.h"

#include <pugixml.hpp>
#include "../Common/SerializeCommon.h"

using namespace pugi;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;


SceneObjectPropertyChange::SceneObjectPropertyChange(IWorld* world, IScene* scene, int instance_id, const std::string& property_name
	, const std::string& old_value, const std::string& new_value)
{
	this->world = world;
	this->scene_name = scene->GetName();
	this->instance_id = instance_id;
	this->property_name = property_name;
	this->old_value = old_value;
	this->new_value = new_value;
}

void SceneObjectPropertyChange::Do()
{
	auto scene = world->GetScene(scene_name);
	auto instance = dynamic_cast<TTransformedClass*>(scene->GetInstance(instance_id));
	instance->GetProperty(property_name)->DeserializeValue(new_value);
}
void SceneObjectPropertyChange::Undo()
{
	auto scene = world->GetScene(scene_name);
	auto instance = dynamic_cast<TTransformedClass*>(scene->GetInstance(instance_id));
	instance->GetProperty(property_name)->DeserializeValue(old_value);
}

