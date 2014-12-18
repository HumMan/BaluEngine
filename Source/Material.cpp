#include "Material.h"

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
	this->material_name = name;
}

std::string TBaluMaterial::GetName()
{
	return material_name;
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
