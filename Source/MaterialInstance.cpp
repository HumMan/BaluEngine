#include "MaterialInstance.h"

TMaterialInstance::TMaterialInstance(TBaluMaterial* source, TResources* resources)
{
	this->source = source;
	if (source!=nullptr)
		texture = resources->CreateTextureFromFile(source->GetImagePath());
}

TBaluTexture TMaterialInstance::GetTexture()
{
	return texture;
}