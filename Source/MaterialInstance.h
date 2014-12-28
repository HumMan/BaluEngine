#pragma once

#include "Material.h"

#include "Resourses.h"

class TBaluMaterial;

class TMaterialInstance
{
	TBaluTexture texture;
	TBaluMaterial* source;
public:
	TMaterialInstance(TBaluMaterial* source, TResourses* resources);
	TBaluTexture GetTexture();
};