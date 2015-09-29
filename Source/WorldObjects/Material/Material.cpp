#include "Material.h"
#include "World/World.h"

#include "MaterialEditor\materialEditor.h"

TBaluMaterial::TBaluMaterial()
{
	world = nullptr;
}

TBaluMaterial::TBaluMaterial(std::string material_name, TBaluWorld* world)
{
	this->material_name = material_name;
	this->world = world;
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

IAbstractEditor* TBaluMaterial::CreateEditor(TDrawingHelperContext drawing_context, EngineInterface::IBaluSceneInstance* editor_scene_instance)
{
	auto result = new TMaterialEditor();
	result->Initialize(drawing_context, world, this, editor_scene_instance);
	return result;
}