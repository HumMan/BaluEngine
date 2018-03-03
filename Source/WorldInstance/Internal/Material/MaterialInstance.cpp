#include "IMaterialInstance.h"
#include <WorldDef/Objects/Material/IMaterial.h>

using namespace EngineInterface;

void TMaterialInstance::SourceChanged()
{
	texture = resources->CreateTextureFromFile(source->GetImagePath());
}

TMaterialInstance::TMaterialInstance(TMaterial* source, TResources* resources)
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

#include "../Scene/ISceneInstance.h"

TSceneInstance* TSceneObjectInstance::GetScene()
{
	return scene;
}
TSceneObjectInstance::TSceneObjectInstance(TSceneInstance* scene)
{
	this->scene = scene;
	scene->AddInstance(this);
}