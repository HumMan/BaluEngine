#pragma once

#include "Material.h"

#include "Resources.h"

class TBaluMaterial;

class TMaterialInstance
{
	TBaluTexture texture;
	TBaluMaterial* source;
public:
	TMaterialInstance(TBaluMaterial* source, TResources* resources);
	TBaluTexture GetTexture();
};