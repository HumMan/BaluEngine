#include "MaterialInstance.h"

using namespace BaluEngine;
using namespace BaluEngine::WorldInstance;
using namespace BaluEngine::WorldInstance::Internal;
using namespace BaluLib;


void TMaterialInstance::SourceChanged()
{
	texture = resources->CreateTextureFromFile(source->GetImagePath());
}

TMaterialInstance::TMaterialInstance(WorldDef::IMaterial* source, TResources* resources)
{
	this->source = source;
	this->resources = resources;
	
	if (source != nullptr)
	{
		//source->AddChangesListener(this);
		texture = resources->CreateTextureFromFile(source->GetImagePath());
	}
}

TMaterialInstance::~TMaterialInstance()
{
	//if (source!=nullptr)
	//	source->RemoveChangesListener(this);
}

TBaluTexture TMaterialInstance::GetTexture()
{
	return texture;
}

