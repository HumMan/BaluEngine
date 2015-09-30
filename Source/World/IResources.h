
#ifndef BALU_ENGINE_DISABLE_PRAGMA_ONCE
#pragma once
#endif

#include <memory>
#include <string>

namespace BaluRender
{
	class TBaluRender;
}

namespace EngineInterface
{

#ifndef BALU_ENGINE_SCRIPT_CLASSES
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
#endif

}