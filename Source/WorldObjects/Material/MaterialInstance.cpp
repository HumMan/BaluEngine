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

	
	if (source != nullptr)
	{
		source->AddChangesListener(this);
		texture = resources->CreateTextureFromFile(source->GetImagePath());
	}
}

TMaterialInstance::~TMaterialInstance()
{
	if (source!=nullptr)
		source->RemoveChangesListener(this);
}

TBaluTexture TMaterialInstance::GetTexture()
{
	return texture;
}