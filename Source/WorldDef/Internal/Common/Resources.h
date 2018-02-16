#pragma once

#include "../../Interface.h"

namespace BaluEngine
{
	namespace WorldDef
	{
		namespace Internal
		{

			class IResources
			{
			public:
				virtual ~IResources() {}
			};

			class TResourcesInternal;

			class TBaluTexture
			{
				int id;
			public:
			};

			class TResources : public IResources
			{
				std::unique_ptr<TResourcesInternal> p;
			public:
				TResources(BaluRender::TBaluRender* render, std::string assets_dir);
				TBaluTexture CreateTextureFromFile(std::string path);
				std::string GetAssetsDir();
				~TResources();
			};
		}
	}
}