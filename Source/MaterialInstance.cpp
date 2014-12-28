#include "MaterialInstance.h"

TMaterialInstance::TMaterialInstance(TBaluMaterial* source, TResourses* resources)
{
	this->source = source;
	texture = resources->CreateTextureFromFile(source->GetImagePath());
}

TBaluTexture TMaterialInstance::GetTexture()
{
	return texture;
}