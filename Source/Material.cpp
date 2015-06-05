#include "Material.h"
#include "World.h"

TBaluMaterial::TBaluMaterial()
{
	world = nullptr;
}

#ifdef BALUENGINE_DESIGN_TIME
TBaluMaterial::TBaluMaterial(std::string material_name, TBaluWorld* world)
{
	this->material_name = material_name;
	this->world = world;
}
#endif

EngineInterface::IProperties* TBaluMaterial::GetProperties()
{
	return nullptr;
}

void TBaluMaterial::SetBlendMode(TTransparentMode mode)
{
	this->blend_mode = mode;
}

void TBaluMaterial::SetAlphaTestValue(float alpha_test_value)
{
	this->alpha_test_value = alpha_test_value;
}

void TBaluMaterial::SetName(std::string name)
{
	assert(!world->ObjectNameExists(TWorldObjectType::Material, name.c_str()));
	material_name = name;
}

std::string TBaluMaterial::GetName()
{
	return  material_name;
}

void TBaluMaterial::SetImagePath(std::string image_path)
{
	this->image_path = image_path;
}

std::string TBaluMaterial::GetImagePath()
{
	return image_path;
}

void TBaluMaterial::SetColor(TVec4 color)
{
	this->color = color;
}
