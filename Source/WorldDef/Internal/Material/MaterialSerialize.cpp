#include "Material.h"

#include <pugixml.hpp>

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;
using namespace pugi;

void TMaterial::Save(pugi::xml_node& parent_node, const int version)const
{
	xml_node new_node = parent_node.append_child("Material");
	SaveProperties(new_node, version);
}

void TMaterial::Load(const pugi::xml_node& material_node, const int version, IWorld* world)
{
	LoadProperties(material_node, version);
}
