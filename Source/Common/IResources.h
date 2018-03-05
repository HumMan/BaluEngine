#pragma once

#include <memory>
#include <string>

namespace BaluRender
{
	class TBaluRender;
}

namespace BaluEngine
{
	namespace WorldInstance
	{
		//class IResources
		//{
		//public:
		//	virtual ~IResources() {}
		//};

		
		//TODO убрать из WorldInstance в Internal
		class TBaluTexture
		{
			int id;
		public:
		};

		class TResources// : public IResources
		{
			class TResourcesInternal;
			std::unique_ptr<TResourcesInternal> p;
		public:
			TResources(BaluRender::TBaluRender* render, std::string assets_dir);
			TBaluTexture CreateTextureFromFile(std::string path);
			std::string GetAssetsDir();
			~TResources();
		};
	}


}