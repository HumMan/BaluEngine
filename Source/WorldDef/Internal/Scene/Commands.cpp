
#include "Commands.h"

#include "Scene.h"

#include <pugixml.hpp>
#include "../Common/SerializeCommon.h"

using namespace pugi;
using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

DestroySceneObject::DestroySceneObject(IWorld* world, IScene* scene, int instance_id, ISceneObject* instance)
{
	this->world = world;
	this->scene_name = scene->GetName();
	this->instance_id = instance_id;

	xml_document doc;
	instance->Save(doc, 1);
	xml_string_writer writer;
	doc.save(writer);
	this->scene_instance_serialized = writer.result;
}

void DestroySceneObject::Do()
{
	auto scene = dynamic_cast<TScene*>(world->GetScene(scene_name));
	scene->DestroyInstance(instance_id);
}
void DestroySceneObject::Undo()
{
	auto scene = dynamic_cast<TScene*>(world->GetScene(scene_name));
	xml_document doc;
	doc.load_string(scene_instance_serialized.c_str());
	auto new_instance = SceneObjectFactory::Create(doc.first_child().name(), scene);
	new_instance->Load(doc.first_child(), 1, world);
	scene->InsertInstance(new_instance, instance_id);
}