#pragma once

#include <memory>
#include <string>

namespace BaluRender
{
	class TBaluRender;
}

namespace EngineInterface
{

	class IResources
	{
	public:
		virtual ~IResources(){}
	};

	class TResourcesInternal;
	
	class TBaluTexture
	{
		int id;
	public:
	};

	class TResources : public IResources
	{
		friend class TBaluEngineRender;
		std::unique_ptr<TResourcesInternal> p;
	public:
		TResources(BaluRender::TBaluRender* render, std::string assets_dir);
		TBaluTexture CreateTextureFromFile(std::string path);
		std::string GetAssetsDir();
		~TResources();
	};

}