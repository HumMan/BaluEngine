#include "baluEditorDefsSerializer.h"

void TBaluEditorDefsSerializer::Save(TBaluWorldDef& use_world, pugi::xml_node& parent_node, const int version)
{
	use_world.Save(parent_node, version);
}