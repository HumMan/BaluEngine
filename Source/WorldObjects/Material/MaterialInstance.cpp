#include "IMaterialInstance.h"
#include "IMaterial.h"

using namespace EngineInterface;

void TMaterialInstance::SourceChanged()
{
	texture = resources->CreateTextureFromFile(source->GetImagePath());
}

TMaterialInstance::TMaterialInstance(TBaluMaterial* source, TResources* resources)
{
	this->source = source;
	this->resources = resources;

	source->AddChangesListener(this);
	if (source!=nullptr)
		texture = resources->CreateTextureFromFile(source->GetImagePath());
}

TMaterialInstance::~TMaterialInstance()
{
	source->RemoveChangesListener(this);
}

TBaluTexture TMaterialInstance::GetTexture()
{
	return texture;
}