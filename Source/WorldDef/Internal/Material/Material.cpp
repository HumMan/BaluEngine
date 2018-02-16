#include "Material.h"

TBaluMaterial::TBaluMaterial(std::string material_name, IWorld* world)
	:TWorldObject(world, material_name)
{
}

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