#include "Interface.h"

#include <World\SerializeCommon.h>

using namespace EngineInterface;

void TBaluMaterial::Save(pugi::xml_node& parent_node, const int version)
{
	xml_node new_node = parent_node.append_child("Material");
	new_node.append_attribute("name").set_value(name.c_str());
	new_node.append_attribute("image_path").set_value(image_path.c_str());
	SaveColor(new_node, color);
}

void TBaluMaterial::Load(const pugi::xml_node& node, const int version, TBaluWorld* world)
{
	name = node.attribute("name").as_string();
	image_path = node.attribute("image_path").as_string();
	color = LoadColor(node.child("Color"));
}
