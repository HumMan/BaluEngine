#pragma once

#include "Material.h"

#include "World/Resources.h"

class TBaluMaterial;

using namespace EngineInterface;

class TMaterialInstance
{
	TBaluTexture texture;
	TBaluMaterial* source;
public:
	TMaterialInstance(TBaluMaterial* source, TResources* resources);
	TBaluTexture GetTexture();
};