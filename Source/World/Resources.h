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

namespace BaluRender
{
	class TBaluRender;
}
using namespace BaluRender;

class TResources: public EngineInterface::IResources
{
	friend class TBaluEngineRender;
	std::unique_ptr<TResourcesInternal> p;
public:
	TResources(TBaluRender* render, std::string assets_dir);
	TBaluTexture CreateTextureFromFile(std::string path);
	std::string GetAssetsDir();
	~TResources();
};