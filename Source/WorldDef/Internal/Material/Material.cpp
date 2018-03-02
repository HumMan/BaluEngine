#include "Material.h"

using namespace BaluEngine::WorldDef;
using namespace BaluEngine::WorldDef::Internal;

TMaterial::TMaterial(std::string material_name, IWorld* world)
	:TWorldObject(world, material_name)
{
	InitAllProperties();
}