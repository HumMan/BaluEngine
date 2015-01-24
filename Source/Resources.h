#pragma once

#include <string>
#include <memory>

#include "EngineInterfaces\IResources.h"

class TBaluTexture
{
	int id;
public:
};

class TResourcesInternal;
class TBaluRender;

class TResources: public EngineInterface::IResources
{
	friend class TBaluEngineRender;
	std::unique_ptr<TResourcesInternal> p;
	TResources(TBaluRender* render);
public:
	TBaluTexture CreateTextureFromFile(std::string path);
	~TResources();
};