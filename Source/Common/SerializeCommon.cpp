#include "SerializeCommon.h"

using namespace EngineInterface;
using namespace BaluLib;

void SaveColor(pugi::xml_node& parent, TVec4 color)
{
	xml_node new_node = parent.append_child("Color");
	new_node.append_attribute("r").set_value(color[0]);
	new_node.append_attribute("g").set_value(color[1]);
	new_node.append_attribute("b").set_value(color[2]);
	new_node.append_attribute("a").set_value(color[3]);
}

TVec4 LoadColor(pugi::xml_node& node)
{
	TVec4 color;
	color[0] = node.attribute("r").as_float();
	color[1] = node.attribute("g").as_float();
	color[2] = node.attribute("b").as_float();
	color[3] = node.attribute("a").as_float();
	return color;
}

void SaveCoord(pugi::xml_node& parent_node, std::string name, TVec2 coord)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	new_node.append_attribute("x").set_value(coord[0]);
	new_node.append_attribute("y").set_value(coord[1]);
}

TVec2 LoadCoord(pugi::xml_node& node)
{
	TVec2 coord;
	coord[0] = node.attribute("x").as_float();
	coord[1] = node.attribute("y").as_float();
	return coord;
}

void SaveTransform(pugi::xml_node& parent_node, std::string name, TBaluTransform transform)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	SaveCoord(new_node, "offset", transform.position);
	new_node.append_attribute("rotation").set_value(transform.angle.GetAngle());
}

TBaluTransform LoadTransform(pugi::xml_node& node)
{
	TBaluTransform transform;
	transform.position = LoadCoord(node.child("offset"));
	transform.angle.Set(node.attribute("rotation").as_float());
	return transform;
}

void SaveTransformWithScale(pugi::xml_node& parent_node, std::string name, TBaluTransformWithScale transform)
{
	xml_node new_node = parent_node.append_child(name.c_str());
	SaveCoord(new_node, "offset", transform.transform.position);
	new_node.append_attribute("rotation").set_value(transform.transform.angle.GetAngle());
	SaveCoord(new_node, "scale", transform.scale);
}

TBaluTransformWithScale LoadTransformWithScale(pugi::xml_node& node)
{
	TBaluTransformWithScale transform;
	transform.transform = LoadTransform(node);
	transform.scale = LoadCoord(node.child("scale"));
	return transform;
}
